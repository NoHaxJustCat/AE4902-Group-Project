#pragma once
#include "sensors.h"
#include <Arduino.h>

// Read sensors from actual hardware ADC pins
SensorReadings getHardwareReadings();

// Hardware configuration helpers
void setAnalogPins(uint8_t temp1Pin, uint8_t temp2Pin, uint8_t temp3Pin, uint8_t voltagePin, uint8_t currentPin);
void setADCParameters(float vref, int resolution);
void setVoltageScaling(float scale);
void setCurrentScaling(float scale);
