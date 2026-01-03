#include "faults.h"
#include <Arduino.h>
#include "sensors.h"

struct FaultEntry {
  FaultType type;
  float amp;
  unsigned long until_ms;
};

static constexpr int N_SENS = 5;
static FaultEntry g_faults[N_SENS];
static bool g_enabled = true;

void enableFaults(bool enable) { g_enabled = enable; }
void clearAllFaults() { for (int i = 0; i < N_SENS; ++i) g_faults[i] = {FAULT_NONE, 0.0f, 0}; }

void injectSensorFault(int sensorIndex, FaultType type, float amp, unsigned long duration_ms) {
  if (sensorIndex < 0 || sensorIndex >= N_SENS) return;
  g_faults[sensorIndex].type = type;
  g_faults[sensorIndex].amp = amp;
  g_faults[sensorIndex].until_ms = millis() + duration_ms;
}

void applyFaults(SensorReadings &r) {
  if (!g_enabled) return;
  unsigned long now = millis();
  float *vals[5] = { &r.temp1, &r.temp2, &r.temp3, &r.voltage, &r.current };
  for (int i = 0; i < N_SENS; ++i) {
    if (g_faults[i].until_ms <= now) { // expired
      g_faults[i].type = FAULT_NONE;
      g_faults[i].amp = 0.0f;
      g_faults[i].until_ms = 0;
      continue;
    }
    switch (g_faults[i].type) {
      case FAULT_NONE: break;
      case FAULT_STUCK:
        // mark with sentinel invalid value
        *vals[i] = -999.0f; break;
      case FAULT_NOISY:
        *vals[i] += g_faults[i].amp * ((float) ( (int)micros() % 100 ) / 100.0f - 0.5f ); break;
      case FAULT_OFFSET:
        *vals[i] += g_faults[i].amp; break;
    }
  }
}
