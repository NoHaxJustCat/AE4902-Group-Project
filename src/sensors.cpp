#include <math.h>
#include <Arduino.h>
#include "sensors.h"

// --- configurable hardware mapping & ADC params ---
static uint8_t g_pin_temp1 = A0;
static uint8_t g_pin_temp2 = A1;
static uint8_t g_pin_temp3 = A2;
static uint8_t g_pin_voltage = A3;
static uint8_t g_pin_current = A4;
static float g_adc_vref = 3.3f;
static int g_adc_resolution = 1024; // supply (use 1024 for 10-bit boards => raw in [0..1023])
static float g_voltage_scale = 1.0f; // divider/mapping to real voltage
static float g_current_scale = 1.0f; // mapping from ADC voltage to current

// current sensor/hardware mode flag
static SensorMode g_sensorMode = SENSOR_MODE_SIMULATION;

// Simulator implementation moved to separate module
#include "sensors_simulator.h"

// Hardware and fault modules are in their own files
#include "sensors_hardware.h"
#include "faults.h"
#include "utils.h"

// --- hardware helpers ---
static inline float analogToVoltage(int raw) {
  int maxRaw = (g_adc_resolution > 1) ? (g_adc_resolution - 1) : 1023;
  return (raw / (float)maxRaw) * g_adc_vref;
}

static float readTempFromAnalog(uint8_t pin) {
  // Default mapping: LM35-like (10 mV/°C). Adjust with calibration as needed.
  int raw = analogRead(pin);
  float v = analogToVoltage(raw);
  return v * 100.0f; // 0.01 V/°C => multiply by 100
}

static float readVoltageFromAnalog(uint8_t pin) {
  int raw = analogRead(pin);
  float v = analogToVoltage(raw) * g_voltage_scale;
  return v;
}

static float readCurrentFromAnalog(uint8_t pin) {
  int raw = analogRead(pin);
  float v = analogToVoltage(raw);
  return v * g_current_scale; // user can calibrate
}

// --- API implementations ---
SensorReadings getSensorsReadings() {
  SensorReadings s = (g_sensorMode == SENSOR_MODE_SIMULATION) ? getSimulatorReadings() : getHardwareReadings();

  // allow faults to be applied by the faults module (in-place)
  applyFaults(s);
  return s;
}

void setSensorMode(SensorMode mode) { g_sensorMode = mode; }
SensorMode getSensorMode() { return g_sensorMode; }

void serialPrintReadings(SensorReadings r, Features f) {
    Serial.print("DATA,");
    const int PREC = 6; // number of decimals for printed floats (cleaner, consistent output)
    Serial.print(r.temp1, PREC); Serial.print(",");
    Serial.print(r.temp2, PREC); Serial.print(",");
    Serial.print(r.temp3, PREC); Serial.print(",");
    Serial.print(r.voltage, PREC); Serial.print(",");
    Serial.print(r.current, PREC); Serial.print(",");
    Serial.print(f.temperature, PREC); Serial.print(",");
    Serial.print(f.voted_temperature, PREC); Serial.print(",");
    Serial.print(f.i_mean_all, PREC); Serial.print(",");
    Serial.print(f.v_mean_all, PREC); Serial.print(",");
    Serial.print(f.i_v_ratio_10, PREC); Serial.print(",");
    Serial.print(f.power_mean_10, PREC); Serial.print(",");
    Serial.print(f.power_prev, PREC); Serial.print(",");
    Serial.println(f.capacity, PREC);
}