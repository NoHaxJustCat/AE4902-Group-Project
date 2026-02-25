#pragma once
#include <Arduino.h>

struct SensorReadings
{
  float temp1;
  float temp2;
  float temp3;
  float voltage;
  float current;
};

struct Features
{
  float time;
  float capacity;
  float temperature;
  float voted_temperature; // decided via triple-redundancy voter (average of two nearest)
  float i_mean_all;
  float i_v_ratio_10;
  float v_mean_all;
  float power_mean_10;
  float count_all;
  float power_prev;
  float i_v_ratio;
};

// Hardware initialization
void initSensors();

// Hardware reading
SensorReadings getHardwareReadings();

// Hardware mapping helpers (kept for API compatibility - not used with INA219/TMP36)

// make getFeatures visible to other translation units
Features getFeatures(SensorReadings readingsArray[], Features oldFeatures, int i);
void serialPrintReadings(SensorReadings r, float current_temp, float capacity);