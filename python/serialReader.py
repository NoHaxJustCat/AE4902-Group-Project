import serial
import time
from influxdb_client import InfluxDBClient, Point
from influxdb_client.client.write_api import SYNCHRONOUS
import re
import argparse
import threading
import sys

# Configurazione InfluxDB
token = "pnAXe3WBVcZ4Vs0KKDKF6Hz576oEih6TY_k18pRRZPZCmH26qzpjfNA0Aw8xn7YuT9eAwWaXBj4jv4H_VsZhqA=="
org = "aur"
bucket = "arduino"
url = "http://100.67.220.32:8086/" # O l'indirizzo del cloud

# Configurazione Seriale (controlla la porta corretta su Arduino IDE)
# Esempio Windows: 'COM3', Mac/Linux: '/dev/tty.usbmodem...'
ser = serial.Serial('COM4', 115200, timeout=1) # Nota: 115200 come nel tuo codice!
time.sleep(2) # Attesa per reset Arduino

# ensure serial buffer is clean and request AUTO mode on the device
try:
    ser.reset_input_buffer()
except AttributeError:
    pass  # older pyserial may not have this

# wait for the boot message (up to ~3s)
start = time.time()
while time.time() - start < 3:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8', errors='replace').strip()
        if line:
            print("Arduino:", line)
            if "Starting:" in line or "Simulator ready" in line:
                break

parser = argparse.ArgumentParser(description="Serial reader (device mode is hardcoded on device)")
parser.add_argument("--status", action="store_true", help="Request device status once on startup")
args = parser.parse_args()

def send_cmd(s):
    try:
        ser.write(s.encode('ascii') + b'\n')
        print("Sent:", s)
    except Exception as e:
        print("Failed to send command:", s, e)

# wait for boot message and then send initial commands
start = time.time()
while time.time() - start < 3:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8', errors='replace').strip()
        if line:
            print("Arduino:", line)
            if "Simulator ready" in line:
                break

# Device mode is hardcoded on the device; optionally request status once
if args.status:
    send_cmd("status")

# start a small background REPL so you can type commands while the script runs
def repl():
    print("Interactive: only 'status' is supported (type 'status' to request device status). Type Ctrl-C to quit.")
    try:
        while True:
            line = input().strip()
            if not line:
                continue
            if line.lower() == 'status':
                send_cmd('status')
            else:
                print("Only 'status' is supported. (Other commands are disabled; mode is hardcoded on device.)")
    except Exception:
        pass

t = threading.Thread(target=repl, daemon=True)
t.start()

# initialize InfluxDB client (graceful fallback)
print("[DEBUG] Initializing InfluxDB client...")
write_api = None
try:
    client = InfluxDBClient(url=url, token=token, org=org)
    write_api = client.write_api(write_options=SYNCHRONOUS)
    print("[SUCCESS] InfluxDB client ready")
except Exception as e:
    write_api = None
    print("[ERROR] InfluxDB init failed, will skip writes:", e)

float_re = re.compile(r'[-+]?\d*\.?\d+(?:[eE][-+]?\d+)?')

# track device-reported status
device_mode = None
device_scenario = None

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8', errors='replace').strip()
        if not line:
            continue

        # textual status / logs
        if line.startswith("Sensor mode:"):
            device_mode = line.split(":", 1)[1].strip()
            print("Device:", line)
            continue
        if line.startswith("Sim:"):
            device_scenario = line.split(":", 1)[1].strip()
            print("Device:", line)
            continue
        if line.startswith("Simulator ready"):
            print(line)
            continue

        # DATA lines (preferred) or any line with >=11 floats
        d = None
        if line.upper().startswith("DATA"):
            parts = [p.strip() for p in line.split(",")]
            tokens = parts[1:] if parts[0].upper().startswith("DATA") else parts
            if len(tokens) >= 13:
                try:
                    d = [float(x) for x in tokens[:13]]
                    print(f"[DEBUG] Parsed DATA line: {len(d)} fields")
                except ValueError:
                    d = None

        if d is None:
            nums = float_re.findall(line)
            if len(nums) >= 13:
                d = [float(x) for x in nums[:13]]
                print(f"[DEBUG] Parsed numeric line: {len(d)} fields")
            else:
                print("Log:", line)
                continue

        try:
            print(f"[DEBUG] Creating InfluxDB point with {len(d)} fields")
            point = Point("battery_analysis") \
                .tag("device", "arduino_uno") \
                .field("temp1", d[0]) \
                .field("temp2", d[1]) \
                .field("temp3", d[2]) \
                .field("voltage", d[3]) \
                .field("current", d[4]) \
                .field("avg_temp", d[5]) \
                .field("voted_temp", d[6]) \
                .field("i_mean_all", d[7]) \
                .field("v_mean_all", d[8]) \
                .field("i_v_ratio_10", d[9]) \
                .field("power_mean_10", d[10]) \
                .field("power_prev", d[11]) \
                .field("capacity", d[12])

            if write_api:
                print("[DEBUG] Attempting to write to InfluxDB...")
                write_api.write(bucket=bucket, org=org, record=point)
                print("[SUCCESS] Data written to InfluxDB")
            else:
                print("[WARNING] No write_api available. Readings:", d)

        except Exception as e:
            print("[ERROR] Failed processing line:", line, "Error:", e)