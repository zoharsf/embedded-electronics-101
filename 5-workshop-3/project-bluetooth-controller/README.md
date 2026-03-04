# 🔵 Project 2: Bluetooth Controller

## What You'll Build

A Bluetooth-controlled LED system where you send commands from your phone to control LEDs, read sensor data, and get status feedback — all wirelessly!

**Control from:** Any Android phone with Serial Bluetooth Terminal app

---

## Hardware Setup

### Components Needed
- 3x LEDs (red, yellow, green)
- 3x 220Ω resistors
- 1x DHT11 sensor (temperature & humidity)
- Jumper wires

### Circuit Connections

| Component | ESP32 Pin | Notes |
|-----------|-----------|-------|
| Red LED (+) | GPIO 25 | Through 220Ω resistor to GND |
| Yellow LED (+) | GPIO 26 | Through 220Ω resistor to GND |
| Green LED (+) | GPIO 27 | Through 220Ω resistor to GND |
| DHT11 VCC | 3.3V | Power |
| DHT11 DATA | GPIO 5 | Signal |
| DHT11 GND | GND | Ground |

### Breadboard Layout

```
ESP32        Breadboard
GPIO 25 ──── [220Ω] ──── LED Red (+) ──── GND
GPIO 26 ──── [220Ω] ──── LED Yellow (+) ── GND
GPIO 27 ──── [220Ω] ──── LED Green (+) ─── GND
GPIO 5  ──── DHT11 DATA
3.3V    ──── DHT11 VCC
GND     ──── DHT11 GND
```

---

## Step-by-Step Build

### Step 1: Build the Circuit (10 min)

1. Place 3 LEDs on the breadboard
2. Connect each LED anode (long leg) through a 220Ω resistor to its GPIO pin
3. Connect each LED cathode (short leg) to GND
4. Connect DHT11 sensor (VCC → 3.3V, DATA → GPIO 5, GND → GND)
5. Verify all connections

### Step 2: Install Phone App (3 min)

1. On your Android phone, install **Serial Bluetooth Terminal** from the Play Store
2. [Download link](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal)

### Step 3: Upload Code (3 min)

1. Open [code-bluetooth-controller.ino](code-bluetooth-controller.ino) in Arduino IDE
2. Upload to ESP32
3. Open Serial Monitor (9600 baud)
4. You should see: `Bluetooth started! Pair with 'ESP32_Controller'`

### Step 4: Pair and Connect (5 min)

1. On your phone: Settings → Bluetooth → Pair with "ESP32_Controller"
2. Open Serial Bluetooth Terminal app
3. Tap "Devices" → Select "ESP32_Controller"
4. You should see: `Welcome! Type HELP for commands.`

---

## Command Reference

Send these commands from your phone:

| Command | Action |
|---------|--------|
| `RED:ON` | Turn red LED on |
| `RED:OFF` | Turn red LED off |
| `YELLOW:ON` | Turn yellow LED on |
| `YELLOW:OFF` | Turn yellow LED off |
| `GREEN:ON` | Turn green LED on |
| `GREEN:OFF` | Turn green LED off |
| `ALL:ON` | Turn all LEDs on |
| `ALL:OFF` | Turn all LEDs off |
| `BLINK` | Blink all LEDs 3 times |
| `TEMP` | Get temperature reading |
| `HUMIDITY` | Get humidity reading |
| `STATUS` | Show all LED states and sensor data |
| `HELP` | Show available commands |

---

## Code Overview

The code:
- Creates a Bluetooth Serial device named "ESP32_Controller"
- Listens for text commands over Bluetooth
- Parses commands and controls hardware
- Sends feedback messages back to your phone
- Supports LED control, sensor reading, and status queries

---

## Customization Ideas

### Beginner
- Change LED colors or add more LEDs
- Add new commands (e.g., `FADE` for PWM dimming)
- Change the Bluetooth device name
- Add a startup LED animation

### Intermediate
- Control LED brightness with PWM (`RED:128` for half brightness)
- Add a buzzer and sound commands
- Create LED patterns (chase, rainbow, alternating)
- Add button input and send notifications to phone

### Advanced
- Build a custom phone app with MIT App Inventor
- Add motor control for a robot
- Implement a command queue
- Add PIN-based security

---

## Troubleshooting

See [troubleshooting.md](../troubleshooting.md) for common issues.

**Bluetooth-specific issues:**
- **Can't find "ESP32_Controller":** Restart ESP32, toggle phone Bluetooth
- **Connected but no response:** Make sure Serial Bluetooth Terminal is connected (not just paired)
- **Garbage text received:** Check baud rate in Serial Monitor matches code (9600)
- **iOS users:** Bluetooth Classic Serial is not supported on iOS. Use WiFi Weather Station or IoT Dashboard project instead.

---

**Complete code:** [code-bluetooth-controller.ino](code-bluetooth-controller.ino)
