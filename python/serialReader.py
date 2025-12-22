import serial
import time
from influxdb_client import InfluxDBClient, Point
from influxdb_client.client.write_api import SYNCHRONOUS

# Configurazione InfluxDB
token = "pnAXe3WBVcZ4Vs0KKDKF6Hz576oEih6TY_k18pRRZPZCmH26qzpjfNA0Aw8xn7YuT9eAwWaXBj4jv4H_VsZhqA=="
org = "aur"
bucket = "arduino"
url = "http://100.67.220.32:8086/" # O l'indirizzo del cloud

# Configurazione Seriale (controlla la porta corretta su Arduino IDE)
# Esempio Windows: 'COM3', Mac/Linux: '/dev/tty.usbmodem...'
ser = serial.Serial('COM3', 115200, timeout=1) # Nota: 115200 come nel tuo codice!
time.sleep(2) # Attesa per reset Arduino

client = InfluxDBClient(url=url, token=token, org=org)
write_api = client.write_api(write_options=SYNCHRONOUS)

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
        parts = line.split(',')
        
        if len(parts) == 11: # Assicurati che ci siano tutti i campi
            try:
                # Conversione di tutti i valori in float
                d = [float(x) for x in parts]
                
                point = Point("battery_analysis") \
                    .tag("device", "arduino_uno") \
                    .field("temp1", d[0]) \
                    .field("temp2", d[1]) \
                    .field("temp3", d[2]) \
                    .field("voltage", d[3]) \
                    .field("current", d[4]) \
                    .field("avg_temp", d[5]) \
                    .field("i_mean_all", d[6]) \
                    .field("v_mean_all", d[7]) \
                    .field("i_v_ratio_10", d[8]) \
                    .field("power_mean_10", d[9]) \
                    .field("power_prev", d[10])

                write_api.write(bucket=bucket, org=org, record=point)
                print("Dati inviati con successo")
                
            except ValueError:
                print(f"Errore conversione: {line}")