#include "sensors.h"
#include "utils.h"
#include <stdint.h>
typedef int16_t int16;
typedef int32_t int32;
extern "C"
{
#include "random_forest_boring.h"
}

// ============================================================================
// QUANTIZATION SCALES (must match Python training script)
// ============================================================================
// INT16 scales
#define TEMP_SCALE 500
#define CAP_SCALE 10000
#define VOLT_SCALE 2000
#define CURR_SCALE 100000000L
#define NUM_FEATURES 4
// pins
const int PIN_TO_SPARE = 3;
const int PIN_FROM_SPARE = 2;
const int PIN_RELAY = A1;

static const float BASE_CAPACITY = 4.2f;
static const int16_t BASE_CAPACITY_Q = (int16_t)(BASE_CAPACITY * CAP_SCALE);
static SensorReadings readingsArray[10] = {};
static int index = 0;
static Features lastFeatures = {};
static unsigned long sampling_period = 1000;
static unsigned long lastSampleTime = 0;
// ============================================================================
// CLAMPING FUNCTIONS
// ============================================================================

inline int16_t clamp_to_int16(float val)
{
  if (val > 32767.0f)
    return 32767;
  if (val < -32768.0f)
    return -32768;
  return (int16_t)roundf(val);
}

inline int32_t clamp_to_int32(float val)
{
  if (val > 2147483647.0f)
    return 2147483647L;
  if (val < -2147483648.0f)
    return -2147483648L;
  return (int32_t)roundf(val);
}
// ============================================================================
// WATCHDOG VARIABLES
// ============================================================================

unsigned long lastBackupSignal = 0;       // Stores the last time backup talked to us
const unsigned long TIMEOUT_LIMIT = 3500; // 3.5 seconds (gives backup 3 tries)
bool backupWarningActive = false;
int lastWatchdogState = LOW;
// ============================================================================
// QUANTIZATION FUNCTIONS
// ============================================================================

inline int16_t quantize_feature_int16(float value, float scale)
{
  return clamp_to_int16(value * scale);
}

inline int32_t quantize_feature_int32(float value, float scale)
{
  return clamp_to_int32(-value * scale);
}

// ============================================================================
// CAPACITY CALCULATION (Model Inference)
// ============================================================================

static float calculateCapacity(SensorReadings readings[])
{
  // Feature array - using int32_t to accommodate mixed precision
  // emlearn with dtype='int32' expects int32_t array
  int32_t x_i[NUM_FEATURES];

  // Get current sensor readings
  float current_voltage = readings[0].voltage;
  float current_current = readings[0].current;
  float current_temp = votedTemperature(readings[0].temp1, readings[0].temp2, readings[0].temp3);

  // Quantize features in the EXACT order expected by the model:
  // 1. Temp_ewma_q      (int16)
  // 2. base_capacity_q  (int16)
  // 3. Voltage_ewma_q   (int16)
  // 4. Current_ewma_q   (int32)

  x_i[0] = (int32_t)quantize_feature_int16(current_temp, TEMP_SCALE);
  x_i[1] = (int32_t)BASE_CAPACITY_Q;
  x_i[2] = (int32_t)quantize_feature_int16(current_voltage, VOLT_SCALE);
  x_i[3] = quantize_feature_int32(current_current, CURR_SCALE); // int32 for Current

  // Debug print
  Serial.print("Quant - T:");
  Serial.print(x_i[0]);
  Serial.print(" Cap:");
  Serial.print(x_i[1]);
  Serial.print(" V:");
  Serial.print(x_i[2]);
  Serial.print(" I:");
  Serial.print(x_i[3]);
  Serial.print(" | ");

  // Call model prediction
  // Note: Update function name to match your exported model name
  float ah_pred = model_int32_current_predict(x_i, NUM_FEATURES);

  return ah_pred;
}

// ============================================================================
// FEATURE EXTRACTION (for other purposes, not used in model)
// ============================================================================

Features getFeatures(SensorReadings readingsArray[], Features oldFeatures, int i)
{
  Features features = {};
  features.time = millis() / 1000.0f;
  features.capacity = calculateCapacity(readingsArray);
  features.temperature = (readingsArray[0].temp1 + readingsArray[0].temp2 + readingsArray[0].temp3) / 3.0f;
  features.voted_temperature = votedTemperature(readingsArray[0].temp1, readingsArray[0].temp2, readingsArray[0].temp3);

  int prev_count = (i > 0) ? i : 0;

  if (prev_count == 0 || oldFeatures.count_all <= 0)
  {
    features.i_mean_all = readingsArray[0].current;
    features.v_mean_all = readingsArray[0].voltage;
  }
  else
  {
    features.i_mean_all = (oldFeatures.i_mean_all * prev_count + readingsArray[0].current) / (prev_count + 1);
    features.v_mean_all = (oldFeatures.v_mean_all * prev_count + readingsArray[0].voltage) / (prev_count + 1);
  }

  int valid_samples = (prev_count + 1 < 10) ? prev_count + 1 : 10;
  float iv[10], power_vals[10];
  int iv_count = 0, power_count = 0;

  for (int k = 0; k < valid_samples; ++k)
  {
    float v = readingsArray[k].voltage;
    float c = readingsArray[k].current;
    if (v != 0.0f)
      iv[iv_count++] = c / v;
    if (v != 0.0f || c != 0.0f)
      power_vals[power_count++] = v * c;
  }

  features.i_v_ratio_10 = computeArrayMean(iv, iv_count);
  features.power_mean_10 = computeArrayMean(power_vals, power_count);
  features.power_prev = (prev_count >= 1) ? (readingsArray[1].voltage * readingsArray[1].current) : 0.0f;
  features.count_all = prev_count + 1;
  features.i_v_ratio = (readingsArray[0].voltage != 0.0f) ? (readingsArray[0].current / readingsArray[0].voltage) : 0.0f;

  return features;
}

// ============================================================================
// MAIN PROGRAM
// ============================================================================

void setup()
{
  Serial.begin(115200);
  initSensors();
  initSafetyRelay();

  // watchdog sanity-checking
  pinMode(2, INPUT);           // WATCH_IN (from Backup)
  pinMode(3, OUTPUT);          // WATCH_OUT (to Backup)
  lastBackupSignal = millis(); // Initialize timer
}

void loop()
{
  unsigned long now = millis();
  int currentWatchdogState = digitalRead(PIN_FROM_SPARE);

  // ============================================================================
  // WATCHDOG SECTION (Consolidated)
  // ============================================================================
  // Part A: Response (The "Heartbeat Echo")
  if (currentWatchdogState == HIGH && lastWatchdogState == LOW)
  {
    digitalWrite(PIN_TO_SPARE, HIGH);
    // Use a very tiny delay for the pulse
    delayMicroseconds(500);
    digitalWrite(PIN_TO_SPARE, LOW);

    lastBackupSignal = now;

    if (backupWarningActive)
    {
      Serial.println(F("SYSTEM RESTORED: Backup signal detected."));
      backupWarningActive = false;
    }
  }
  // IMPORTANT: Only update this ONCE at the very end of the watchdog logic
  lastWatchdogState = currentWatchdogState;

  // Part B: Warning (The "Silence Detector")
  if (now - lastBackupSignal > TIMEOUT_LIMIT)
  {
    if (!backupWarningActive)
    {
      Serial.println(F("WARNING: Backup Arduino Heartbeat Lost!"));
      backupWarningActive = true;
    }
  }

  // ============================================================================
  // SENSOR & INFERENCE SECTION (1Hz)
  // ============================================================================
  if (now - lastSampleTime >= sampling_period)
  {
    lastSampleTime = now;

    SensorReadings r = getHardwareReadings();

    // Shift array
    for (int j = 9; j > 0; --j)
      readingsArray[j] = readingsArray[j - 1];
    readingsArray[0] = r;

    float current_temp = votedTemperature(r.temp1, r.temp2, r.temp3);
    // spare_code.ino and main .ino
    checkThermalSafety(current_temp, r.current, r.voltage); // float current_temp = (readings[0].temp1 + readings[0].temp2 + readings[0].temp3) / 3.0f;
  }
}