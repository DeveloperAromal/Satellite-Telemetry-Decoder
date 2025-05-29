import time
import struct
import random
import os


def createTelemetryReport():
    unix_time = int(time.time())
    voltage = random.uniform(30, 40)
    altitude = random.randint(400, 600)
    signal = random.choice(["OK", "WARN", "FAIL"]).ljust(2)[:4]
    return struct.pack('Iff4s', unix_time, voltage, altitude, signal.encode())

with open("../../data/telemetry.bin", "wb") as f:
    while True:
            packet = createTelemetryReport()
            f.write(packet)
            f.flush()
            os.fsync(f.fileno())
            time.sleep(1)
            print(packet)