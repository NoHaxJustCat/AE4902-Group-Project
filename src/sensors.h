#pragma once
#include <Arduino.h>

struct SensorReadings {
  float temp1;
  float temp2;
  float temp3;
  float voltage;
  float current;
};

struct Features {
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

// New enums for mode / scenarios
enum SensorMode { SENSOR_MODE_SIMULATION = 0, SENSOR_MODE_HARDWARE = 1 };
enum SimScenario { SIM_NORMAL = 0, SIM_PULSE = 1, SIM_SPIKE = 2, SIM_FAULTY = 3, SIM_AUTO = 4 };

SensorReadings getSensorsReadings();
float whiteNoise(float mean, float stddev);

// Simulation control / configuration
void initSensorSimulator(uint32_t seed = 0);
void setSensorMode(SensorMode mode);
SensorMode getSensorMode();
void setSimulationScenario(SimScenario s);
void simInjectSpike(float amplitude, unsigned long duration_ms);

// Automatic / probabilistic event parameters (probabilities are per-second)
void setAutoProbabilities(float spikeProbPerSec, float faultProbPerSec, float glitchProbPerSec, float pulseProbPerSec);

// Per-sensor automatic event probabilities (sensorIndex: 0..4)
void setPerSensorAutoProbabilities(int sensorIndex, float spikeProbPerSec, float faultProbPerSec, float glitchProbPerSec, float pulseProbPerSec);

// per-sensor injection helper (sensorIndex: 0=temp1,1=temp2,2=temp3,3=voltage,4=current)
void simInjectSensorSpike(int sensorIndex, float amplitude, unsigned long duration_ms);

// Hardware mapping helpers (defaults are A0..A4)
void setAnalogPins(uint8_t temp1Pin, uint8_t temp2Pin, uint8_t temp3Pin, uint8_t voltagePin, uint8_t currentPin);
void setADCParameters(float vref, int resolution);
void setVoltageScaling(float scale);
void setCurrentScaling(float scale);

// make getFeatures visible to other translation units
Features getFeatures(SensorReadings readingsArray[], Features oldFeatures, int i);

void serialPrintReadings(SensorReadings r, Features f);

// helpers
SimScenario getSimulationScenario(); // new: query current simulation scenario