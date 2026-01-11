# 🌡️ Project 1: Sensor Data Logger

## What You'll Build

A device that reads temperature and humidity from the DHT11 sensor and displays real-time data on your computer screen.

**Finished product:** Plug it in, watch temperature/humidity appear in real-time!

## Hardware Setup

### Connections

| DHT11 Sensor | ESP32 Pin |
|--------------|-----------|
| VCC (red) | 3.3V |
| DATA (yellow) | GPIO 5 |
| GND (black) | GND |

### Breadboard Layout

```
DHT11 sensor on left side of breadboard:
VCC → top rail (power)
DATA → GPIO 5 (any row)
GND → bottom rail (ground)
```

## Code

See [code-dht11-read.ino](code-dht11-read.ino) for complete sketch.

## Step-by-Step

1. **Build the circuit** (5 min)
   - Plug DHT11 into breadboard
   - Connect wires: VCC → 3.3V, DATA → GPIO5, GND → GND

2. **Install DHT library** (3 min)
   - In Arduino Create: Libraries → Search "DHT" → Install "DHT sensor library by Adafruit"

3. **Upload code** (3 min)
   - Copy [code-dht11-read.ino](code-dht11-read.ino)
   - Paste into Arduino Create
   - Click Upload

4. **View data** (2 min)
   - Click Serial Monitor (magnifying glass, top right)
   - Set baud to 9600
   - Watch temperature & humidity appear!

## Try These Experiments

- **Breathe on the sensor:** Watch humidity jump!
- **Hold it in warm hand:** Temperature rises
- **Wait 30 seconds:** Notice the 2-second lag? Sensors aren't instant!

## Troubleshooting

**No data appearing?**
- Check connections (DATA wire on GPIO5?)
- Check baud rate (9600)
- Reboot the board (unplug USB, replug)

**"DHT not found" error?**
- Did you install the library? (See Step 2)

---

Finished? Try extending it! See [Project Inspiration](/resources/inspiration.md)

