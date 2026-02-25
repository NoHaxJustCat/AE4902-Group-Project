#include <math.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include "sensors.h"
#include "utils.h"

// --- Hardware objects ---
static Adafruit_INA219 ina219;         // Default Address 0x40
static Adafruit_INA219 ina219_b(0x41); // Address 0x44 (A1 soldered)

static bool inaOk = false;
static bool inabOk = false;

static float voltage1 = 0;
static float voltage2 = 0;
static float current1 = 0;
static float current2 = 0;
// --- Redundancy / Safety Settings ---
static const uint8_t ALERT_PIN = 4;       // Pin to trigger on mismatch
static const float MAX_VOLT_DELTA = 0.5;  // Max allowed voltage difference (Volts)
static const float MAX_CURR_DELTA = 20.0; // Max allowed current difference (mA)
static bool sensorMismatch = false;       // Flag to track mismatch status

// --- Pin definitions for temperature sensors ---
static const uint8_t tempPin1 = A0;
static const uint8_t tempPin2 = A2;
static const uint8_t tempPin3 = A3;

// --- Helper function for averaged current reading ---
static float getAverageCurrent(uint8_t samples = 10)
{
  if (!inaOk)
    return 0.0f;
  float sum = 0;
  for (uint8_t i = 0; i < samples; i++)
  {
    sum += ina219.getCurrent_mA();
    delay(5);
  }
  return sum / samples;
}

// --- Temperature reading from TMP36 sensor ---
static float readTMP36(uint8_t pin)
{
  int raw = analogRead(pin);
  float voltage = raw * (5.0 / 1023.0);         // Convert to voltage (5V reference)
  float temperatureC = (voltage - 0.5) * 100.0; // TMP36 formula
  return temperatureC;
}

// --- Initialize hardware sensors ---
void initSensors()
{
  Wire.begin();

  // Setup Alert Pin
  pinMode(ALERT_PIN, OUTPUT);
  digitalWrite(ALERT_PIN, LOW);

  inaOk = ina219.begin();
  inabOk = ina219_b.begin();

  if (!inaOk && !inabOk)
  {
    Serial.println("ERROR: Neither INA219 detected. Check wiring and I2C address.");
  }
  else if (!inaOk)
  {
    Serial.println("ERROR: First INA219 not detected. Check wiring and I2C address.");
  }
  else if (!inabOk)
  {
    Serial.println("ERROR: Second INA219 not detected. Check wiring and I2C address.");
  }
  else
  {
    ina219.setCalibration_16V_400mA();
    ina219_b.setCalibration_16V_400mA();
    Serial.println(" INA219 Initialized (16V/400mA Range)");
  }
}

// --- Main hardware reading function ---
SensorReadings getHardwareReadings()
{
  SensorReadings r;

  // Read three TMP36 temperature sensors
  r.temp1 = readTMP36(tempPin1); // A1
  r.temp2 = readTMP36(tempPin2); // A2
  r.temp3 = readTMP36(tempPin3); // A3

  // Read voltage and current from INA219
  if (inaOk)
  {
    voltage1 = ina219.getBusVoltage_V(); // Voltage in Volts
    current1 = ina219.getCurrent_mA();   // Current in Amperes (converted from mA)
  }
  else
  {
    Serial.print("WARNING: INA sensor 1 is OFFLINE");
    voltage1 = 0.0f;
    current1 = 0.0f;
  }
  if (inabOk)
  {
    voltage2 = ina219_b.getBusVoltage_V(); // Voltage in Volts
    current2 = ina219_b.getCurrent_mA();   // Current in Amperes (converted from mA)
  }
  else
  {
    Serial.print("WARNING: INA sensor 2 is OFFLINE");
    voltage2 = 0.0f;
    current2 = 0.0f;
  }
  r.voltage = 2 * voltage1 + 2 * voltage2;
  r.current = current1 + current2;
  // --- Redundancy Check Logic ---
  // Only check if both sensors are actually online
  if (inaOk && inabOk)
  {
    r.voltage = r.voltage / 2.0f;
    r.current = r.current / 2.0f;

    float voltageDelta = abs(voltage1 - voltage2);
    float currentDelta = abs(current1 - current2);

    if (voltageDelta > MAX_VOLT_DELTA || currentDelta > MAX_CURR_DELTA)
    {
      // Sensors disagree — check if the hardware pin already reflects this
      if (digitalRead(ALERT_PIN) == LOW)
      {
        // Pin was LOW but mismatch just appeared — genuine new mismatch
        sensorMismatch = true;
        digitalWrite(ALERT_PIN, HIGH);
        Serial.println(F("====================================================="));
        Serial.println(F("WARNING: INA219 SENSORS ARE READING DIFFERENT VALUES!"));
        Serial.println(F("====================================================="));
        Serial.println(F("Using Sensor Average"));
      }
      // If pin is already HIGH, mismatch is ongoing — no new action needed
    }
    else
    {
      // Sensors agree — check if the pin is still HIGH
      if (digitalRead(ALERT_PIN) == HIGH)
      {
        // Pin is HIGH but sensors now agree — something flipped the pin unexpectedly
        Serial.println(F("BIT FLIP DETECTED on ALERT_PIN — clearing."));
        sensorMismatch = false;
        digitalWrite(ALERT_PIN, LOW);
      }
    }
  }

  return r;
}

// --- Stub functions (kept for API compatibility, do nothing) ---
void setAnalogPins(uint8_t temp1Pin, uint8_t temp2Pin, uint8_t temp3Pin,
                   uint8_t voltagePin, uint8_t currentPin)
{
  // Not used with hardware sensors
}

void setADCParameters(float vref, int resolution)
{
  // Not used with hardware sensors
}

void setVoltageScaling(float scale)
{
  // Not used with hardware sensors
}

void setCurrentScaling(float scale)
{
  // Not used with hardware sensors
}

// --- Serial output function ---
void serialPrintReadings(SensorReadings r, float current_temp, float capacity)
{
  // Build the payload into a buffer so we can compute its CRC
  // Max field: sign + digits + '.' + 6 decimals ≈ 14 chars  × 13 fields + commas + "DATA," + margin
  char buf[256];
  const int PREC = 6;
  int pos = 0;

  pos += snprintf(buf + pos, sizeof(buf) - pos, "DATA,");
  pos += snprintf(buf + pos, sizeof(buf) - pos, "%s,", String(r.temp1, PREC).c_str());
  pos += snprintf(buf + pos, sizeof(buf) - pos, "%s,", String(r.temp2, PREC).c_str());
  pos += snprintf(buf + pos, sizeof(buf) - pos, "%s,", String(r.temp3, PREC).c_str());
  pos += snprintf(buf + pos, sizeof(buf) - pos, "%s,", String(r.voltage, PREC).c_str());
  pos += snprintf(buf + pos, sizeof(buf) - pos, "%s,", String(r.current, PREC).c_str());
  pos += snprintf(buf + pos, sizeof(buf) - pos, "%s,", String(current_temp, PREC).c_str());
  pos += snprintf(buf + pos, sizeof(buf) - pos, "%s", String(capacity, PREC).c_str());

  // Compute CRC-16 over the payload and append as *XXXX
  uint16_t crc = crc16_ccitt(buf, pos);
  snprintf(buf + pos, sizeof(buf) - pos, "*%04X", crc);

  Serial.println(buf);
}