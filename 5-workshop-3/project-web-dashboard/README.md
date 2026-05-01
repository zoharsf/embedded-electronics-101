# Project 3: IoT Dashboard

## What You'll Build

A full-featured web dashboard with sensor cards, LED toggle buttons, and a JSON API - all served from your ESP32. Most "real-app" feel of the three Workshop 3 projects.

You will:
1. Turn your phone into a 2.4 GHz hotspot.
2. Have the ESP32 join the hotspot.
3. Open the dashboard in your phone's browser and toggle physical LEDs from the page.

---

## Hardware Setup

### Components Needed (all in your kit)
- 1x DHT11 sensor (temperature & humidity)
- 1x LDR (light sensor)
- 1x 10kΩ resistor (LDR voltage divider)
- 2x LEDs (red, green)
- 2x 220Ω resistors
- Jumper wires

### Circuit Connections

| Component | ESP32 Pin | Notes |
|-----------|-----------|-------|
| DHT11 VCC  | 3.3V    | Power |
| DHT11 DATA | GPIO 5  | Signal |
| DHT11 GND  | GND     | Ground |
| LDR leg 1  | 3.3V    | Voltage divider top |
| LDR leg 2 + 10kΩ | GPIO 34 | Junction = analog input |
| 10kΩ other end | GND | Voltage divider bottom |
| Red LED (+) | GPIO 25 | Via 220Ω to GND |
| Green LED (+) | GPIO 26 | Via 220Ω to GND |

### Breadboard Layout

```
ESP32        Breadboard
3.3V    ──── DHT11 VCC
GPIO 5  ──── DHT11 DATA
GND     ──── DHT11 GND

3.3V    ──── LDR ──┬── GPIO 34 (analog)
                    └── [10kΩ] ── GND

GPIO 25 ──── [220Ω] ──── Red LED (+) ──── GND
GPIO 26 ──── [220Ω] ──── Green LED (+) ── GND
```

---

## Step-by-Step Build

### Step 1: Build the circuit (12 min)
1. DHT11 in place: VCC, DATA, GND.
2. LDR voltage divider with the 10kΩ.
3. Two LEDs each with a 220Ω resistor in series.

### Step 2: Turn on your phone hotspot (2 min)
- **iPhone:** Settings → Personal Hotspot → on. Enable "Maximize Compatibility" (forces 2.4 GHz). Keep this screen open while pairing the ESP32.
- **Android:** Settings → Network → Hotspot. Set band to "2.4 GHz".

### Step 3: Configure the sketch (3 min)
Open [code-web-dashboard.ino](code-web-dashboard.ino) and paste your hotspot's SSID and password:

```cpp
const char* ssid     = "YOUR_PHONE_HOTSPOT_NAME";
const char* password = "YOUR_HOTSPOT_PASSWORD";
```

Both are case-sensitive.

### Step 4: Upload and connect (5 min)
1. Make sure the DHT library is installed.
2. Upload the sketch.
3. Open Serial Monitor at 9600 baud.
4. Note the IP address printed after `Connected!`.

### Step 5: Open the dashboard (1 min)
On the **same phone** running the hotspot, browse to that IP. You'll see the dashboard with sensor cards and LED toggle buttons. Tap the LED buttons - the physical LEDs should change state on the breadboard.

---

## Dashboard Features

- Temperature (Celsius and Fahrenheit)
- Humidity (with comfort label)
- Light (raw value plus a visual progress bar)
- LED toggle buttons (state syncs across browser refreshes)
- JSON API at `/api/data` for everything readable
- POST `/api/led` for LED control
- Real-time refresh every 3 seconds

---

## Code Overview

The code defines three routes:
- `GET /` - the HTML dashboard, with embedded CSS and JS.
- `GET /api/data` - JSON with sensor readings and LED states.
- `POST /api/led` - flips the requested LED.

The page polls `/api/data` every 3 seconds and replaces the values in-place. LED toggle buttons POST to `/api/led` with a small body and re-render on response.

---

## Stretch Goals (with acceptance criteria)

### Beginner
- **Recolor the page.** Replace the gradient (search for the CSS background). *Done when:* the page looks visually different.
- **Add a third LED card** for the blue LED on, say, GPIO 27. *Done when:* the new button toggles a real LED.
- **Change update interval** to 1 second. *Done when:* values tick once a second in the browser.

### Intermediate
- **Min/max tracking.** Maintain min/max of temperature and humidity since boot, expose in JSON, render on the page. *Done when:* min stops dropping and max stops climbing as you breathe on the sensor.
- **`/api/csv`.** Add a route returning all current values as one CSV line. *Done when:* `curl http://<esp-ip>/api/csv` returns a CSV row.
- **Threshold alert.** Color the temperature card red when temperature > 28°C. *Done when:* warming the sensor flips the color.

### Advanced
- **History sparkline.** Keep last 60 readings in a ring buffer. Add an inline-SVG sparkline. *Done when:* recent ups and downs appear in the chart.
- **Auth.** Add HTTP Basic auth using `server.authenticate(...)`. *Done when:* visiting the page prompts for credentials.
- **Cloud forwarding.** POST a JSON snapshot to webhook.site once per minute. *Done when:* you see the data on the webhook capture page.

---

## Troubleshooting

### Page loads but values show `--`
- Hit `/api/data` directly in the browser - if it returns NaNs, the DHT11 isn't responding (loose data wire, library missing, wrong sensor type).
- If `/api/data` is fine but the page values stay `--`, look at the browser console (long-press address bar → "Inspect" or use desktop browser).

### LED buttons don't toggle the physical LED
- Check the LED resistor isn't shorted; the LEDs aren't reversed (long leg = anode = the GPIO side).
- Check the browser console for failed `POST /api/led` requests.

### Connecting to WiFi never finishes
- Hotspot is 5 GHz - force 2.4 GHz (iPhone "Maximize Compatibility", Android band setting).
- iPhone hotspot went to sleep - keep the Personal Hotspot screen open.
- SSID/password typo - both are case-sensitive.

For more, see the [Workshop 3 troubleshooting guide](../troubleshooting.md).

---

**Complete code:** [code-web-dashboard.ino](code-web-dashboard.ino)
