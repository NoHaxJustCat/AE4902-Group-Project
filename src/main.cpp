#include <Arduino.h>
#include <sensors.h>

static unsigned long sampling_period = 0;
SensorReadings readingsArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int index = 0;
static Features lastFeatures = {0};              // store previous features across iterations

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(A0)); // seed RNG from floating analog pin
  int sampling_freq = 1; // Hz
  sampling_period = 1000UL / sampling_freq; // ms
}

void loop() {
  static unsigned long last = 0;
  unsigned long now = millis();
  if (now - last >= sampling_period) {
    last = now;
    SensorReadings r = getSensorsReadings();
    for (int i = 9; i > 0; --i) readingsArray[i] = readingsArray[i - 1];
    readingsArray[0] = r;

    // pass lastFeatures (zero-initialized on first call)
    Features f = getFeatures(readingsArray, lastFeatures, index);

    serialPrintReadings(r, f);
    
    lastFeatures = f;   // save for next iteration
    ++index;            // increment sample counter AFTER using it
  }
}

float computeArrayMean(float arr[], int size) {
  if (size <= 0) return 0.0f;            // avoid divide-by-zero / invalid means
  float sum = 0.0f;
  for (int i = 0; i < size; ++i) {
    sum += arr[i];
  }
  return sum / size;
}

Features getFeatures(SensorReadings readingsArray[], Features oldFeatures, int i) {
  Features features;
  features.time = millis() / 1000.0f;
  features.capacity = 100.0f;
  features.temperature = (readingsArray[0].temp1 + readingsArray[0].temp2 + readingsArray[0].temp3) / 3.0f;

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