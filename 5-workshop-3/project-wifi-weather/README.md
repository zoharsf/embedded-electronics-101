# 📡 Project 1: WiFi Weather Station

## What You'll Build

A web-based weather station displaying real-time temperature, humidity, and light levels accessible from any browser on your network.

**Access from:** Phone, tablet, computer - anything with a browser!

---

## Hardware Setup

### Components Needed
- 1x DHT11 sensor (temperature & humidity)
- 1x LDR (light sensor)
- 1x 10kΩ resistor
- Jumper wires

### Circuit Connections

| Component | ESP32 Pin | Notes |
|-----------|-----------|-------|
| DHT11 VCC | 3.3V | Power |
| DHT11 DATA | GPIO 5 | Signal |
| DHT11 GND | GND | Ground |
| LDR one end | 3.3V | Voltage divider |
| LDR other end | GPIO 34 | Analog input |
| 10kΩ resistor | GPIO 34 to GND | Pull-down |

---

## Step-by-Step Build

### Step 1: Build the Circuit (10 min)

1. Connect DHT11 sensor
2. Build LDR voltage divider
3. Verify all connections

### Step 2: Configure WiFi (5 min)

Open [code-wifi-weather.ino](code-wifi-weather.ino) and update:

```cpp
const char* ssid = "YOUR_NETWORK_NAME";
const char* password = "YOUR_PASSWORD";
```

### Step 3: Upload Code (3 min)

1. Install DHT library (if not already installed)
2. Upload code to ESP32
3. Open Serial Monitor

### Step 4: Access Dashboard (2 min)

1. Find IP address in Serial Monitor
2. Open browser
3. Go to `http://YOUR_ESP32_IP`
4. See live weather data!

---

## Code Overview

The code creates a web server that:
- Reads DHT11 sensor every 2 seconds
- Reads light level from LDR
- Generates HTML dashboard
- Auto-refreshes every 5 seconds
- Shows current values with nice formatting

---

## Dashboard Features

✅ Temperature in Celsius and Fahrenheit
✅ Humidity percentage
✅ Light level (0-4095)
✅ Auto-refresh (updates automatically)
✅ Mobile-friendly responsive design
✅ Clean, modern interface

---

## Customization Ideas

### Beginner
- Change refresh rate (currently 5 seconds)
- Add more sensors
- Change colors/styling
- Add temperature history

### Intermediate
- Add graphs/charts
- Log data to SD card
- Email alerts for thresholds
- Add weather icons

### Advanced
- Cloud integration (ThingSpeak, Blynk)
- Historical data storage
- Weather forecasting
- Multiple ESP32 devices

---

## Troubleshooting

See [troubleshooting.md](../troubleshooting.md) for common issues.

---

**Complete code:** [code-wifi-weather.ino](code-wifi-weather.ino)
