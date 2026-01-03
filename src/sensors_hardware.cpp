#include "sensors_hardware.h"
#include <Arduino.h>

// --- configurable hardware mapping & ADC params (kept here) ---
static uint8_t g_pin_temp1 = A0;
static uint8_t g_pin_temp2 = A1;
static uint8_t g_pin_temp3 = A2;
static uint8_t g_pin_voltage = A3;
static uint8_t g_pin_current = A4;
static float g_adc_vref = 3.3f;
static int g_adc_resolution = 1024; // typical 10-bit boards
static float g_voltage_scale = 1.0f; // divider/mapping to real voltage
static float g_current_scale = 1.0f; // mapping from ADC voltage to current

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

SensorReadings getHardwareReadings() {
  SensorReadings s;
  s.temp1 = readTempFromAnalog(g_pin_temp1);
  s.temp2 = readTempFromAnalog(g_pin_temp2);
  s.temp3 = readTempFromAnalog(g_pin_temp3);
  s.voltage = readVoltageFromAnalog(g_pin_voltage);
  s.current = readCurrentFromAnalog(g_pin_current);
  return s;
}

void setAnalogPins(uint8_t temp1Pin, uint8_t temp2Pin, uint8_t temp3Pin, uint8_t voltagePin, uint8_t currentPin) {
  g_pin_temp1 = temp1Pin; g_pin_temp2 = temp2Pin; g_pin_temp3 = temp3Pin;
  g_pin_voltage = voltagePin; g_pin_current = currentPin;
}
void setADCParameters(float vref, int resolution) { g_adc_vref = vref; g_adc_resolution = resolution; }
void setVoltageScaling(float scale) { g_voltage_scale = scale; }
void setCurrentScaling(float scale) { g_current_scale = scale; }
