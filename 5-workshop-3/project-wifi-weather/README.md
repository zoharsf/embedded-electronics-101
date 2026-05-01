# Project 1: WiFi Weather Station

## What You'll Build

A web-based weather station displaying live temperature, humidity, and light, accessible from your phone's browser.

You will:
1. Turn your phone into a 2.4 GHz hotspot.
2. Have the ESP32 join your hotspot.
3. Open the ESP32's IP address from the same phone's browser to see your dashboard.

---

## Hardware Setup

### Components Needed (all in your kit)
- 1x DHT11 sensor (temperature & humidity)
- 1x LDR (light sensor)
- 1x 10kΩ resistor
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

The LDR and 10kΩ form a voltage divider: as the LDR's resistance changes with light, the voltage at GPIO 34 changes between 0 and 3.3V.

---

## Step-by-Step Build

### Step 1: Build the circuit (10 min)
1. Plug in the DHT11. Power and data wires to ESP32.
2. Build the LDR voltage divider with the 10kΩ resistor.
3. Double-check ground connections.

### Step 2: Turn on your phone hotspot (2 min)
- **iPhone:** Settings → Personal Hotspot → toggle "Allow Others to Join". Enable "Maximize Compatibility" (this forces 2.4 GHz - the ESP32 cannot connect to 5 GHz). Keep this screen open while pairing the ESP32.
- **Android:** Settings → Network → Hotspot. Set band to "2.4 GHz". Set a memorable SSID and password (8+ characters).

### Step 3: Configure the sketch (3 min)
Open [code-wifi-weather.ino](code-wifi-weather.ino) and paste your hotspot's SSID and password:

```cpp
const char* ssid     = "YOUR_PHONE_HOTSPOT_NAME";
const char* password = "YOUR_HOTSPOT_PASSWORD";
```

The values are case-sensitive - typos here are the #1 cause of failure to connect.

### Step 4: Upload and watch the Serial Monitor (5 min)
1. Make sure the DHT library is installed (Library Manager → search "DHT sensor library" by Adafruit).
2. Upload the sketch.
3. Open Serial Monitor at 9600 baud.

You should see:
```
Connecting to WiFi....
Connected!
IP Address: 172.20.10.x   (or 192.168.x.x depending on phone)
Open browser to: http://172.20.10.x
```

If it sits on `Connecting to WiFi.....` forever, see the [troubleshooting section](#troubleshooting) below.

### Step 5: Open the dashboard (1 min)
On the **same phone** that's running the hotspot, open Safari/Chrome and go to the IP address from the Serial Monitor. You should see your live sensor dashboard.

---

## Code Overview

The sketch:
- Reads the DHT11 every 2 seconds.
- Reads the LDR analog value (0-4095) on each request.
- Serves an HTML page at `/` and a JSON endpoint at `/api/data`.
- The HTML page polls `/api/data` every 5 seconds and updates the values without a full reload.

---

## Dashboard Features

- Temperature in Celsius and Fahrenheit
- Humidity percentage
- Light level (raw 0-4095, with "dark/bright" hint)
- Auto-refresh every 5 seconds
- Mobile-friendly responsive layout

---

## Stretch Goals (with acceptance criteria)

### Beginner
- **Change refresh rate.** Make it update every second. *Done when:* you watch the value tick once per second.
- **Restyle the page.** Pick a new color scheme by editing the CSS gradient (search for `#667eea`). *Done when:* the page looks visually different.
- **Add a "feels like" reading** by combining temperature and humidity into a heat-index estimate. *Done when:* the new value appears on the page.

### Intermediate
- **Track min and max** for temperature since boot, and show them in the dashboard. *Done when:* breathe on the sensor and watch the max climb but not retreat.
- **Add a `/api/csv` endpoint** that returns all current values as a single CSV line. *Done when:* `curl http://<esp-ip>/api/csv` returns a CSV row.
- **Add a "last updated" timestamp** that shows seconds since the page was loaded. *Done when:* the time counter increments live in the browser.

### Advanced
- **Cloud forwarding.** Once per minute, POST current readings to a free webhook (try webhook.site). *Done when:* you see your data appear on the webhook capture page.
- **Multi-device.** Get a second ESP32 (one per group), have both connect to the same hotspot, and aggregate readings on the one serving the dashboard. *Done when:* the dashboard shows two temperature columns.
- **History buffer.** Keep the last 60 readings in a ring buffer and add a sparkline using inline SVG. *Done when:* the line in the dashboard tracks recent changes.

---

## Troubleshooting

### "Connecting to WiFi....." never finishes
- **Hotspot is 5 GHz.** ESP32 cannot connect to 5 GHz. Force 2.4 GHz (iPhone: Maximize Compatibility, Android: band setting).
- **iPhone hotspot went to sleep.** Keep the Personal Hotspot screen open until the ESP32 connects.
- **SSID or password typo.** Both are case-sensitive. No quotes inside the values.
- **Hotspot password too short.** Some Android variants reject passwords under 8 characters.

### Connected, but the IP address never loads in my browser
- Confirm your phone is connected to **its own hotspot** (some phones don't list it - check Settings → WiFi).
- Use the IP exactly as printed (it's usually `172.20.10.x` on iOS, `192.168.x.x` on Android).
- Try `http://` not `https://`.

### Page loads but all values show `--`
- The DHT library isn't installed (compile would fail) - verify it's installed.
- DHT data wire is loose or on the wrong pin.
- LDR is on the wrong analog pin (must be 34, 35, 36, or 39 on most ESP32 dev boards).

For more, see the [Workshop 3 troubleshooting guide](../troubleshooting.md) and the [master troubleshooting guide](../../resources/troubleshooting-master.md).

---

**Complete code:** [code-wifi-weather.ino](code-wifi-weather.ino)
