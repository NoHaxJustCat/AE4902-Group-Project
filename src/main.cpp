#include <Arduino.h>
#include "sensors.h"

// --- Random forest model inclusion (CHANGED) ---
#ifdef USE_RF_ON_DEVICE
#include "random_forest.h"
static Eloquent::ML::Port::RandomForestRegressor rf_model;  // single instance
#endif
// --- end change ---

// --- Main application code ---
static unsigned long sampling_period = 0;
SensorReadings readingsArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int index = 0;
static Features lastFeatures = {0};
static String cmdBuffer;

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 2000) {}

  int sampling_freq = 1; // Hz
  sampling_period = 1000UL / sampling_freq; // ms
}

static void processSerialLine(String line) {
  line.trim();
  if (line.length() == 0) return;

  String cmd = line; cmd.toLowerCase();
  Serial.print("Unknown command: "); Serial.println(line);
}

#include "utils.h"

// Enable on-device ML prediction only when explicitly requested via build flag:
#ifdef USE_RF_ON_DEVICE
#if defined(__AVR__) && (defined(ARDUINO_AVR_UNO) || defined(__AVR_ATmega328P__))
#warning "USE_RF_ON_DEVICE on AVR Uno may overflow flash. Prefer host-side prediction or bigger board."
#endif
#endif

static float calculateCapacity(SensorReadings readings[], Features oldFeatures, int i) {
  float cap_base = 0.0f;
  if (oldFeatures.count_all > 0) {
    cap_base = oldFeatures.capacity;
  } else {
    cap_base = (readings[0].voltage / 4.2f) * 100.0f;
  }

#ifdef USE_RF_ON_DEVICE
  float t = millis() / 1000.0f;
  float i_mean_all = (oldFeatures.count_all > 0) ? oldFeatures.i_mean_all : readings[0].current;
  float temp_meas = (readings[0].temp1 + readings[0].temp2 + readings[0].temp3) / 3.0f;

  float x[4] = { t, cap_base, i_mean_all, temp_meas };

  // --- Random forest usage (CHANGED) ---
  float cap_pred = rf_model.predict(x);
  // --- end change ---

  if (cap_pred < 0.0f) cap_pred = 0.0f;
  if (cap_pred > 100.0f) cap_pred = 100.0f;
  return cap_pred;
#else
  (void)i;
  return cap_base;
#endif
}

Features getFeatures(SensorReadings readingsArray[], Features oldFeatures, int i) {
  Features features;
  features.time = millis() / 1000.0f;
  features.capacity = calculateCapacity(readingsArray, oldFeatures, i);
  features.temperature = (readingsArray[0].temp1 + readingsArray[0].temp2 + readingsArray[0].temp3) / 3.0f;
  features.voted_temperature = votedTemperature(readingsArray[0].temp1, readingsArray[0].temp2, readingsArray[0].temp3);

  int prev_count = (i > 0) ? i : 0;
  int new_count = prev_count + 1;

  if (prev_count == 0 || oldFeatures.count_all <= 0) {
    features.i_mean_all = readingsArray[0].current;
    features.v_mean_all = readingsArray[0].voltage;
  } else {
    features.i_mean_all = (oldFeatures.i_mean_all * prev_count + readingsArray[0].current) / (prev_count + 1);
    features.v_mean_all = (oldFeatures.v_mean_all * prev_count + readingsArray[0].voltage) / (prev_count + 1);
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

  features.i_v_ratio_10 = computeArrayMean(iv, iv_count);
  features.power_mean_10 = computeArrayMean(power_vals, power_count);

  features.power_prev = (prev_count >= 1) ? (readingsArray[1].voltage * readingsArray[1].current) : 0.0f;

  features.count_all = new_count;
  features.i_v_ratio = (readingsArray[0].voltage != 0.0f) ? (readingsArray[0].current / readingsArray[0].voltage) : 0.0f;
  return features;
}

void loop() {
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
      if (cmdBuffer.length() > 128) cmdBuffer = cmdBuffer.substring(0, 128);
    }
  }

  static unsigned long last = 0;
  unsigned long now = millis();
  if (now - last >= sampling_period) {
    last = now;
    SensorReadings r = getHardwareReadings();
    for (int i = 9; i > 0; --i) readingsArray[i] = readingsArray[i - 1];
    readingsArray[0] = r;

    Features f = getFeatures(readingsArray, lastFeatures, index);
    serialPrintReadings(r, f);

    lastFeatures = f;
    ++index;
  }
}