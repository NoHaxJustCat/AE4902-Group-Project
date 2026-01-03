#pragma once
#include "sensors.h"

// Fault types that can be applied to individual measurements
enum FaultType { FAULT_NONE = 0, FAULT_STUCK = 1, FAULT_NOISY = 2, FAULT_OFFSET = 3 };

// Inject a fault on a single sensor (index: 0=temp1,1=temp2,2=temp3,3=voltage,4=current)
void injectSensorFault(int sensorIndex, FaultType type, float amp, unsigned long duration_ms);

// Apply any active faults to the given readings (in-place)
void applyFaults(SensorReadings &r);

// Global control
void enableFaults(bool enable);

// Clear all active faults
void clearAllFaults();
