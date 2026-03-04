# 📊 Project 3: IoT Dashboard

## What You'll Build

A full-featured web dashboard with real-time charts, LED control, and a JSON API — all served from your ESP32. This is the most advanced Workshop 3 project!

**Access from:** Phone, tablet, computer — anything with a browser on the same network.

---

## Hardware Setup

### Components Needed
- 1x DHT11 sensor (temperature & humidity)
- 1x LDR (light sensor)
- 1x 10kΩ resistor (for LDR voltage divider)
- 2x LEDs (red, green)
- 2x 220Ω resistors
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
| Red LED (+) | GPIO 25 | Through 220Ω resistor to GND |
| Green LED (+) | GPIO 26 | Through 220Ω resistor to GND |

### Breadboard Layout

```
ESP32        Breadboard
3.3V    ──── DHT11 VCC
GPIO 5  ──── DHT11 DATA
GND     ──── DHT11 GND

3.3V    ──── LDR ──┬── GPIO 34 (analog)
                    └── [10kΩ] ── GND

GPIO 25 ──── [220Ω] ──── LED Red (+) ──── GND
GPIO 26 ──── [220Ω] ──── LED Green (+) ── GND
```

---

## Step-by-Step Build

### Step 1: Build the Circuit (15 min)

1. Connect DHT11 sensor (VCC → 3.3V, DATA → GPIO 5, GND → GND)
2. Build LDR voltage divider (3.3V → LDR → GPIO 34, GPIO 34 → 10kΩ → GND)
3. Place 2 LEDs with 220Ω resistors
4. Verify all connections

### Step 2: Configure WiFi (5 min)

Open [code-web-dashboard.ino](code-web-dashboard.ino) and update:

```cpp
const char* ssid = "YOUR_NETWORK_NAME";
const char* password = "YOUR_PASSWORD";
```

### Step 3: Upload Code (3 min)

1. Install DHT library (if not already installed)
2. Upload code to ESP32
3. Open Serial Monitor (9600 baud)
4. Note the IP address printed

### Step 4: Access Dashboard (2 min)

1. Open any browser on the same WiFi network
2. Go to `http://YOUR_ESP32_IP`
3. Explore the interactive dashboard!

---

## Dashboard Features

### Sensor Display
- Temperature in Celsius and Fahrenheit
- Humidity percentage with status indicator
- Light level with descriptive label (Dark / Dim / Bright)

### LED Control
- Toggle red and green LEDs from the web page
- Buttons show current LED state
- Instant feedback

### JSON API
- `GET /api/data` — returns all sensor readings and LED states as JSON
- Use this to build your own apps or log data

### Design
- Modern card-based UI with gradient background
- Mobile-friendly responsive layout
- Real-time updates every 3 seconds
- Status indicator showing live connection

---

## Code Overview

The code creates a web server with multiple routes:
- `/` — Serves the HTML dashboard with embedded CSS and JavaScript
- `/api/data` — Returns JSON with sensor readings and LED states
- `/api/led` — Accepts POST requests to toggle LEDs

JavaScript on the page calls `/api/data` every 3 seconds to update readings and calls `/api/led` when you click the toggle buttons.

---

## Customization Ideas

### Beginner
- Change the color scheme (search for CSS gradient colors)
- Add more sensor cards
- Change the update interval (currently 3 seconds)
- Change LED pin assignments

### Intermediate
- Add historical data charts using Chart.js
- Store min/max values and display them
- Add temperature threshold alerts
- Add a buzzer control button

### Advanced
- Log data to SPIFFS (ESP32 flash storage)
- Add authentication (username/password)
- Push data to a cloud service (ThingSpeak, Firebase)
- Add multiple pages (settings, history, about)

---

## Troubleshooting

See [troubleshooting.md](../troubleshooting.md) for common issues.

**Dashboard-specific issues:**
- **Page loads but shows '--' for values:** Check `/api/data` endpoint directly — visit `http://ESP32_IP/api/data` in your browser
- **LED buttons don't work:** Check browser console (F12) for JavaScript errors
- **Slow updates:** Reduce sensor read interval or increase JavaScript poll interval
- **ESP32 crashes:** The HTML is large — make sure you're using ESP32 (not ESP8266)

---

**Complete code:** [code-web-dashboard.ino](code-web-dashboard.ino)
