#include <math.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include "sensors.h"
#include "utils.h"

// --- Hardware objects ---
static Adafruit_INA219 ina219;
static bool inaOk = false;

// --- Pin definitions for temperature sensors ---
static const uint8_t tempPin1 = A1;
static const uint8_t tempPin2 = A2;
static const uint8_t tempPin3 = A3;

// --- Helper function for averaged current reading ---
static float getAverageCurrent(uint8_t samples = 10) {
  if (!inaOk) return 0.0f;
  float sum = 0;
  for (uint8_t i = 0; i < samples; i++) {
    sum += ina219.getCurrent_mA();
    delay(5);
  }
  return sum / samples;
}

// --- Temperature reading from TMP36 sensor ---
static float readTMP36(uint8_t pin) {
  int raw = analogRead(pin);
  float voltage = raw * (5.0 / 1023.0);  // Convert to voltage (5V reference)
  float temperatureC = (voltage - 0.5) * 100.0;  // TMP36 formula
  return temperatureC;
}

// --- Initialize hardware sensors ---
void initSensors() {
  Wire.begin();
  
  inaOk = ina219.begin();
  
  if (!inaOk) {
    Serial.println("ERROR: INA219 not detected. Check wiring and I2C address.");
  } else {
    ina219.setCalibration_16V_400mA();
    Serial.println("INA219 Initialized (16V/400mA Range)");
  }
}

// --- Main hardware reading function ---
SensorReadings getHardwareReadings() {
  SensorReadings r;
  
  // Read three TMP36 temperature sensors
  r.temp1 = readTMP36(tempPin1);  // A1
  r.temp2 = readTMP36(tempPin2);  // A2
  r.temp3 = readTMP36(tempPin3);  // A3
  
  // Read voltage and current from INA219
  if (inaOk) {
    r.voltage = ina219.getBusVoltage_V();           // Voltage in Volts
    r.current = getAverageCurrent(10) / 1000.0f;    // Current in Amperes (converted from mA)
  } else {
    r.voltage = 0.0f;
    r.current = 0.0f;
  }
  
  return r;
}

// --- Stub functions (kept for API compatibility, do nothing) ---
void setAnalogPins(uint8_t temp1Pin, uint8_t temp2Pin, uint8_t temp3Pin, 
                   uint8_t voltagePin, uint8_t currentPin) {
  // Not used with hardware sensors
}

void setADCParameters(float vref, int resolution) {
  // Not used with hardware sensors
}

void setVoltageScaling(float scale) {
  // Not used with hardware sensors
}

void setCurrentScaling(float scale) {
  // Not used with hardware sensors
}

// --- Serial output function ---
void serialPrintReadings(SensorReadings r, Features f) {
  Serial.print("DATA,");
  const int PREC = 6;
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