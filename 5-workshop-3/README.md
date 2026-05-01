# Workshop 3: Connected IoT Projects (1.5 hours)

## Learning Objectives

By the end of this workshop, you will:
- Connect an ESP32 to a WiFi network (via your phone hotspot)
- Run a web server or Bluetooth service on the ESP32
- Build an interactive dashboard or controller you can use from your phone
- Understand the basic IoT communication loop: device → network → browser

---

## What You'll Build

**Choose ONE connected project:**
- **WiFi Weather Station** - browser dashboard showing live sensor data
- **Bluetooth Controller** - send commands from your phone to the ESP32 over Bluetooth (Android only)
- **IoT Dashboard** - full web app: sensor cards, LED control, JSON API

---

## The Network: Your Phone Is the WiFi

We are not using office or home WiFi today. Office networks often block ESP32-style devices, and home WiFi credentials are private. Instead, **each of you will turn your own phone into a WiFi hotspot**, and your ESP32 will connect to that hotspot. You'll then open the ESP32's webpage in your phone's browser - the phone is talking to itself, basically, over its own little WiFi network.

This sidesteps every corporate-network problem and means everyone has a self-contained setup that works the same way at home.

**One catch:** the ESP32 only supports 2.4 GHz WiFi.
- **iPhone:** turn on Personal Hotspot in Settings, then enable "Maximize Compatibility" (this forces 2.4 GHz). On older iPhones the hotspot is 2.4 GHz by default.
- **Android:** turn on the hotspot in Settings → Network → Hotspot. In hotspot settings make sure the band is set to "2.4 GHz" (some phones default to 5 GHz or auto).

We'll do this together at minute 5. You don't need to do anything before arriving.

---

## Workshop Timeline (90 min)

| Time | Activity | Duration |
|------|----------|----------|
| 0:00 | Welcome, what we're building, project pick recap | 5 min |
| 0:05 | Phone hotspot setup walkthrough (everyone) | 8 min |
| 0:13 | Build the circuit for your project | 17 min |
| 0:30 | Paste hotspot SSID + password, upload, first connect | 20 min |
| 0:50 | Open the dashboard, customize, attempt stretch goals | 30 min |
| 1:20 | Demo lap - everyone shows their phone screen | 8 min |
| 1:28 | Wrap, take-home tips | 2 min |

If your project lights up early, head straight to the stretch goals in your project's README. Each one has a "you'll know it works when..." line so you don't need me to verify.

---

## What You Need Today

**From your kit:**
- ESP32 board, breadboard, jumpers, USB-C cable
- DHT11 sensor (all three projects use it)
- LDR + 10kΩ resistor (Weather Station and IoT Dashboard)
- LEDs and 220Ω resistors (Bluetooth Controller and IoT Dashboard)

**From you:**
- Laptop with Arduino IDE or Arduino Cloud working (you set this up before Workshop 1)
- Your phone, with a working data plan (or office WiFi - the hotspot will share whatever the phone is connected to)
- For the Bluetooth project: an Android phone with the **Serial Bluetooth Terminal** app pre-installed. iPhones cannot do this project (iOS does not support Bluetooth Classic Serial).

---

## Projects for Today

### Project 1: WiFi Weather Station
→ [WiFi Weather Station Guide](./project-wifi-weather/README.md)

A clean web dashboard showing live temperature, humidity, and light. Mobile-friendly. Updates every 5 seconds.

### Project 2: Bluetooth Controller
→ [Bluetooth Controller Guide](./project-bluetooth-controller/README.md)

Type commands like `RED:ON` or `TEMP` from your phone over Bluetooth. The ESP32 responds with confirmations and sensor readings.

### Project 3: IoT Dashboard
→ [IoT Dashboard Guide](./project-web-dashboard/README.md)

The biggest project: real-time sensor cards, two LEDs you can toggle from the browser, JSON API at `/api/data`. The most "real-app" feel of the three.

---

## If Something Doesn't Work

→ [Workshop 3 Troubleshooting](./troubleshooting.md) - covers the hotspot path explicitly.

Top three things to check, in order:
1. Is your phone hotspot **on**, **2.4 GHz**, and **not auto-sleeping**? (iPhone: keep the Settings → Personal Hotspot screen open while pairing.)
2. Does the SSID and password you pasted into the sketch match your hotspot **exactly** (case-sensitive)?
3. Is your phone actually connected to your hotspot itself? (Some phones only see their hotspot once another device joins.)

---

## After Workshop 3

You leave with:
- A working connected ESP32 project
- A WiFi/web-server pattern you can apply to anything
- Skills to extend any of these projects independently

**For more ideas:** [Project Inspiration](../resources/inspiration.md) (25+ projects).

---

**Ready to go wireless?** Pick your project above and let's build something connected.
