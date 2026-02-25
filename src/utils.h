
#pragma once

// Small general-purpose helpers
float computeArrayMean(float arr[], int size);

// Voter: for triple redundancy, return the average of the two closest values
float votedTemperature(float t1, float t2, float t3);

void checkThermalSafety(float currentTemp, float measuredCurrent, float measuredVoltage);
void initSafetyRelay();

// Clamping helper
float clampf(float v, float lo, float hi);

uint16_t crc16_ccitt(const char *data, size_t len);

