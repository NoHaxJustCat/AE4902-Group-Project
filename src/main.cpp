#include <Arduino.h>
#include <sensors.h>
#include "faults.h"

// --- Main application code ---
// define global/static variables for main, readings array
static unsigned long sampling_period = 0;
SensorReadings readingsArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int index = 0;
static Features lastFeatures = {0};              // store previous features across iterations
static String cmdBuffer; // buffer for incoming serial text lines

void setup() {
  // initialize Serial
  Serial.begin(115200);
  while (!Serial && millis() < 2000) {} // brief wait for Serial on some boards

  // seed RNG (simulation uses its own RNG)
  randomSeed(analogRead(A0)); // seed RNG from floating analog pin
  initSensorSimulator(analogRead(A0) ^ (unsigned long)micros()); // deterministic-ish seed for sim

  // HARD-CODED MODE: choose simulation or hardware readings here (no console toggles)
  static const bool kUseSimulation = true; // <-- set to `false` to use hardware ADC reads
  setSensorMode(kUseSimulation ? SENSOR_MODE_SIMULATION : SENSOR_MODE_HARDWARE);

  // Fault modes (hardcoded): perfect vs faulty (probabilities per-sensor)
  static const bool kFaultyMode = false; // set to `false` for perfect (no auto faults)

  // Example per-sensor probabilities (for 5 sensors: temp1,temp2,temp3,voltage,current)
  // Values are probabilities per second for each event type when in SIM_AUTO
  static const float per_spike_prob[5] = {0.02f, 0.02f, 0.02f, 0.01f, 0.015f};
  static const float per_fault_prob[5] = {0.001f, 0.001f, 0.001f, 0.0005f, 0.0007f};
  static const float per_glitch_prob[5] = {0.005f, 0.005f, 0.005f, 0.003f, 0.004f};
  static const float per_pulse_prob[5] = {0.002f, 0.002f, 0.002f, 0.001f, 0.0015f};

  // Configure simulator/system-level and per-sensor probabilities depending on mode
  if (kUseSimulation) {
    setSimulationScenario(SIM_AUTO);
    if (kFaultyMode) {
      // keep some system-level background probabilities (minor)
      setAutoProbabilities(0.002f, 0.001f, 0.0005f, 0.005f);
      for (int s = 0; s < 5; ++s) setPerSensorAutoProbabilities(s, per_spike_prob[s], per_fault_prob[s], per_glitch_prob[s], per_pulse_prob[s]);
    } else {
      // perfect simulation: disable all auto events
      setAutoProbabilities(0.0f, 0.0f, 0.0f, 0.0f);
      for (int s = 0; s < 5; ++s) setPerSensorAutoProbabilities(s, 0.0f, 0.0f, 0.0f, 0.0f);
    }
  }

  Serial.print("Starting: "); Serial.println(kUseSimulation ? (kFaultyMode ? "SIMULATION (FAULTY)" : "SIMULATION (PERFECT)") : "HARDWARE (hardcoded)");
  Serial.println("Console controls for switching modes/scenarios have been removed. Use code to change mode.");

  int sampling_freq = 1; // Hz
  sampling_period = 1000UL / sampling_freq; // ms
}

static const char* scenarioToString(SimScenario s) {
  switch (s) {
    case SIM_NORMAL: return "NORMAL";
    case SIM_PULSE:  return "PULSE";
    case SIM_SPIKE:  return "SPIKE";
    case SIM_FAULTY: return "FAULTY";
    case SIM_AUTO:   return "AUTO";
    default: return "UNKNOWN";
  }
}

static const char* modeToString(SensorMode m) {
  return (m == SENSOR_MODE_HARDWARE) ? "HARDWARE" : "SIMULATION";
}

static void processSerialLine(String line) {
  line.trim();
  if (line.length() == 0) return;

  // Note: interactive simulation/scenario/fault commands removed.
  // Only minimal console support remains (e.g., 'status').
  String cmd = line; cmd.toLowerCase();

  if (cmd.equals("status")) {
    Serial.print("Sensor mode: "); Serial.println(modeToString(getSensorMode()));
    Serial.print("Simulation scenario: "); Serial.println(scenarioToString(getSimulationScenario()));
    return;
  }

  // Fault commands removed from console (use programmatic APIs).

  Serial.print("Unknown command: "); Serial.println(line);
}

#include "utils.h" // computeArrayMean and helpers
// Enable on-device ML prediction only when explicitly requested via build flag:
#ifdef USE_RF_ON_DEVICE
#include "capacity_calculator.h"
#if defined(__AVR__) && (defined(ARDUINO_AVR_UNO) || defined(__AVR_ATmega328P__))
#warning "USE_RF_ON_DEVICE on AVR Uno may overflow flash. Prefer host-side prediction or bigger board."
#endif
#endif

// Simple capacity calculator: if we have a previous capacity value, return it;
// otherwise estimate capacity from measured voltage (assumes nominal full voltage ~= 4.2V).
static float calculateCapacity(SensorReadings readings[], Features oldFeatures, int i) {
  // base estimate (previous value or voltage-based)
  float cap_base = 0.0f;
  if (oldFeatures.count_all > 0) {
    cap_base = oldFeatures.capacity;
  } else {
    float v = readings[0].voltage;
    if (v <= 0.0f) cap_base = 0.0f;
    else cap_base = (v / 4.2f) * 100.0f;
  }

#ifdef USE_RF_ON_DEVICE
  // prepare feature vector: Time, capacity (base), I_mean_all, Temperature_measured
  float t = millis() / 1000.0f;
  float i_mean_all = (oldFeatures.count_all > 0) ? oldFeatures.i_mean_all : readings[0].current;
  float temp_meas = (readings[0].temp1 + readings[0].temp2 + readings[0].temp3) / 3.0f;
  Eloquent::ML::Port::RandomForestRegressor rf;
  float x[4] = { t, cap_base, i_mean_all, temp_meas };
  float cap_pred = rf.predict(x);
  if (cap_pred < 0.0f) cap_pred = 0.0f;
  if (cap_pred > 100.0f) cap_pred = 100.0f;
  return cap_pred;
#else
  // fallback, unchanged behavior
  if (cap_base < 0.0f) cap_base = 0.0f;
  if (cap_base > 100.0f) cap_base = 100.0f;
  return cap_base;
#endif
}

Features getFeatures(SensorReadings readingsArray[], Features oldFeatures, int i) {
  Features features;
  features.time = millis() / 1000.0f;
  // compute capacity using capacity calculator (replace with real signature if different)
  features.capacity = calculateCapacity(readingsArray, oldFeatures, i);
  features.temperature = (readingsArray[0].temp1 + readingsArray[0].temp2 + readingsArray[0].temp3) / 3.0f;
  // decide voted temperature using triple redundancy voter (average of the two closest temps)
  features.voted_temperature = votedTemperature(readingsArray[0].temp1, readingsArray[0].temp2, readingsArray[0].temp3);

  int prev_count = (i > 0) ? i : 0;      // treat negative/zero i as "no previous samples"
  int new_count = prev_count + 1;

  // handle first iteration (no previous features) safely
  if (prev_count == 0 || oldFeatures.count_all <= 0) {
    features.i_mean_all = readingsArray[0].current;
    features.v_mean_all = readingsArray[0].voltage;
  } else {
    features.i_mean_all = (oldFeatures.i_mean_all * prev_count + readingsArray[0].current) / (prev_count + 1);
    features.v_mean_all = (oldFeatures.v_mean_all * prev_count + readingsArray[0].voltage) / (prev_count + 1);
  }

  // compute iv and power means using only available valid samples (up to 10)
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
  features.i_v_ratio_10 = computeArrayMean(iv, iv_count);
  features.power_mean_10 = computeArrayMean(power_vals, power_count);

  // previous power only valid if we have at least one previous sample
  features.power_prev = (prev_count >= 1) ? (readingsArray[1].voltage * readingsArray[1].current) : 0.0f;

  features.count_all = new_count;
  features.i_v_ratio = (readingsArray[0].voltage != 0.0f) ? (readingsArray[0].current / readingsArray[0].voltage) : 0.0f;
  return features;
}

// ML prediction removed from device (run on host instead if needed)

void loop() {
  // read incoming serial lines non-blocking and process them
  while (Serial.available()) {
    char ch = Serial.read();
    if (ch == '\r') continue;
    if (ch == '\n') {
      if (cmdBuffer.length() > 0) {
        processSerialLine(cmdBuffer);
        cmdBuffer = "";
      }
    } else {
      cmdBuffer += ch;
      if (cmdBuffer.length() > 128) cmdBuffer = cmdBuffer.substring(0, 128); // cap buffer
    }
  }

  static unsigned long last = 0;
  unsigned long now = millis();
  if (now - last >= sampling_period) {
    last = now;
    SensorReadings r = getSensorsReadings();
    for (int i = 9; i > 0; --i) readingsArray[i] = readingsArray[i - 1];
    readingsArray[0] = r;

    // pass lastFeatures (zero-initialized on first call)
    Features f = getFeatures(readingsArray, lastFeatures, index);

    // print a single DATA line (serialPrintReadings already includes capacity)
    serialPrintReadings(r, f);
 
     lastFeatures = f;   // save for next iteration
     ++index;            // increment sample counter AFTER using it
   }
 }