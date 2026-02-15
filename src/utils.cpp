#include "utils.h"
#include <math.h>
#include <stdint.h>
#include <stddef.h>

float computeArrayMean(float arr[], int size)
{
  if (size <= 0)
    return 0.0f;
  float sum = 0.0f;
  for (int i = 0; i < size; ++i)
    sum += arr[i];
  return sum / size;
}

// Voter implementation with threshold filtering:
// - exclude readings outside of [MIN_TEMP, MAX_TEMP]
// - if >=2 valid readings: choose the two with smallest difference and return their average
// - if 1 valid reading: return that value
// - if none valid: return sentinel -999.0f
float votedTemperature(float t1, float t2, float t3)
{
  const float MIN_TEMP = -50.0f;
  const float MAX_TEMP = 50.0f;
  const float INVALID_SENTINEL = -999.0f;

  float inputs[3] = {t1, t2, t3};
  float valid[3];
  int vcount = 0;
  for (int i = 0; i < 3; ++i)
  {
    float v = inputs[i];
    if (v >= MIN_TEMP && v <= MAX_TEMP)
      valid[vcount++] = v;
  }

  if (vcount >= 2)
  {
    // find pair among valid[] with smallest absolute difference
    float best_a = valid[0], best_b = valid[1];
    float best_d = fabsf(best_a - best_b);
    if (vcount == 3)
    {
      float d01 = fabsf(valid[0] - valid[1]);
      float d02 = fabsf(valid[0] - valid[2]);
      float d12 = fabsf(valid[1] - valid[2]);
      if (d01 <= d02 && d01 <= d12)
      {
        best_a = valid[0];
        best_b = valid[1];
      }
      else if (d02 <= d01 && d02 <= d12)
      {
        best_a = valid[0];
        best_b = valid[2];
      }
      else
      {
        best_a = valid[1];
        best_b = valid[2];
      }
    }
    return (best_a + best_b) * 0.5f;
  }

  if (vcount == 1)
    return valid[0];

  // no valid readings
  return INVALID_SENTINEL;
}

float clampf(float v, float lo, float hi)
{
  if (v < lo)
    return lo;
  if (v > hi)
    return hi;
  return v;
}

// CRC-16/CCITT – byte-at-a-time (no lookup table, saves RAM on AVR)
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
