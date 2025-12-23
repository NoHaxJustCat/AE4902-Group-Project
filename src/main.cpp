#include <Arduino.h>
#include <sensors.h>

static unsigned long sampling_period = 0;
SensorReadings readingsArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int index = 0;
static Features lastFeatures = {0};              // store previous features across iterations
static String cmdBuffer; // buffer for incoming serial text lines

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 2000) {} // brief wait for Serial on some boards

  randomSeed(analogRead(A0)); // seed RNG from floating analog pin
  initSensorSimulator(analogRead(A0) ^ (unsigned long)micros()); // deterministic-ish seed for sim
  setSensorMode(SENSOR_MODE_SIMULATION); // default to simulation
  setSimulationScenario(SIM_AUTO); // start in automatic probabilistic mode by default
  Serial.println("Simulator ready. Default: AUTO mode. Commands:");
  Serial.println("  m - toggle sensor mode (simulation/hardware)");
  Serial.println("  a - enable AUTO (random faults/spikes/pulses)");
  Serial.println("Simulation controls (when in sim mode): n=normal p=pulse s=spike f=fault x=inject spike");

  int sampling_freq = 1; // Hz
  sampling_period = 1000UL / sampling_freq; // ms
}

static const char* scenarioToString(SimScenario s) {
  switch (s) {
    case SIM_NORMAL: return "NORMAL";
    case SIM_PULSE:  return "PULSE";
    case SIM_SPIKE:  return "SPIKE";
    case SIM_FAULTY: return "FAULTY";
    case SIM_AUTO:   return "AUTO";
    default: return "UNKNOWN";
  }
}

static const char* modeToString(SensorMode m) {
  return (m == SENSOR_MODE_HARDWARE) ? "HARDWARE" : "SIMULATION";
}

static void processSerialLine(String line) {
  line.trim();
  if (line.length() == 0) return;

  // legacy single-char commands
  if (line.length() == 1) {
    char c = line.charAt(0);
    if (c == 'm') {
      if (getSensorMode() == SENSOR_MODE_SIMULATION) {
        setSensorMode(SENSOR_MODE_HARDWARE);
        Serial.println("Sensor mode: HARDWARE (reading analog pins)");
      } else {
        setSensorMode(SENSOR_MODE_SIMULATION);
        Serial.println("Sensor mode: SIMULATION");
      }
      return;
    } else if (c == 'a') { setSimulationScenario(SIM_AUTO); Serial.println("Sim: AUTO (probabilistic events enabled)"); return; }
    else if (c == 'p') { setSimulationScenario(SIM_PULSE); Serial.println("Sim: PULSE"); return; }
    else if (c == 'n') { setSimulationScenario(SIM_NORMAL); Serial.println("Sim: NORMAL"); return; }
    else if (c == 's') { setSimulationScenario(SIM_SPIKE); Serial.println("Sim: SPIKE"); return; }
    else if (c == 'f') { setSimulationScenario(SIM_FAULTY); Serial.println("Sim: FAULTY"); return; }
    else if (c == 'x') { simInjectSpike(0.05f, 3000); Serial.println("Injected spike"); return; }
    // unknown single-char => fall-through to message below
  }

  // robust textual commands (case-insensitive)
  String cmd = line;
  cmd.toLowerCase();

  if (cmd.startsWith("mode ")) {
    String val = cmd.substring(5); val.trim();
    if (val.startsWith("sim")) { setSensorMode(SENSOR_MODE_SIMULATION); Serial.println("Sensor mode: SIMULATION"); }
    else if (val.startsWith("hw") || val.startsWith("hard")) { setSensorMode(SENSOR_MODE_HARDWARE); Serial.println("Sensor mode: HARDWARE"); }
    else { Serial.print("Unknown mode: "); Serial.println(val); }
    return;
  }

  if (cmd.startsWith("scenario ")) {
    String val = cmd.substring(9); val.trim();
    if (val.startsWith("auto")) { setSimulationScenario(SIM_AUTO); Serial.println("Sim: AUTO"); }
    else if (val.startsWith("normal")) { setSimulationScenario(SIM_NORMAL); Serial.println("Sim: NORMAL"); }
    else if (val.startsWith("pulse")) { setSimulationScenario(SIM_PULSE); Serial.println("Sim: PULSE"); }
    else if (val.startsWith("spike")) { setSimulationScenario(SIM_SPIKE); Serial.println("Sim: SPIKE"); }
    else if (val.startsWith("fault") || val.startsWith("faulty")) { setSimulationScenario(SIM_FAULTY); Serial.println("Sim: FAULTY"); }
    else { Serial.print("Unknown scenario: "); Serial.println(val); }
    return;
  }

  if (cmd.startsWith("auto ")) {
    String val = cmd.substring(5); val.trim();
    if (val.startsWith("on")) { setSimulationScenario(SIM_AUTO); Serial.println("Sim: AUTO"); return; }
    else if (val.startsWith("off")) { setSimulationScenario(SIM_NORMAL); Serial.println("Sim: NORMAL"); return; }
  }

  // inject [sensorIndex] [amp] [duration_ms]  OR  inject spike [amp] [duration_ms]
  if (cmd.startsWith("inject")) {
    char buf[120];
    cmd.toCharArray(buf, sizeof(buf));
    int sindex; float amp; unsigned long dur;
    if (sscanf(buf, "inject %d %f %lu", &sindex, &amp, &dur) == 3) {
      simInjectSensorSpike(sindex, amp, dur);
      Serial.print("Injected sensor spike: idx="); Serial.print(sindex);
      Serial.print(" amp="); Serial.print(amp); Serial.print(" dur="); Serial.println(dur);
      return;
    }
    if (sscanf(buf, "inject spike %f %lu", &amp, &dur) == 2) {
      simInjectSpike(amp, dur);
      Serial.print("Injected global spike amp="); Serial.print(amp); Serial.print(" dur="); Serial.println(dur);
      return;
    }
    Serial.print("Could not parse inject command: "); Serial.println(line);
    return;
  }

  if (cmd.equals("status")) {
    Serial.print("Sensor mode: "); Serial.println(modeToString(getSensorMode()));
    Serial.print("Simulation scenario: "); Serial.println(scenarioToString(getSimulationScenario()));
    return;
  }

  Serial.print("Unknown command: "); Serial.println(line);
}

float computeArrayMean(float arr[], int size) {
  if (size <= 0) return 0.0f;            // avoid divide-by-zero / invalid means
  float sum = 0.0f;
  for (int i = 0; i < size; ++i) {
    sum += arr[i];
  }
  return sum / size;
}

Features getFeatures(SensorReadings readingsArray[], Features oldFeatures, int i) {
  Features features;
  features.time = millis() / 1000.0f;
  features.capacity = 100.0f;
  features.temperature = (readingsArray[0].temp1 + readingsArray[0].temp2 + readingsArray[0].temp3) / 3.0f;

  int prev_count = (i > 0) ? i : 0;      // treat negative/zero i as "no previous samples"
  int new_count = prev_count + 1;

  // handle first iteration (no previous features) safely
  if (prev_count == 0 || oldFeatures.count_all <= 0) {
    features.i_mean_all = readingsArray[0].current;
    features.v_mean_all = readingsArray[0].voltage;
  } else {
    features.i_mean_all = (oldFeatures.i_mean_all * prev_count + readingsArray[0].current) / (prev_count + 1);
    features.v_mean_all = (oldFeatures.v_mean_all * prev_count + readingsArray[0].voltage) / (prev_count + 1);
  }

  // compute iv and power means using only available valid samples (up to 10)
  int valid_samples = (new_count < 10) ? new_count : 10;
  float iv[10];
  int iv_count = 0;
  float power_vals[10];
  int power_count = 0;
  for (int k = 0; k < valid_samples; ++k) {
    float v = readingsArray[k].voltage;
    float c = readingsArray[k].current;
    if (v != 0.0f) iv[iv_count++] = c / v;
    if (v != 0.0f || c != 0.0f) power_vals[power_count++] = v * c;
  }
  features.i_v_ratio_10 = computeArrayMean(iv, iv_count);
  features.power_mean_10 = computeArrayMean(power_vals, power_count);

  // previous power only valid if we have at least one previous sample
  features.power_prev = (prev_count >= 1) ? (readingsArray[1].voltage * readingsArray[1].current) : 0.0f;

  features.count_all = new_count;
  features.i_v_ratio = (readingsArray[0].voltage != 0.0f) ? (readingsArray[0].current / readingsArray[0].voltage) : 0.0f;
  return features;
}

void loop() {
  // read incoming serial lines non-blocking and process them
  while (Serial.available()) {
    char ch = Serial.read();
    if (ch == '\r') continue;
    if (ch == '\n') {
      if (cmdBuffer.length() > 0) {
        processSerialLine(cmdBuffer);
        cmdBuffer = "";
      }
    } else {
      cmdBuffer += ch;
      if (cmdBuffer.length() > 128) cmdBuffer = cmdBuffer.substring(0, 128); // cap buffer
    }
  }

  static unsigned long last = 0;
  unsigned long now = millis();
  if (now - last >= sampling_period) {
    last = now;
    SensorReadings r = getSensorsReadings();
    for (int i = 9; i > 0; --i) readingsArray[i] = readingsArray[i - 1];
    readingsArray[0] = r;

    // pass lastFeatures (zero-initialized on first call)
    Features f = getFeatures(readingsArray, lastFeatures, index);

    serialPrintReadings(r, f);
    
    lastFeatures = f;   // save for next iteration
    ++index;            // increment sample counter AFTER using it
  }
}