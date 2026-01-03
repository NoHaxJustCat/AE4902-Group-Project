#pragma once

// Small general-purpose helpers
float computeArrayMean(float arr[], int size);

// Voter: for triple redundancy, return the average of the two closest values
float votedTemperature(float t1, float t2, float t3);

// Clamping helper
float clampf(float v, float lo, float hi);
