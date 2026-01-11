# 📊 Project 4: Data Dashboard

## What You'll Build

A complete data logging and visualization system that collects sensor data over time and displays it in a dashboard!

**Finished product:** 
- ESP32 collects temperature, humidity, and light data
- Data is logged to Serial in CSV format
- Python script captures and visualizes the data
- Real-time graphs update as data comes in

**Difficulty:** ⭐⭐⭐ (Requires Python setup)

---

## Hardware Setup

### Components Needed
- 1x DHT11 sensor (temperature & humidity)
- 1x LDR (light-dependent resistor)
- 1x 10kΩ resistor (for LDR voltage divider)
- Jumper wires

### Circuit Connections

| Component | ESP32 Pin | Notes |
|-----------|-----------|-------|
| DHT11 VCC | 3.3V | Power |
| DHT11 DATA | GPIO 5 | Signal |
| DHT11 GND | GND | Ground |
| LDR one end | 3.3V | Forms voltage divider |
| LDR other end | GPIO 34 (A0) | Analog input |
| 10kΩ resistor | Between GPIO 34 and GND | Pull-down |

### Breadboard Layout

```
DHT11 Sensor:
  VCC  ──→ 3.3V
  DATA ──→ GPIO 5
  GND  ──→ GND

LDR Circuit (voltage divider):
  3.3V ──[LDR]──┬──→ GPIO 34 (analog read)
                │
             [10kΩ]
                │
               GND
```

---

## Software Requirements

### Part 1: Arduino Code (ESP32)
See [code-data-logger.ino](code-data-logger.ino)

### Part 2: Python Dashboard
See [dashboard.py](dashboard.py)

**Python libraries needed:**
```bash
pip install pyserial matplotlib pandas
```

---

## Step-by-Step Build

### Step 1: Build the Circuit (10 min)

1. Connect DHT11 sensor:
   - VCC → 3.3V
   - DATA → GPIO 5
   - GND → GND

2. Build LDR voltage divider:
   - LDR from 3.3V to GPIO 34
   - 10kΩ resistor from GPIO 34 to GND

**Test:** Upload Arduino code, open Serial Monitor, you should see CSV data!

### Step 2: Set Up Python Environment (10 min)

1. Install Python 3.7+ (if not already installed)
2. Install required libraries:
   ```bash
   pip install pyserial matplotlib pandas
   ```

3. Download [dashboard.py](dashboard.py)

### Step 3: Run the Dashboard (5 min)

1. Find your ESP32's serial port:
   - **macOS:** Usually `/dev/cu.usbserial-*` or `/dev/cu.wchusbserial*`
   - **Windows:** Usually `COM3`, `COM4`, etc.
   - **Linux:** Usually `/dev/ttyUSB0`

2. Edit `dashboard.py` line 8:
   ```python
   SERIAL_PORT = '/dev/cu.usbserial-XXX'  # Change to your port
   ```

3. Run the script:
   ```bash
   python dashboard.py
   ```

4. Watch the graphs update in real-time!

---

## Understanding the Data

### CSV Format

The ESP32 outputs data in this format:
```
timestamp,temperature,humidity,light
0,23.5,45.2,1234
2000,23.6,45.1,1245
4000,23.5,45.3,1256
```

**Columns:**
- `timestamp`: Milliseconds since start
- `temperature`: Degrees Celsius
- `humidity`: Percentage (0-100%)
- `light`: Raw ADC value (0-4095)

### Python Dashboard Features

The dashboard shows 3 real-time graphs:
1. **Temperature over time** (°C)
2. **Humidity over time** (%)
3. **Light level over time** (0-4095)

All graphs update every 2 seconds with new data!

---

## Experiments to Try

### Beginner
- Change the logging interval (currently 2 seconds)
- Add more data points to each graph
- Change graph colors/styles

### Intermediate
- Add data export to CSV file
- Calculate and display statistics (min, max, average)
- Add alerts (e.g., if temperature > 30°C)

### Advanced
- Add WiFi connectivity (send data to cloud)
- Create a web-based dashboard (using Flask or Node.js)
- Store data in a database (SQLite or Firebase)
- Add multiple ESP32 devices to one dashboard

---

## Troubleshooting

### ESP32 Issues

**"DHT not found" error:**
- Install DHT sensor library: Libraries → "DHT sensor library" by Adafruit
- Check wiring (DATA on GPIO 5?)

**Light sensor always reads 0 or 4095:**
- Check LDR connections
- Verify 10kΩ resistor is connected
- Try reading raw values in Serial Monitor

### Python Dashboard Issues

**"Serial port not found":**
- Check ESP32 is plugged in
- Verify correct port name in code
- On macOS/Linux: You may need `sudo` permissions

**"Module not found" error:**
- Install missing library: `pip install <library-name>`
- Verify you're using the correct Python version

**Graphs don't update:**
- Check Serial Monitor shows data flowing
- Verify baud rate matches (9600)
- Restart both Arduino and Python script

**Graphs look weird:**
- Close Serial Monitor (can't have two programs reading same port)
- Check data format matches CSV (timestamp,temp,humidity,light)

---

## Code Walkthrough

### Arduino Code Highlights

```cpp
// Read sensors
float temp = dht.readTemperature();
int light = analogRead(LIGHT_PIN);

// Output as CSV
Serial.print(millis());      // Timestamp
Serial.print(",");
Serial.print(temp);          // Temperature
Serial.print(",");
Serial.print(humidity);      // Humidity
Serial.print(",");
Serial.println(light);       // Light level
```

### Python Code Highlights

```python
# Read serial data
line = ser.readline().decode('utf-8').strip()
data = line.split(',')

# Parse values
timestamp = float(data[0])
temperature = float(data[1])
humidity = float(data[2])
light = int(data[3])

# Update graph
ax1.plot(timestamps, temperatures)
plt.pause(0.1)  # Redraw
```

---

## Take It Further

### Ideas for Home

**Hardware additions:**
- Add more sensors (pressure, CO2, sound)
- Add SD card module (log data offline)
- Add RTC module (real timestamps)
- Battery power (make it portable)

**Software improvements:**
- Export to CSV for Excel analysis
- Email alerts when thresholds exceeded
- Mobile app dashboard (Blynk, MIT App Inventor)
- Machine learning (predict temperature trends)

**Advanced projects:**
- Multi-room monitoring (multiple ESP32s)
- Weather station (add outdoor sensors)
- Smart home automation (control based on data)
- Web API (other apps can access your data)

---

## Sample Output

```
=== Data Logger Dashboard ===
Collecting data from ESP32...

Current readings:
  Temperature: 23.5°C
  Humidity: 45.2%
  Light: 1234

[Graph shows real-time line plots updating every 2 seconds]

Press Ctrl+C to stop and save data.
```

---

## Resources

- [DHT11 Datasheet](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf)
- [ESP32 Analog Read Guide](https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/)
- [Matplotlib Documentation](https://matplotlib.org/stable/contents.html)
- [PySerial Documentation](https://pyserial.readthedocs.io/)

---

**Questions?** Check [Resources](/resources/) or open an [Issue](https://github.com/zoharsf/embedded-electronics-101/issues)!
