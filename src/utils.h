#pragma once
#include <stdint.h>
#include <stddef.h>

// Small general-purpose helpers
float computeArrayMean(float arr[], int size);

// Voter: for triple redundancy, return the average of the two closest values
float votedTemperature(float t1, float t2, float t3);

// Clamping helper
float clampf(float v, float lo, float hi);

// CRC-16/CCITT (0xFFFF initial, poly 0x1021) – used for serial data integrity
uint16_t crc16_ccitt(const char *data, size_t len);
