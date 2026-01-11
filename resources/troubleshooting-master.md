# 🔧 Troubleshooting Master Guide

## Setup Issues

### "Board not found" error

**What it means:** Arduino IDE can't find your ESP32.

**Fix:**
1. Check USB-C cable is plugged in
2. Try a different USB port
3. Restart Arduino Create

### "Failed to get board info"

**What it means:** Board manager download failed.

**Fix:**
1. Check internet connection
2. Try again

---

## Code Issues

### "DHT not found" error

**What it means:** Missing DHT library.

**Fix:**
1. In Arduino Create → Libraries (left sidebar)
2. Search "DHT"
3. Install "DHT sensor library by Adafruit"
4. Try uploading again

### Code won't compile

**What it means:** There was a problem compiling your code.

**Fix:**
1. Check for typos (capitalization matters!)
2. Check all brackets match: { }, ( ), [ ]
3. Check semicolons at end of lines

---

## Hardware Issues

### LED won't light up

**Debug steps:**
1. Check LED polarity (long leg = positive!)
2. Check resistor is connected
3. Try a different LED 
4. Check wires are inserted firmly into breadboard

### Button doesn't work

**Debug steps:**
1. Check wiring matches circuit diagram
2. Check wires are inserted firmly into breadboard
3. Try a different button

### Sensor always reads same value

**Debug steps:**
1. Check connections wires are inserted firmly into breadboard
2. Try restarting the board
3. Try a different GPIO pin

---

## General Tips

- **Read error messages carefully** - They usually tell you the problem!
- **Always check Serial Monitor** - It shows what the board is doing
- **Change one thing at a time** - Makes debugging easier
- **Google the error** - Probably someone had it before!