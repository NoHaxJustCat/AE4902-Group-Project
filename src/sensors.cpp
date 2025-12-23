#include <math.h>
#include <Arduino.h>
#include "sensors.h"

// --- configurable hardware mapping & ADC params ---
static uint8_t g_pin_temp1 = A0;
static uint8_t g_pin_temp2 = A1;
static uint8_t g_pin_temp3 = A2;
static uint8_t g_pin_voltage = A3;
static uint8_t g_pin_current = A4;
static float g_adc_vref = 3.3f;
static int g_adc_resolution = 1024; // supply (use 1024 for 10-bit boards => raw in [0..1023])
static float g_voltage_scale = 1.0f; // divider/mapping to real voltage
static float g_current_scale = 1.0f; // mapping from ADC voltage to current

// current sensor/hardware mode flag
static SensorMode g_sensorMode = SENSOR_MODE_SIMULATION;

// --- Small stateful sensor simulator ---
class SensorSimulator {
public:
  SensorSimulator() : rng_state(0xDEADBEEF), last_ms(0), inited(false), scenario(SIM_NORMAL) {}

  void begin(uint32_t seed) {
    rng_state = seed ? seed : ((uint32_t)micros() ^ 0xA5A5A5A5u);
    last_ms = millis();
    inited = true;

    // initial physical state
    capacity = 100.0f;     // %
    v_nominal = 3.3f;
    v_drop_end = 0.9f;
    internal_resistance = 5.0f; // ohms (affects voltage drop)
    base_current = 0.004f; // A
    ambient_temp = 19.0f;  // C
    temp = ambient_temp;
    power_to_temp_gain = 10.0f;
    cooling = 0.1f;

    // noise & resolution
    voltage_noise = 0.005f;
    current_noise = 0.0002f;
    temp_noise = 0.05f;
    voltage_resolution = 3.3f / 4095.0f;
    current_resolution = 1e-6f;
    temp_resolution = 0.01f;

    // per-sensor biases (small)
    sensor_bias[0] = gaussian(0.0f, 0.2f);
    sensor_bias[1] = gaussian(-0.05f, 0.15f);
    sensor_bias[2] = gaussian(0.07f, 0.15f);

    // existing spike state
    spike_until_ms = 0;
    spike_amplitude = 0.0f;
    scenario = SIM_NORMAL;

    // auto-mode defaults (probabilities are per-second)
    auto_prob_spike = 0.002f;
    auto_prob_fault = 0.001f;
    auto_prob_glitch = 0.0005f;
    auto_prob_pulse = 0.005f;

    // per-sensor event state
    for (int s = 0; s < NSENS; ++s) {
      meas_spike_amp[s] = 0.0f; meas_spike_until_ms[s] = 0;
      meas_glitch_amp[s] = 0.0f; meas_glitch_until_ms[s] = 0;
      meas_fault_until_ms[s] = 0; meas_fault_type[s] = 0;
    }

    pulse_until_ms = 0;
    pulse_amplitude = 0.0f;
  }

  // public gaussian helper (used by whiteNoise wrapper)
  float gaussian(float mean, float stddev) {
    if (stddev <= 0.0f) return mean;
    float u1 = uniform();
    if (u1 <= 1e-12f) u1 = 1e-12f;
    float u2 = uniform();
    float z0 = sqrtf(-2.0f * logf(u1)) * cosf(TWO_PI_F * u2);
    return mean + z0 * stddev;
  }

  SensorReadings read() {
    if (!inited) begin(0);
    step();
    SensorReadings r;
    r.temp1 = meas_temp[0];
    r.temp2 = meas_temp[1];
    r.temp3 = meas_temp[2];
    r.voltage = meas_voltage;
    r.current = meas_current;
    return r;
  }

  void setScenario(SimScenario s) { scenario = s; }
  SimScenario getScenario() const { return static_cast<SimScenario>(scenario); } // new getter
  void injectSpike(float amplitude, unsigned long duration_ms) {
    spike_amplitude = amplitude;
    spike_until_ms = millis() + duration_ms;
  }

  // set per-second probabilities for automatic events
  void setAutoProbabilities(float spike, float fault, float glitch, float pulse) {
    auto_prob_spike = spike;
    auto_prob_fault = fault;
    auto_prob_glitch = glitch;
    auto_prob_pulse = pulse;
  }

  // public injection helper (measurement-level spike for a single sensor)
  void injectSensorSpike(int sensorIndex, float amplitude, unsigned long duration_ms) {
    if (sensorIndex < 0 || sensorIndex >= NSENS) return;
    meas_spike_amp[sensorIndex] = amplitude;
    meas_spike_until_ms[sensorIndex] = millis() + duration_ms;
  }

private:
  uint32_t xorshift() {
    uint32_t x = rng_state;
    x ^= x << 13; x ^= x >> 17; x ^= x << 5;
    rng_state = x;
    return x;
  }
  float uniform() { return (xorshift() >> 8) / (float)(1UL << 24); }
  float quantize(float value, float res) {
    if (res <= 0.0f) return value;
    return roundf(value / res) * res;
  }

  void step() {
    unsigned long now = millis();
    float dt = (now - last_ms) / 1000.0f;
    if (dt <= 0.0f) dt = 0.001f;
    last_ms = now;

    // base current + scenario effects (keep system-level pulses/spikes)
    float current = base_current;
    bool spike_added = false;

    if (scenario == SIM_PULSE) {
      unsigned long t = (now / 1000UL) % 10UL;
      if (t < 2UL) { current += 0.01f; } // fixed periodic pulse
    } else if (scenario == SIM_SPIKE) {
      if (spike_until_ms > now) { current += spike_amplitude; spike_added = true; }
      else if (uniform() < 0.005f) {
        spike_amplitude = 0.01f + 0.03f * uniform();
        spike_until_ms = now + (unsigned long)(1000UL * (0.2f + 2.0f * uniform()));
      }
    } else if (scenario == SIM_FAULTY) {
      base_current += gaussian(0.0f, 0.00005f);
    } else if (scenario == SIM_AUTO) {
      // system-level events (rarer here)
      if (spike_until_ms <= now && uniform() < auto_prob_spike * dt * 0.2f) {
        spike_amplitude = 0.01f + 0.05f * uniform();
        spike_until_ms = now + (unsigned long)(200 + 3000 * uniform());
      }
      if (pulse_until_ms <= now && uniform() < auto_prob_pulse * dt * 0.3f) {
        pulse_amplitude = 0.01f + 0.04f * uniform();
        pulse_until_ms = now + (unsigned long)(1000 + 9000 * uniform());
      }

      // schedule per-sensor independent events
      for (int s = 0; s < NSENS; ++s) {
        // measurement spikes
        if (meas_spike_until_ms[s] <= now && uniform() < auto_prob_spike * dt) {
          if (s < 3) { // temps
            meas_spike_amp[s] = 2.0f + 8.0f * uniform(); // °C
            meas_spike_until_ms[s] = now + (unsigned long)(200 + 3000 * uniform());
          } else if (s == 3) { // voltage
            meas_spike_amp[s] = 0.02f + 0.18f * uniform();
            meas_spike_until_ms[s] = now + (unsigned long)(50 + 2000 * uniform());
          } else { // current measurement spike
            meas_spike_amp[s] = 0.005f + 0.05f * uniform();
            meas_spike_until_ms[s] = now + (unsigned long)(50 + 2000 * uniform());
          }
        }

        // glitches
        if (meas_glitch_until_ms[s] <= now && uniform() < auto_prob_glitch * dt) {
          if (s < 3) {
            meas_glitch_amp[s] = gaussian(0.0f, 1.0f) + (uniform() * 6.0f - 3.0f);
            meas_glitch_until_ms[s] = now + (unsigned long)(50 + 800 * uniform());
          } else if (s == 3) {
            meas_glitch_amp[s] = gaussian(0.0f, 0.02f);
            meas_glitch_until_ms[s] = now + (unsigned long)(30 + 500 * uniform());
          } else {
            meas_glitch_amp[s] = gaussian(0.0f, 0.002f);
            meas_glitch_until_ms[s] = now + (unsigned long)(30 + 500 * uniform());
          }
        }

        // faults (stuck / noisy) per-sensor
        if (meas_fault_until_ms[s] <= now && uniform() < auto_prob_fault * dt) {
          meas_fault_type[s] = (uniform() < 0.5f) ? 0 : 1;
          meas_fault_until_ms[s] = now + (unsigned long)(500 + 15000 * uniform());
        }
      }
    }

    // apply active global spike / pulse events
    if (spike_until_ms > now && !spike_added) current += spike_amplitude;
    if (pulse_until_ms > now) current += pulse_amplitude;

    // capacity / voltage / thermal model (unchanged)
    float consumptionFactor = 0.0005f;
    capacity -= (current * 1000.0f) * consumptionFactor * dt;
    if (capacity < 0.0f) capacity = 0.0f;

    true_voltage = v_nominal - (1.0f - capacity / 100.0f) * v_drop_end - internal_resistance * current;
    if (true_voltage < 0.0f) true_voltage = 0.0f;

    float power = true_voltage * current;
    temp += (power * power_to_temp_gain - cooling * (temp - ambient_temp)) * dt;

    // base measured values
    meas_voltage = quantize(true_voltage + gaussian(0.0f, voltage_noise), voltage_resolution);
    meas_current = quantize(current + gaussian(0.0f, current_noise), current_resolution);
    meas_temp[0] = quantize(temp + sensor_bias[0] + gaussian(0.0f, temp_noise), temp_resolution);
    meas_temp[1] = quantize(temp + sensor_bias[1] + gaussian(0.0f, temp_noise), temp_resolution);
    meas_temp[2] = quantize(temp + sensor_bias[2] + gaussian(0.0f, temp_noise), temp_resolution);

    // apply per-sensor measurement spikes/glitches/faults independently
    for (int s = 0; s < NSENS; ++s) {
      if (meas_spike_until_ms[s] > now) {
        if (s < 3) meas_temp[s] = quantize(meas_temp[s] + meas_spike_amp[s], temp_resolution);
        else if (s == 3) meas_voltage = quantize(meas_voltage + meas_spike_amp[s], voltage_resolution);
        else meas_current = quantize(meas_current + meas_spike_amp[s], current_resolution);
      }

      if (meas_glitch_until_ms[s] > now) {
        if (s < 3) meas_temp[s] = quantize(meas_temp[s] + meas_glitch_amp[s], temp_resolution);
        else if (s == 3) meas_voltage = quantize(meas_voltage + meas_glitch_amp[s], voltage_resolution);
        else meas_current = quantize(meas_current + meas_glitch_amp[s], current_resolution);
      }

      if (meas_fault_until_ms[s] > now) {
        if (meas_fault_type[s] == 0) { // stuck
          if (s < 3) meas_temp[s] = -999.0f;
          else if (s == 3) meas_voltage = -999.0f;
          else meas_current = -999.0f;
        } else { // noisy
          if (s < 3) meas_temp[s] = quantize(meas_temp[s] + gaussian(0.0f, 5.0f) + (uniform() * 20.0f - 10.0f), temp_resolution);
          else if (s == 3) meas_voltage = quantize(meas_voltage + gaussian(0.0f, 0.02f) + (uniform() * 0.05f - 0.025f), voltage_resolution);
          else meas_current = quantize(meas_current + gaussian(0.0f, 0.01f) + (uniform() * 0.02f - 0.01f), current_resolution);
        }
      }
    }

    // rare random voltage spike/glitch (existing)
    if (uniform() < 0.001f) meas_voltage += gaussian(0.0f, voltage_noise * 2.0f);
  }

  // per-sensor event state
  static constexpr int NSENS = 5; // 0..2 temps, 3=voltage, 4=current
  float meas_spike_amp[NSENS];
  unsigned long meas_spike_until_ms[NSENS];
  float meas_glitch_amp[NSENS];
  unsigned long meas_glitch_until_ms[NSENS];
  unsigned long meas_fault_until_ms[NSENS];
  int meas_fault_type[NSENS];

  uint32_t rng_state;
  unsigned long last_ms;
  bool inited;

  // state
  float capacity;
  float true_voltage;
  float temp;
  float ambient_temp;

  // params
  float base_current;
  float pulse_amplitude;     // used by AUTO pulses
  float spike_amplitude;
  unsigned long spike_until_ms;
  unsigned long pulse_until_ms;  // used by AUTO pulses
  unsigned long glitch_until_ms;
  unsigned long fault_until_ms;

  float v_nominal;
  float v_drop_end;
  float internal_resistance;

  // noise / resolution
  float voltage_noise, current_noise, temp_noise;
  float voltage_resolution, current_resolution, temp_resolution;
  float meas_voltage, meas_current, meas_temp[3];
  float sensor_bias[3];

  float power_to_temp_gain;
  float cooling;

  int scenario;

  // auto-mode parameters (per-second probabilities)
  float auto_prob_spike;
  float auto_prob_fault;
  float auto_prob_glitch;
  float auto_prob_pulse;

  // auto-mode event state
  float glitch_amplitude;
  int fault_sensor;
  int fault_type; // 0=stuck, 1=noisy

  static constexpr float TWO_PI_F = 6.28318530717958647692f;
};

static SensorSimulator g_sim;

// --- hardware helpers ---
static inline float analogToVoltage(int raw) {
  int maxRaw = (g_adc_resolution > 1) ? (g_adc_resolution - 1) : 1023;
  return (raw / (float)maxRaw) * g_adc_vref;
}

static float readTempFromAnalog(uint8_t pin) {
  // Default mapping: LM35-like (10 mV/°C). Adjust with calibration as needed.
  int raw = analogRead(pin);
  float v = analogToVoltage(raw);
  return v * 100.0f; // 0.01 V/°C => multiply by 100
}

static float readVoltageFromAnalog(uint8_t pin) {
  int raw = analogRead(pin);
  float v = analogToVoltage(raw) * g_voltage_scale;
  return v;
}

static float readCurrentFromAnalog(uint8_t pin) {
  int raw = analogRead(pin);
  float v = analogToVoltage(raw);
  return v * g_current_scale; // user can calibrate
}

// --- API implementations ---
SensorReadings getSensorsReadings() {
  if (g_sensorMode == SENSOR_MODE_SIMULATION) {
    return g_sim.read();
  } else {
    SensorReadings s;
    s.temp1 = readTempFromAnalog(g_pin_temp1);
    s.temp2 = readTempFromAnalog(g_pin_temp2);
    s.temp3 = readTempFromAnalog(g_pin_temp3);
    s.voltage = readVoltageFromAnalog(g_pin_voltage);
    s.current = readCurrentFromAnalog(g_pin_current);
    return s;
  }
}

float whiteNoise(float mean, float stddev) {
  // Prefer simulator's RNG for reproducibility when it's initialized
  if (stddev <= 0.0f) return mean;
  return g_sim.gaussian(mean, stddev);
}

void initSensorSimulator(uint32_t seed) { g_sim.begin(seed); }
void setSensorMode(SensorMode mode) { g_sensorMode = mode; }
SensorMode getSensorMode() { return g_sensorMode; }
void setSimulationScenario(SimScenario s) { g_sim.setScenario(s); }
void simInjectSpike(float amplitude, unsigned long duration_ms) { g_sim.injectSpike(amplitude, duration_ms); }

void setAnalogPins(uint8_t temp1Pin, uint8_t temp2Pin, uint8_t temp3Pin, uint8_t voltagePin, uint8_t currentPin) {
  g_pin_temp1 = temp1Pin; g_pin_temp2 = temp2Pin; g_pin_temp3 = temp3Pin;
  g_pin_voltage = voltagePin; g_pin_current = currentPin;
}
void setADCParameters(float vref, int resolution) { g_adc_vref = vref; g_adc_resolution = resolution; }
void setVoltageScaling(float scale) { g_voltage_scale = scale; }
void setCurrentScaling(float scale) { g_current_scale = scale; }

void serialPrintReadings(SensorReadings r, Features f) {
    Serial.print("DATA,");
    const int PREC = 6; // number of decimals for printed floats
    Serial.print(r.temp1, PREC); Serial.print(",");
    Serial.print(r.temp2, PREC); Serial.print(",");
    Serial.print(r.temp3, PREC); Serial.print(",");
    Serial.print(r.voltage, PREC); Serial.print(",");
    Serial.print(r.current, PREC); Serial.print(",");
    Serial.print(f.temperature, PREC); Serial.print(",");
    Serial.print(f.i_mean_all, PREC); Serial.print(",");
    Serial.print(f.v_mean_all, PREC); Serial.print(",");
    Serial.print(f.i_v_ratio_10, PREC); Serial.print(",");
    Serial.print(f.power_mean_10, PREC); Serial.print(",");
    Serial.println(f.power_prev, PREC);
}

// top-level wrapper for auto probabilities
void setAutoProbabilities(float spikeProbPerSec, float faultProbPerSec, float glitchProbPerSec, float pulseProbPerSec) {
  g_sim.setAutoProbabilities(spikeProbPerSec, faultProbPerSec, glitchProbPerSec, pulseProbPerSec);
}

// public shim
void simInjectSensorSpike(int sensorIndex, float amplitude, unsigned long duration_ms) {
  g_sim.injectSensorSpike(sensorIndex, amplitude, duration_ms);
}

// getter for scenario
SimScenario getSimulationScenario() { return g_sim.getScenario(); } // new