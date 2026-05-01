#!/usr/bin/env python3
"""
Real-Time Data Dashboard for ESP32 Sensor Logger
Reads CSV data from serial port and displays live graphs
"""

import serial
import serial.tools.list_ports
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque
import sys

# ===== CONFIGURATION =====
# Set this to a specific port to skip auto-detect, e.g. '/dev/cu.usbserial-0001'
# or 'COM4'. Leave as None to auto-detect.
SERIAL_PORT = None
BAUD_RATE = 9600
MAX_DATA_POINTS = 100

# Common USB-serial chips on ESP32 dev boards. We match these in port descriptions.
ESP32_HINTS = ('CP210', 'CP2102', 'CH340', 'CH9102', 'usbserial', 'wchusbserial', 'SLAB')


def find_esp32_port():
    """Return the first port that looks like an ESP32, or None."""
    candidates = list(serial.tools.list_ports.comports())
    for port in candidates:
        text = ' '.join(filter(None, [port.device, port.description, port.manufacturer or '', port.hwid or '']))
        if any(hint.lower() in text.lower() for hint in ESP32_HINTS):
            return port.device
    return None


# ===== DATA STORAGE =====
timestamps = deque(maxlen=MAX_DATA_POINTS)
temperatures = deque(maxlen=MAX_DATA_POINTS)
humidities = deque(maxlen=MAX_DATA_POINTS)
light_levels = deque(maxlen=MAX_DATA_POINTS)

# ===== SERIAL CONNECTION =====
port_to_open = SERIAL_PORT or find_esp32_port()
if port_to_open is None:
    print("Could not auto-detect an ESP32 serial port.")
    print("Available ports:")
    for p in serial.tools.list_ports.comports():
        print(f"  {p.device}  -  {p.description}")
    print("\nFix: edit SERIAL_PORT at the top of dashboard.py to one of the above,")
    print("or close Arduino Serial Monitor (it holds the port exclusively) and re-run.")
    sys.exit(1)

try:
    ser = serial.Serial(port_to_open, BAUD_RATE, timeout=1)
    print(f"Connected to {port_to_open}")
    print("Waiting for data...\n")
except Exception as e:
    print(f"Error: could not open serial port {port_to_open}")
    print(f"Details: {e}")
    print("\nTroubleshooting:")
    print("1. Is the ESP32 plugged in?")
    print("2. Close Arduino Serial Monitor (it holds the port exclusively).")
    print("3. List available ports: python3 -m serial.tools.list_ports -v")
    sys.exit(1)

# Skip the header line and startup messages
while True:
    line = ser.readline().decode('utf-8').strip()
    if line.startswith('timestamp'):
        print("Header found, starting data collection...")
        break
    if ',' in line:
        # Found data line, don't skip it
        break

# ===== MATPLOTLIB SETUP =====
fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(10, 8))
fig.suptitle('ESP32 Sensor Dashboard', fontsize=16, fontweight='bold')

# ===== UPDATE FUNCTION (called repeatedly) =====
def update_graphs(frame):
    try:
        # Read line from serial
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            
            # Skip empty lines and error messages
            if not line or line.startswith('ERROR'):
                return
            
            # Parse CSV data: timestamp,temperature,humidity,light
            data = line.split(',')
            
            if len(data) != 4:
                return
            
            try:
                timestamp = float(data[0]) / 1000.0  # Convert to seconds
                temperature = float(data[1])
                humidity = float(data[2])
                light = int(data[3])
                
                # Store data
                timestamps.append(timestamp)
                temperatures.append(temperature)
                humidities.append(humidity)
                light_levels.append(light)
                
                # Print to console
                print(f"Time: {timestamp:.1f}s | Temp: {temperature:.1f}°C | "
                      f"Humidity: {humidity:.1f}% | Light: {light}")
                
            except ValueError:
                return  # Skip malformed data
        
        # Update graphs only if we have data
        if len(timestamps) > 0:
            # Clear previous plots
            ax1.clear()
            ax2.clear()
            ax3.clear()
            
            # Plot 1: Temperature
            ax1.plot(list(timestamps), list(temperatures), 'r-', linewidth=2)
            ax1.set_ylabel('Temperature (°C)', fontsize=12)
            ax1.set_title('Temperature over Time')
            ax1.grid(True, alpha=0.3)
            
            # Plot 2: Humidity
            ax2.plot(list(timestamps), list(humidities), 'b-', linewidth=2)
            ax2.set_ylabel('Humidity (%)', fontsize=12)
            ax2.set_title('Humidity over Time')
            ax2.grid(True, alpha=0.3)
            
            # Plot 3: Light Level
            ax3.plot(list(timestamps), list(light_levels), 'g-', linewidth=2)
            ax3.set_ylabel('Light Level', fontsize=12)
            ax3.set_xlabel('Time (seconds)', fontsize=12)
            ax3.set_title('Light Level over Time')
            ax3.grid(True, alpha=0.3)
            
            # Adjust layout
            plt.tight_layout()
        
    except KeyboardInterrupt:
        print("\nStopping data collection...")
        ser.close()
        plt.close()
        sys.exit(0)
    except Exception as e:
        print(f"Error: {e}")

# ===== START ANIMATION =====
ani = animation.FuncAnimation(fig, update_graphs, interval=100, cache_frame_data=False)

print("\n=== Dashboard Running ===")
print("Press Ctrl+C to stop\n")

try:
    plt.show()
except KeyboardInterrupt:
    print("\nExiting...")
    ser.close()
    sys.exit(0)
