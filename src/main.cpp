#include "sensors.h"
#include "utils.h"
#include <stdint.h>
typedef int16_t int16;

extern "C" {
  #include "random_forest.h"  // CHANGED: Use integer-only emlearn header
}


#ifndef RF_MODEL_N_TREES
#define RF_MODEL_N_TREES 4
#endif

#ifndef RF_MODEL_N_FEATURES
#define RF_MODEL_N_FEATURES 4
#endif

#ifndef RF_MODEL_Y_SCALE
#define RF_MODEL_Y_SCALE 10000
#endif

// CRITICAL: Function name from emlearn is model_Nico_allparams_predict
// NOT rf_model_predict. We create an alias for compatibility:
#ifndef rf_model_predict
#define rf_model_predict(features) model_Nico_allparams_predict(features, RF_MODEL_N_FEATURES)
#endif

// If you want RF enabled, uncomment the next line (or define it in build flags)
// #define USE_RF_ON_DEVICE

// ============================================================================
// QUANTIZATION CONSTANTS - MUST MATCH PYTHON TRAINING
// ============================================================================
// These scales are used to convert float EWMA values to int16 for the model

// FEATURE SCALES (for inputs)
#define TEMP_SCALE  500     // Temperature EWMA scaling
#define CAP_SCALE   10000   // Base capacity scaling
#define VOLT_SCALE  2000    // Voltage EWMA scaling
#define CURR_SCALE  4000    // Current EWMA scaling

// TARGET SCALE (for output) - NEW!
#define Y_SCALE     RF_MODEL_Y_SCALE   // Target Ah scaling (model outputs Ah * Y_SCALE)

// EWMA alpha parameters - MUST MATCH PYTHON TRAINING
// Voltage_ewma: alpha = 1/3001, adjust=False
// Current_ewma: alpha = 1/2501, adjust=False
// Temp_ewma:    alpha = 1/1310, adjust=True  ← CHANGED: was 1/710, now matches Python
static const float alphaV = 1.0f / 3001.0f;  // Voltage EWMA alpha
static const float alphaI = 1.0f / 2501.0f;  // Current EWMA alpha
static const float alphaT = 1.0f / 1310.0f;  // Temperature EWMA alpha (CORRECTED)

// Number of features for the model
#define NUM_FEATURES  RF_MODEL_N_FEATURES

// Base capacity constant (same units as Ah in dataset)
static const float BASE_CAPACITY = 2.9f;

// Pre-computed base_capacity quantized value (constant)
static const int16_t BASE_CAPACITY_Q = (int16_t)(BASE_CAPACITY * CAP_SCALE);

// ============================================================================
// EWMA STATE VARIABLES
// ============================================================================
// All EWMA states maintained in float precision, then quantized for model input
// The shift(1) semantics: we use the PREVIOUS EWMA value as the feature,
// then UPDATE the EWMA with the current measurement AFTER prediction.

// Voltage EWMA (adjust=False): simple recursive update
static float voltage_ewma = 0.0f;        // Current EWMA state
static float voltage_ewma_prev = 0.0f;   // Previous EWMA (used as feature)

// Current EWMA (adjust=False): simple recursive update
static float current_ewma = 0.0f;        // Current EWMA state
static float current_ewma_prev = 0.0f;   // Previous EWMA (used as feature)

// Temperature EWMA (adjust=True): bias-corrected form using num/den
// adjust=True EWMA formula (bias-corrected):
//   beta = 1 - alpha
//   num_next = beta * num_prev + x_current
//   den_next = beta * den_prev + 1
//   ewma = num_next / den_next
// Initialize: num=0, den=0 -> ewma=0 (matches fillna(0))
static float temp_ewma_num = 0.0f;       // Numerator state
static float temp_ewma_den = 0.0f;       // Denominator state
static float temp_ewma_prev = 0.0f;      // Previous EWMA (used as feature)

static bool first_sample = true;         // Track if this is the first sample

// ============================================================================
// HELPER FUNCTIONS
// ============================================================================

// Clamp value to int16 range [-32768, 32767]
inline int16_t clamp_to_int16(float val) {
  if (val > 32767.0f) return 32767;
  if (val < -32768.0f) return -32768;
  return (int16_t)roundf(val);
}

// Quantize a float feature to int16 using the given scale
inline int16_t quantize_feature(float value, float scale) {
  return clamp_to_int16(value * scale);
}

// ============================================================================
// CAPACITY ESTIMATION USING INTEGER-ONLY RANDOM FOREST
// ============================================================================
// This function builds the feature vector exactly as in Python training:
//   1. Temp_ewma      (from previous EWMA state)
//   2. base_capacity  (constant 2.9)
//   3. Voltage_ewma   (from previous EWMA state)
//   4. Current_ewma   (from previous EWMA state)
// All quantized to int16 using per-feature scales.
//
// CRITICAL CHANGE: Model now returns int32_t (quantized Ah * Y_SCALE)
// We must divide by Y_SCALE to get actual Ah in float.
// ============================================================================
static float calculateCapacity(SensorReadings readings[]) {
  
  // -------------------------------------------------------------------------
  // STEP 1: Build feature vector from PREVIOUS EWMA values (shift(1) logic)
  // -------------------------------------------------------------------------
  
  // Feature order MUST match training:
  // 0. Temp_ewma_q
  // 1. base_capacity_q
  // 2. Voltage_ewma_q
  // 3. Current_ewma_q
  
  int16_t features[NUM_FEATURES];
  
  features[0] = quantize_feature(temp_ewma_prev, TEMP_SCALE);      // Temp_ewma_q
  features[1] = BASE_CAPACITY_Q;                                   // base_capacity_q (constant)
  features[2] = quantize_feature(voltage_ewma_prev, VOLT_SCALE);   // Voltage_ewma_q
  features[3] = quantize_feature(current_ewma_prev, CURR_SCALE);   // Current_ewma_q
  
  // -------------------------------------------------------------------------
  // STEP 2: Call the integer-only model
  // -------------------------------------------------------------------------
  // CRITICAL: The actual function name is model_Nico_allparams_predict
  // But we've aliased it to rf_model_predict above for compatibility
  // Function signature: int32_t model_Nico_allparams_predict(const int16_t *features, int32_t features_length)
  // Returns: Ah * Y_SCALE (quantized integer)
  
  int32_t ah_pred_q = model_Nico_allparams_predict((features), RF_MODEL_N_FEATURES);  
  
  // Dequantize: convert from int32 back to float Ah
  float ah_pred = (float)ah_pred_q / (float)Y_SCALE;
  
  // DO NOT clamp to [0,100] - the model predicts Ah, not percentage
  // The valid range for Ah depends on your battery (e.g., 0 to ~3 Ah)
  
  // -------------------------------------------------------------------------
  // STEP 3: Update EWMA states with CURRENT sensor reading (after prediction)
  // -------------------------------------------------------------------------
  // This implements the shift(1) semantics: prediction uses previous EWMA,
  // then we update for next iteration.
  
  float current_voltage = readings[0].voltage;
  float current_current = readings[0].current;
  float current_temp = (readings[0].temp1 + readings[0].temp2 + readings[0].temp3) / 3.0f;
  
  if (first_sample) {
    // First sample: initialize EWMA states
    // For adjust=False: ewma starts at first value
    // For adjust=True: num and den start accumulating
    voltage_ewma = current_voltage;
    current_ewma = current_current;
    
    // For adjust=True temp EWMA: initialize num and den
    temp_ewma_num = current_temp;
    temp_ewma_den = 1.0f;
    
    first_sample = false;
  } else {
    // Subsequent samples: update EWMAs
    
    // Voltage EWMA (adjust=False): ewma_next = (1 - alpha) * ewma_prev + alpha * x
    voltage_ewma = (1.0f - alphaV) * voltage_ewma + alphaV * current_voltage;
    
    // Current EWMA (adjust=False): ewma_next = (1 - alpha) * ewma_prev + alpha * x
    current_ewma = (1.0f - alphaI) * current_ewma + alphaI * current_current;
    
    // Temperature EWMA (adjust=True): bias-corrected form
    // beta = 1 - alpha
    // num_next = beta * num_prev + x_current
    // den_next = beta * den_prev + 1
    // ewma = num_next / den_next
    float betaT = 1.0f - alphaT;
    temp_ewma_num = betaT * temp_ewma_num + current_temp;
    temp_ewma_den = betaT * temp_ewma_den + 1.0f;
  }
  
  // Store current EWMA as "previous" for next iteration (shift(1))
  voltage_ewma_prev = voltage_ewma;
  current_ewma_prev = current_ewma;
  
  // For adjust=True temp EWMA, compute the bias-corrected value
  if (temp_ewma_den > 0.0f) {
    temp_ewma_prev = temp_ewma_num / temp_ewma_den;
  } else {
    temp_ewma_prev = 0.0f;  // Should not happen after first sample
  }
  
  return ah_pred;
}

// ============================================================================
// FEATURE STRUCT POPULATION (for logging/debugging)
// ============================================================================
Features getFeatures(SensorReadings readingsArray[], Features oldFeatures, int i) {
  Features features = {};

  features.time = millis() / 1000.0f;
  
  // Call capacity estimation (which also updates EWMA states)
  features.capacity = calculateCapacity(readingsArray);
  
  features.temperature =
      (readingsArray[0].temp1 + readingsArray[0].temp2 + readingsArray[0].temp3) / 3.0f;

  features.voted_temperature =
      votedTemperature(readingsArray[0].temp1, readingsArray[0].temp2, readingsArray[0].temp3);

  int prev_count = (i > 0) ? i : 0;
  int new_count = prev_count + 1;

  if (prev_count == 0 || oldFeatures.count_all <= 0) {
    features.i_mean_all = readingsArray[0].current;
    features.v_mean_all = readingsArray[0].voltage;
  } else {
    features.i_mean_all =
        (oldFeatures.i_mean_all * prev_count + readingsArray[0].current) / (prev_count + 1);
    features.v_mean_all =
        (oldFeatures.v_mean_all * prev_count + readingsArray[0].voltage) / (prev_count + 1);
  }

  int valid_samples = (new_count < 10) ? new_count : 10;

  float iv[10];
  int iv_count = 0;
  float power_vals[10];
  int power_count = 0;

  for (int k = 0; k < valid_samples; ++k) {
    float v = readingsArray[k].voltage;
    float c = readingsArray[k].current;
    if (v != 0.0f) iv[iv_count++] = c / v;
    if (v != 0.0f || c != 0.0f) power_vals[power_count++] = v * c;
  }

  features.i_v_ratio_10   = computeArrayMean(iv, iv_count);
  features.power_mean_10  = computeArrayMean(power_vals, power_count);

  features.power_prev = (prev_count >= 1)
      ? (readingsArray[1].voltage * readingsArray[1].current)
      : 0.0f;

  features.count_all = new_count;
  features.i_v_ratio = (readingsArray[0].voltage != 0.0f)
      ? (readingsArray[0].current / readingsArray[0].voltage)
      : 0.0f;

  return features;
}

// ============================================================================
// ARDUINO MAIN FUNCTIONS
// ============================================================================

static unsigned long sampling_period = 0;
static SensorReadings readingsArray[10] = {};
static int index = 0;
static Features lastFeatures = {};
static String cmdBuffer;

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 2000) {}

  Serial.println("Battery Monitor - Integer-Only RF Model");
  Serial.println("========================================");
  Serial.println("Model configuration:");
  Serial.print("  Trees: ");
  Serial.println(RF_MODEL_N_TREES);
  Serial.print("  Features: ");
  Serial.println(RF_MODEL_N_FEATURES);
  Serial.print("  Target scale: ");
  Serial.println(RF_MODEL_Y_SCALE);
  Serial.println();
  Serial.println("Feature order (int16 quantized):");
  Serial.println("  0. Temp_ewma      (scaled by 500)");
  Serial.println("  1. base_capacity  (scaled by 10000, constant=2.9)");
  Serial.println("  2. Voltage_ewma   (scaled by 2000)");
  Serial.println("  3. Current_ewma   (scaled by 4000)");
  Serial.println();
  Serial.println("EWMA alpha values:");
  Serial.print("  Temperature: 1/");
  Serial.println(1.0f / alphaT);
  Serial.print("  Voltage: 1/");
  Serial.println(1.0f / alphaV);
  Serial.print("  Current: 1/");
  Serial.println(1.0f / alphaI);
  Serial.println();
  Serial.println("Model returns: int32 (Ah * Y_SCALE)");
  Serial.println("Converted to: float Ah");
  Serial.println("========================================");
  Serial.println();

  const int sampling_freq = 1;                 // Hz
  sampling_period = 1000UL / sampling_freq;    // ms
}

static void processSerialLine(String line) {
  line.trim();
  if (line.length() == 0) return;

  line.toLowerCase();
  Serial.print("Unknown command: ");
  Serial.println(line);
}

void loop() {
  while (Serial.available()) {
    char ch = (char) Serial.read();
    if (ch == '\r') continue;

    if (ch == '\n') {
      if (cmdBuffer.length() > 0) {
        processSerialLine(cmdBuffer);
        cmdBuffer = "";
      }
    } else {
      cmdBuffer += ch;
      if (cmdBuffer.length() > 128) cmdBuffer.remove(128);
    }
  }

  static unsigned long last = 0;
  unsigned long now = millis();

  if (now - last >= sampling_period) {
    last = now;

    SensorReadings r = getHardwareReadings();

    for (int j = 9; j > 0; --j) readingsArray[j] = readingsArray[j - 1];
    readingsArray[0] = r;

    Features f = getFeatures(readingsArray, lastFeatures, index);
    serialPrintReadings(r, f);

    lastFeatures = f;
    ++index;
  }
}
