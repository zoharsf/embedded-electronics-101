# Inter-Workshop Homework

**Time Required:** 30-45 minutes
**When to Complete:** Between Workshop 1 and Workshop 2

## Overview

This homework prepares you for Workshop 2, where you'll work with sensors to read real-world data. You'll learn about different types of sensors and practice modifying code.

## What You'll Learn

1. **Sensor Basics** (15 min) - How sensors work and common types
2. **Code Tweaking** (20 min) - Practice modifying Arduino sketches
3. **Project Selection** (10 min) - Choose your Workshop 2 project

---

## 1. Sensor Basics

### DHT11 — Temperature & Humidity Sensor

- **Temperature Range:** 0-50°C (±2°C accuracy)
- **Humidity Range:** 20-90% RH (±5% accuracy)
- **Important:** Wait at least 2 seconds between readings

**Wiring:** VCC → 3.3V, DATA → GPIO pin, GND → GND

```cpp
#include <DHT.h>
DHT dht(5, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  Serial.print("Temp: "); Serial.print(temp);
  Serial.print("C  Humidity: "); Serial.print(hum);
  Serial.println("%");
  delay(2000);
}
```

### LDR — Light-Dependent Resistor

- Resistance changes with light (dark = high, bright = low)
- Use a voltage divider circuit with a 10kΩ resistor
- Returns values 0 (dark) to 4095 (bright)

```cpp
int lightLevel = analogRead(34);  // Read light sensor
Serial.println(lightLevel);       // 0 = dark, 4095 = bright
```

[View full sensor basics guide](https://github.com/zoharsf/embedded-electronics-101/blob/main/2-inter-workshop/01-sensor-basics.md)

---

## 2. Code Tweaking Practice

Get comfortable modifying existing code with these exercises:

1. **Change the blink speed** — modify `delay()` values
2. **Add a second LED** — duplicate the blink code for a new pin
3. **Threshold detection** — turn on LED when temperature exceeds a value
4. **Serial formatting** — output sensor data in CSV format
5. **Combine sensors** — read both DHT11 and LDR in one sketch

[View all code tweaking exercises with solutions](https://github.com/zoharsf/embedded-electronics-101/blob/main/2-inter-workshop/02-code-tweaking.md)

---

## 3. Project Selection

Choose which project you'll build in Workshop 2:

| Project | What You'll Build | Difficulty |
|---------|-------------------|------------|
| **Sensor Logger** | Log temp/humidity to Serial | ⭐⭐ |
| **LED Light Show** | Patterns with 3 LEDs + buttons | ⭐⭐ |
| **Button Game** | Reaction timer or Simon Says | ⭐⭐⭐ |
| **Data Dashboard** | Python visualization of sensor data | ⭐⭐⭐⭐ |

[View detailed project picker guide](https://github.com/zoharsf/embedded-electronics-101/blob/main/2-inter-workshop/project-picker.md)

---

## Homework Checklist

- [ ] Read and understand sensor basics
- [ ] Complete at least 3 code tweaking exercises
- [ ] Choose your Workshop 2 project
- [ ] Review the requirements for your chosen project

## Ready for Workshop 2?

**Next Step:** [Workshop 2: Group Projects](workshop-2.md)

## Need Help?

Check the [troubleshooting guide](resources.md#troubleshooting) if you encounter issues.

---

**Previous:** [Workshop 1](workshop-1.md) | **Next:** [Workshop 2](workshop-2.md)
