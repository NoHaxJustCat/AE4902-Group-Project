#pragma once
#include <Arduino.h>
#include "sensors.h"

// Thin public API for the internal SensorSimulator implementation.
// This header exposes only the functions used by the rest of the codebase
// and keeps the heavy implementation details in `sensors_simulator.cpp`.

// Initialize simulator RNG/state
void initSensorSimulator(uint32_t seed = 0);

// Read a simulated set of sensor measurements
SensorReadings getSimulatorReadings();

// Scenario / injection helpers
void setSimulationScenario(SimScenario s);
void simInjectSpike(float amplitude, unsigned long duration_ms);
void simInjectSensorSpike(int sensorIndex, float amplitude, unsigned long duration_ms);

// Automatic probabilities (system-level)
void setAutoProbabilities(float spikeProbPerSec, float faultProbPerSec, float glitchProbPerSec, float pulseProbPerSec);

// Per-sensor automatic event probabilities (sensorIndex: 0..4)
void setPerSensorAutoProbabilities(int sensorIndex, float spikeProbPerSec, float faultProbPerSec, float glitchProbPerSec, float pulseProbPerSec);

// Query the current active scenario
SimScenario getSimulationScenario();

// Small helper exposed for deterministic noise when desired
float simulatorGaussian(float mean, float stddev);

// white noise helper (calls simulator RNG when available)
float whiteNoise(float mean, float stddev);
