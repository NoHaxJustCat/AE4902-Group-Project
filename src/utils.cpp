#include <Arduino.h>
#include <stdint.h>
#include <math.h>

// Hardware Pin
const uint8_t RELAY_PIN = A1; 

// Relay Logic (Most JQC3F modules are Active-Low)
#define RELAY_ON  HIGH
#define RELAY_OFF LOW

// --- Relay state ---
bool circuitOpen = false;
unsigned long relayTimestamp = 0;
static bool relayBroken = false;
static uint8_t relayRetries = 0;

// --- Timing & thresholds ---
const unsigned long COOL_DOWN_TIME = 5000;
const float TEMP_THRESHOLD    = 45.0f;
const float RELAY_CURRENT_THRESHOLD = 0.3f;    // mA — proves relay is still closed
const uint8_t MAX_RELAY_RETRIES = 3;

// --- Border value limits (NCR18650B datasheet) ---
const float MIN_VOLTAGE = 2.5f;     // V
const float MAX_VOLTAGE = 4.2f;     // V
const float MAX_CURRENT = 4875.0f;  // mA (4.875 A)

// --- Helper: engage relay with shared logic ---
static void engageRelay(unsigned long now) {
  digitalWrite(RELAY_PIN, RELAY_ON);
  circuitOpen = true;
  relayTimestamp = now;
  relayRetries = 0;
}

void initSafetyRelay() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // ensure it starts with closed circuit
}

float computeArrayMean(float arr[], int size) {
  if (size == 0) return 0.0f;
  float sum = 0.0f;
  for (int i = 0; i < size; i++) sum += arr[i];
  return sum / size;
}

void checkThermalSafety(float currentTemp, float measuredCurrent, float measuredVoltage) {
  unsigned long now = millis();

  // ----------------------------------------------------------------
  // Condition 1: Border value violations — trigger relay if not already open
  // ----------------------------------------------------------------
  if (!circuitOpen && !relayBroken) {

    if (currentTemp >= TEMP_THRESHOLD) {
      Serial.print(F("CRITICAL: Temp "));
      Serial.print(currentTemp);
      Serial.print(F("C exceeds threshold ("));
      Serial.print(TEMP_THRESHOLD);
      Serial.println(F("C). Relay ENGAGED."));
      engageRelay(now);
    }
    else if (measuredVoltage > MAX_VOLTAGE) {
      Serial.print(F("CRITICAL: Overvoltage detected ("));
      Serial.print(measuredVoltage);
      Serial.println(F("V). Relay ENGAGED."));
      engageRelay(now);
    }
    else if (measuredVoltage < MIN_VOLTAGE) {
      Serial.print(F("CRITICAL: Undervoltage detected ("));
      Serial.print(measuredVoltage);
      Serial.println(F("V). Relay ENGAGED."));
      engageRelay(now);
    }
    else if (measuredCurrent > MAX_CURRENT) {
      Serial.print(F("CRITICAL: Overcurrent detected ("));
      Serial.print(measuredCurrent);
      Serial.println(F("mA). Relay ENGAGED."));
      engageRelay(now);
    }
  }

  // ----------------------------------------------------------------
  // Condition 2: Circuit should be open — verify relay actually opened
  // ----------------------------------------------------------------
  if (circuitOpen) {
    if (abs(measuredCurrent) > RELAY_CURRENT_THRESHOLD) {
      // Current still flowing — relay did not open correctly
      relayTimestamp = now;  // Reset cooldown to prevent premature release
      relayRetries++;
      Serial.print(F("WARNING: Relay did not operate correctly. Retry "));
      Serial.print(relayRetries);
      Serial.print(F("/"));
      Serial.println(MAX_RELAY_RETRIES);

      digitalWrite(RELAY_PIN, RELAY_ON);  // Re-assert signal

      if (relayRetries >= MAX_RELAY_RETRIES) {
        relayBroken = true;
      }
    } else {
      // Current stopped — relay opened successfully, wait for cooldown
      if (now - relayTimestamp >= COOL_DOWN_TIME) {
        digitalWrite(RELAY_PIN, RELAY_OFF);
        circuitOpen = false;
        relayRetries = 0;
        Serial.println(F("INFO: Cooldown complete. Relay RELEASED (Circuit Closed)."));
      }
    }
  }

  // ----------------------------------------------------------------
  // Condition 3: Relay confirmed broken — warn every cycle
  // ----------------------------------------------------------------
  if (relayBroken && circuitOpen && abs(measuredCurrent) > RELAY_CURRENT_THRESHOLD) {
    Serial.println(F("CRITICAL: RELAY FAILURE CONFIRMED. Manual intervention required."));
  }
}

float votedTemperature(float t1, float t2, float t3) {
  const float MIN_TEMP = -50.0f;
  const float MAX_TEMP = 50.0f;
  const float maxDelta = 5.0f;

  float inputs[3] = { t1, t2, t3 };
  float valid[3]; 
  int validIdx[3];
  int vcount = 0;

  // 1. Range Validation (Sanity Check)
  for (int i = 0; i < 3; ++i) {
    if (inputs[i] >= MIN_TEMP && inputs[i] <= MAX_TEMP) {
      valid[vcount] = inputs[i];
      validIdx[vcount] = i + 1;
      vcount++;
    }
  }

  float d12 = fabsf(valid[0] - valid[1]);
  float d13 = fabsf(valid[0] - valid[2]);
  float d23 = fabsf(valid[1] - valid[2]);

  // 2. Voting Logic
  if (vcount == 3) {
    if (d12 > maxDelta || d13 > maxDelta || d23 > maxDelta) {
      if (d12 <= d13 && d12 <= d23) {
        Serial.println(F("FAULT: Sensor 3 deviation detected."));
        return (valid[0] + valid[1]) * 0.5f;
      } 
      else if (d13 <= d12 && d13 <= d23) {
        Serial.println(F("FAULT: Sensor 2 deviation detected."));
        return (valid[0] + valid[2]) * 0.5f;
      } 
      else {
        Serial.println(F("FAULT: Sensor 1 deviation detected."));
        return (valid[1] + valid[2]) * 0.5f;
      }
    } else {
      return (valid[0] + valid[1] + valid[2]) / 3.0f;
    }
  }

  if (vcount == 2) {
    if (fabsf(valid[0] - valid[1]) > maxDelta) {
      Serial.println(F("WARNING: High Delta between only remaining sensors."));
    }
    return (valid[0] + valid[1]) * 0.5f;
  }

  // vcount == 0 or 1 — check if any pair still agrees within delta
  if (d12 < maxDelta || d13 < maxDelta || d23 < maxDelta) {
    if (d12 <= d13 && d12 <= d23) {
      Serial.println(F("WARNING: High temperature!"));
      return (t1 + t2) * 0.5f;
    } 
    else if (d13 <= d12 && d13 <= d23) {
      Serial.println(F("WARNING: High temperature!"));
      return (t1 + t3) * 0.5f;
    } 
    else {
      Serial.println(F("WARNING: High temperature!"));
      return (t2 + t3) * 0.5f;
    }
  }

  if (vcount == 1) {
    Serial.println(F("WARNING: Sensors cannot agree on a value!"));
    Serial.print(F("Sensor 1: ")); Serial.println(t1);
    Serial.print(F("Sensor 2: ")); Serial.println(t2);
    Serial.print(F("Sensor 3: ")); Serial.println(t3);
  }

  return 100;
}

float clampf(float v, float lo, float hi) {
  if (v < lo) return lo; if (v > hi) return hi; return v;
}

uint16_t crc16_ccitt(const char *data, size_t len)
{
  uint16_t crc = 0xFFFF;
  for (size_t i = 0; i < len; i++)
  {
    crc ^= ((uint16_t)(uint8_t)data[i]) << 8;
    for (uint8_t b = 0; b < 8; b++)
    {
      if (crc & 0x8000)
        crc = (crc << 1) ^ 0x1021;
      else
        crc <<= 1;
    }
  }
  return crc;
}
