# Inter-Workshop 2 Homework

**Time Required:** 45-60 minutes
**When to Complete:** Between Workshop 2 and Workshop 3

## Overview

This homework prepares you for Workshop 3, where you'll build connected IoT projects using WiFi and Bluetooth. You'll learn the fundamentals of wireless communication and web servers.

## What You'll Learn

1. **WiFi Basics** (15 min) - Connect ESP32 to WiFi networks
2. **Bluetooth Basics** (15 min) - Understand Bluetooth communication
3. **Web Server Fundamentals** (15 min) - Create web interfaces
4. **Project Selection** (10 min) - Choose your Workshop 3 project

---

## 1. WiFi Basics

The ESP32 supports 2.4 GHz WiFi (not 5 GHz). It can operate as a station (connect to router), access point (create its own network), or both.

### Connecting to WiFi

```cpp
#include <WiFi.h>

const char* ssid = "YourNetwork";
const char* password = "YourPassword";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
```

[View full WiFi basics guide](4-inter-workshop/01-wifi-basics.md)

---

## 2. Bluetooth Basics

The ESP32 supports both **Bluetooth Classic** (easier, used in Workshop 3) and **BLE** (more power-efficient).

### Simple Bluetooth Echo

```cpp
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32_Device");
  Serial.println("Bluetooth started!");
}

void loop() {
  if (SerialBT.available()) {
    char received = SerialBT.read();
    SerialBT.print("Echo: ");
    SerialBT.println(received);
  }
}
```

**To test:** Pair your phone, then use Serial Bluetooth Terminal app to send messages.

[View full Bluetooth basics guide](4-inter-workshop/02-bluetooth-basics.md)

---

## 3. Web Server Fundamentals

Your ESP32 can host web pages accessible from any browser on your network:

```cpp
#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

void handleRoot() {
  server.send(200, "text/html",
    "<h1>Hello from ESP32!</h1>");
}

void setup() {
  // ... WiFi connection code ...
  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}
```

Key concepts: routes map URLs to handler functions, JSON APIs enable dynamic updates, CSS makes dashboards look professional.

[View full web server basics guide](4-inter-workshop/03-web-server-basics.md)

---

## 4. Project Selection

| Project | Technology | Difficulty |
|---------|-----------|------------|
| **WiFi Weather Station** | WiFi + Web Server | ⭐⭐⭐ |
| **Bluetooth Controller** | Bluetooth Serial | ⭐⭐ |
| **IoT Dashboard** | WiFi + Advanced Web UI + API | ⭐⭐⭐⭐ |

[View detailed project picker guide](4-inter-workshop/project-picker.md)

---

## Homework Checklist

- [ ] Read and understand WiFi connectivity basics
- [ ] Learn about Bluetooth communication options
- [ ] Review web server fundamentals and HTML basics
- [ ] Choose your Workshop 3 project
- [ ] Have your WiFi network credentials ready

## Important Notes

- **WiFi:** Must be a 2.4 GHz network. Have SSID and password ready.
- **Bluetooth:** Android phone needed for Bluetooth Classic. Install [Serial Bluetooth Terminal](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal). iOS does not support BT Classic — use a WiFi project.

**Next Step:** [Workshop 3: WiFi & Bluetooth](workshop-3.md)

## Need Help?

Check the [troubleshooting guide](resources.md#troubleshooting) if you encounter issues.

---

**Previous:** [Workshop 2](workshop-2.md) | **Next:** [Workshop 3](workshop-3.md)
