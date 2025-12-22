#include <math.h>
#include <Arduino.h>
#include "sensors.h"

SensorReadings getSensorsReadings() {
  SensorReadings s;
  s.temp1 = whiteNoise(19.0f, 0.5f);
  s.temp2 = whiteNoise(19.0f, 0.5f);
  s.temp3 = whiteNoise(19.0f, 0.5f);
  s.voltage = whiteNoise(3.3f, 0.1f);
  s.current = whiteNoise(0.004f, 0.0005f);
  return s;
}

float whiteNoise(float mean, float stddev) {
  if (stddev <= 0.0f) return mean;
  const long N = 1000000L;
  float u1 = random(1, N) / (float)N;
  float u2 = random(0, N) / (float)N;
  float z0 = sqrtf(-2.0f * logf(u1)) * cosf(2.0f * PI * u2);
  return mean + z0 * stddev;
};

void serialPrintReadings(SensorReadings r, Features f) {
    // Aggiungi questo nel loop dopo aver calcolato 'f'
    Serial.print(r.temp1); Serial.print(",");
    Serial.print(r.temp2); Serial.print(",");
    Serial.print(r.temp3); Serial.print(",");
    Serial.print(r.voltage); Serial.print(",");
    Serial.print(r.current); Serial.print(",");
    Serial.print(f.temperature); Serial.print(",");
    Serial.print(f.i_mean_all); Serial.print(",");
    Serial.print(f.v_mean_all); Serial.print(",");
    Serial.print(f.i_v_ratio_10); Serial.print(",");
    Serial.print(f.power_mean_10); Serial.print(",");
    Serial.println(f.power_prev);
}