# 🔧 Troubleshooting Master Guide

The definitive debugging reference for all workshops. If something isn't working, start here!

---

## Setup & Upload Issues

### "Board not found" error

**What it means:** Arduino IDE can't detect your ESP32.

**Fix:**
1. Check USB-C cable is plugged in firmly at both ends
2. Try a different USB port (avoid USB hubs)
3. Make sure you're using a **data** cable, not a charge-only cable — this is the #1 cause!
4. Restart Arduino IDE / Arduino Create
5. On Windows: check Device Manager for the COM port
6. On Mac: look for `/dev/cu.usbserial-*` in Tools → Port

### "Failed to get board info"

**What it means:** Board manager download failed.

**Fix:**
1. Check internet connection
2. Verify the ESP32 board URL is in Preferences:
   `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
3. Go to Tools → Board → Boards Manager, search "esp32", and install
4. Select "ESP32 Dev Module" as your board

### Upload fails with "A fatal error occurred: Failed to connect"

**What it means:** ESP32 isn't entering bootloader mode.

**Fix:**
1. Hold the **BOOT** button on the ESP32 while uploading
2. Release BOOT after you see "Connecting..." in the console
3. If that doesn't work, try: hold BOOT, press and release EN/RST, then release BOOT
4. Check your USB cable (data vs charge-only)

### "Sketch too large" error

**What it means:** Your program is too big for flash memory.

**Fix:**
1. Go to Tools → Partition Scheme → select "Huge APP" or "No OTA"
2. Remove unused `#include` libraries
3. Use `PROGMEM` for large strings (like HTML)
4. Reduce HTML size in web server projects

---

## Code & Compilation Issues

### "DHT not found" or library errors

**What it means:** A required library is missing.

**Fix:**
1. In Arduino IDE: Sketch → Include Library → Manage Libraries
2. In Arduino Create: Libraries tab (left sidebar)
3. Search for the library name and install it
4. Common libraries needed:
   - **DHT sensor library** by Adafruit (also install "Adafruit Unified Sensor")
   - **WiFi** (built-in with ESP32)
   - **WebServer** (built-in with ESP32)
   - **BluetoothSerial** (built-in with ESP32)

### Code won't compile

**What it means:** Syntax error in your code.

**Fix:**
1. Read the error message — it tells you the line number!
2. Check for typos (capitalization matters: `digitalWrite` not `digitalwrite`)
3. Check all brackets match: `{ }`, `( )`, `[ ]`
4. Check semicolons at end of lines `;`
5. Make sure `setup()` and `loop()` functions exist
6. Check variable names are consistent

### "was not declared in this scope"

**What it means:** You're using a variable or function that hasn't been defined.

**Fix:**
1. Check spelling of the variable/function name
2. Make sure the variable is declared before you use it
3. Check if it's defined inside a different function (scope issue)
4. Make sure you've included the right library

---

## Hardware Issues

### LED won't light up

**Debug steps:**
1. **Check polarity:** Long leg (anode) → GPIO pin side, short leg (cathode) → GND side
2. **Check the resistor** is connected in series (not bypassed)
3. **Test the LED:** Connect it directly to 3.3V through a 220Ω resistor to GND
4. **Check wires** are firmly inserted into breadboard holes
5. **Check the GPIO pin** — some ESP32 pins are input-only (GPIO 34-39)
6. **Try `digitalWrite(pin, HIGH)`** in Serial Monitor to confirm the pin works

### Button doesn't respond

**Debug steps:**
1. Check wiring matches the circuit diagram exactly
2. Make sure button straddles the center gap of the breadboard
3. Check `pinMode(pin, INPUT_PULLDOWN)` is in your `setup()`
4. Add `Serial.println(digitalRead(buttonPin))` to verify button state
5. Try a different button (they can be faulty)
6. Check for debouncing issues — add a 50ms delay after detecting a press

### DHT11 reads NaN (Not a Number)

**Debug steps:**
1. Check wiring: VCC → 3.3V, DATA → GPIO pin, GND → GND
2. Make sure pin 3 (NC) is not connected
3. Wait at least 2 seconds between readings
4. Install both "DHT sensor library" AND "Adafruit Unified Sensor" libraries
5. Try a different GPIO pin
6. Add a 10kΩ pull-up resistor between DATA and VCC (some modules need it)

### LDR always reads 0 or 4095

**Debug steps:**
1. Check voltage divider circuit: 3.3V → LDR → GPIO 34 → 10kΩ → GND
2. Make sure the 10kΩ resistor is connected properly
3. Use an analog-capable pin (GPIO 32-39)
4. Cover and uncover the sensor — value should change
5. Try `Serial.println(analogRead(pin))` to see raw values
6. Check that you're NOT using a digital-only pin

### Sensor readings seem wrong

**Debug steps:**
1. Check power supply — USB cable quality matters!
2. Make sure sensor has had time to stabilize (1-2 seconds after power-on)
3. Compare readings with a known source (thermometer, phone light meter)
4. Check for loose connections causing intermittent readings

---

## WiFi Issues

### Can't connect to WiFi

**Common causes and fixes:**
1. **Wrong credentials:** Double-check SSID and password (case-sensitive!)
2. **5 GHz network:** ESP32 only supports 2.4 GHz WiFi
3. **Network not found:** Make sure you're in range of the router
4. **Hidden network:** ESP32 may not find hidden SSIDs — unhide it temporarily
5. **Too many devices:** Some routers limit connections
6. Try connecting to a phone hotspot first (for testing)
7. Check Serial Monitor for specific WiFi error codes:
   - `WL_NO_SSID_AVAIL` — Network not found
   - `WL_CONNECT_FAILED` — Wrong password
   - `WL_DISCONNECTED` — Connection dropped

### Connected but can't access web page

**Debug steps:**
1. Note the IP address from Serial Monitor
2. Make sure your computer/phone is on the **same WiFi network**
3. Use `http://` not `https://`
4. Try pinging the ESP32: `ping IP_ADDRESS` from a terminal
5. Try a different browser
6. Check that your code calls `server.begin()`

### WiFi keeps disconnecting

**Fixes:**
1. Check power supply — brownouts cause WiFi drops
2. Use a quality USB cable (short, data-capable)
3. Move closer to the WiFi router
4. Add reconnection logic in your `loop()`:
   ```cpp
   if (WiFi.status() != WL_CONNECTED) {
     WiFi.reconnect();
   }
   ```

---

## Bluetooth Issues

### Can't find ESP32 device

**Debug steps:**
1. Check Serial Monitor — is "Bluetooth started!" printed?
2. Toggle Bluetooth off and on on your phone
3. Forget old ESP32 pairings and try again
4. Move phone closer to ESP32
5. Restart ESP32

### Connected but no data

**Debug steps:**
1. Make sure you're using a Bluetooth Serial Terminal app (not just paired)
2. Check that your code uses `SerialBT.available()` in `loop()`
3. Send data from Serial Monitor first to verify code works
4. Check for newline issues — some apps don't send `\n` automatically

### iOS can't connect

**Note:** iOS does NOT support Bluetooth Classic Serial. You have two options:
1. Use BLE (Bluetooth Low Energy) instead — more complex setup
2. Switch to a WiFi-based project (Weather Station or IoT Dashboard)

---

## Web Server Issues

### Page loads but shows "--" for all values

**Fixes:**
1. Check the API endpoint directly: visit `http://ESP32_IP/api/data`
2. Open browser console (F12) and look for JavaScript errors
3. Verify sensors are connected and reading correctly
4. Check that the DHT library is installed

### ESP32 crashes when accessing page

**Possible causes:**
1. Out of memory (too much HTML in strings)
2. Too many simultaneous connections

**Fixes:**
1. Reduce HTML size
2. Use `R"(...)` raw strings instead of concatenating `String` objects
3. Access from only one device at a time
4. Restart ESP32

---

## Power Issues

### ESP32 keeps resetting / "Brownout detector" message

**What it means:** Not enough power.

**Fixes:**
1. Use a quality USB cable (short cables are better)
2. Connect directly to computer (avoid USB hubs)
3. Try a different USB port (rear ports on desktops are often more powerful)
4. If using WiFi + sensors, power from a USB adapter rated at 1A or more

### Serial Monitor shows garbage characters

**Fix:**
1. Make sure baud rate in Serial Monitor matches your code (`Serial.begin(9600)` → set monitor to 9600)
2. Press the EN/RST button to restart the ESP32
3. Close and reopen Serial Monitor

---

## General Debugging Tips

- **Read error messages carefully** — they usually tell you the problem!
- **Always check Serial Monitor** — it shows what the board is doing
- **Change one thing at a time** — makes debugging easier
- **Google the exact error message** — someone has probably had it before!
- **Check connections first** — 90% of hardware problems are loose wires
- **Use Serial.println() liberally** — add print statements to trace code flow
- **Test components individually** — before combining, make sure each part works alone
- **Check your USB cable** — charge-only cables are the most common hidden issue

---

**Still stuck?** Open an [Issue](https://github.com/zoharsf/embedded-electronics-101/issues) and we'll help!
