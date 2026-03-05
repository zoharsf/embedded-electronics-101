# Workshop 3: WiFi & Bluetooth IoT Projects

**Duration:** 1.5-2 hours
**Difficulty:** Intermediate to Advanced

## Choose Your IoT Project

In Workshop 3, you'll build connected devices that communicate wirelessly. Each project demonstrates real-world IoT applications.

## Project Options

### Project 1: WiFi Weather Station
**Difficulty:** ⭐⭐⭐ Intermediate | **Time:** 1.5 hours

Build a web-accessible weather station with temperature, humidity, and light sensors.

**What you'll build:** A web dashboard accessible from any browser on your network, showing real-time sensor data with auto-refresh.

**Circuit:**
```
DHT11: VCC→3.3V, DATA→GPIO 5, GND→GND
LDR:   3.3V→LDR→GPIO 34→10kΩ→GND
```

[View WiFi Weather Station guide](5-workshop-3/project-wifi-weather/README.md)

---

### Project 2: Bluetooth LED Controller
**Difficulty:** ⭐⭐ Beginner/Intermediate | **Time:** 1-1.5 hours

Control LEDs and read sensors from your phone using Bluetooth Serial commands.

**What you'll build:** A command-based system where you send text commands (like `RED:ON`, `TEMP`, `STATUS`) from your phone to control hardware.

**Commands include:** LED on/off, blink patterns, temperature/humidity readings, status queries

[View Bluetooth Controller guide](5-workshop-3/project-bluetooth-controller/README.md)

---

### Project 3: IoT Dashboard
**Difficulty:** ⭐⭐⭐⭐ Advanced | **Time:** 2 hours

Create a full-featured web dashboard with sensor monitoring, LED control, and a JSON API.

**What you'll build:** A modern dark-themed dashboard with real-time sensor cards, interactive LED toggle buttons, light level bar, and a REST API at `/api/data`.

**Features:** Temperature + humidity + light monitoring, LED control from browser, responsive mobile layout, JSON API for integration

[View IoT Dashboard guide](5-workshop-3/project-web-dashboard/README.md)

---

## Project Comparison

| Project | WiFi | Bluetooth | Sensors | Web UI | Difficulty |
|---------|------|-----------|---------|--------|------------|
| Weather Station | ✅ | - | DHT11 + LDR | Basic | ⭐⭐⭐ |
| Bluetooth Controller | - | ✅ | DHT11 | - | ⭐⭐ |
| IoT Dashboard | ✅ | - | DHT11 + LDR | Advanced | ⭐⭐⭐⭐ |

## Prerequisites

Before starting Workshop 3:
- ✅ Complete Inter-Workshop 2 Homework
- ✅ Have WiFi credentials ready (2.4 GHz network)
- ✅ Smartphone with Bluetooth (for Project 2)
- ✅ Basic understanding of HTML/CSS (for web projects)

## Troubleshooting

Common WiFi, Bluetooth, and web server issues:
[View Workshop 3 troubleshooting](5-workshop-3/troubleshooting.md)

## What's Next?

After Workshop 3, you have the skills to build real IoT projects! Check out:
- [25+ Project Ideas](resources.md#project-inspiration)
- Advanced topics: MQTT, cloud integration, machine learning
- Join the maker community and share your projects!

## Extension Ideas

- **Weather Station:** Add forecasts, email alerts, data logging
- **Bluetooth Controller:** Add voice control, automation, scheduling
- **IoT Dashboard:** Add cloud storage, remote access, mobile app

---

**Previous:** [Inter-Workshop 2 Homework](inter-workshop-2.md) | **Next:** [Project Ideas & Resources](resources.md)
