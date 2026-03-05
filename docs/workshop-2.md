# Workshop 2: Group Projects

**Duration:** 1.5 hours
**Difficulty:** Intermediate

## Choose Your Project

In Workshop 2, you'll build one of four projects. Each teaches different skills while working with sensors and real-world data.

## Project Options

### Project 1: Sensor Logger
**Difficulty:** ⭐⭐ Beginner/Intermediate | **Time:** 1-1.5 hours

Read temperature, humidity, and light data. Log it to your computer via Serial monitor.

**You'll Learn:** DHT11 sensor integration, LDR usage, Serial communication, data formatting

**Key code snippet:**
```cpp
float temp = dht.readTemperature();
float hum = dht.readHumidity();
int light = analogRead(34);
Serial.print(temp); Serial.print(",");
Serial.print(hum); Serial.print(",");
Serial.println(light);
```

[View full Sensor Logger guide](3-workshop-2/project-sensor-logger/README.md)

---

### Project 2: LED Light Show
**Difficulty:** ⭐⭐ Intermediate | **Time:** 1-1.5 hours

Create animated LED patterns with 3 LEDs. Use buttons to control modes and speed.

**You'll Learn:** Multiple LED control, pattern programming, button state machines, timing

**Patterns include:** All Blink, Chase Sequence, Breathing Effect (PWM), Random Disco, Color Mixing

[View full LED Light Show guide](3-workshop-2/project-led-patterns/README.md)

---

### Project 3: Button Game
**Difficulty:** ⭐⭐⭐ Intermediate/Advanced | **Time:** 1.5-2 hours

Build a reaction timer or Simon Says memory game with LEDs and buttons.

**You'll Learn:** Game logic, multiple button handling, sequence generation, score tracking

**Two game modes:**
1. **Reaction Timer** — LED lights up randomly, measure your response time
2. **Memory Game** — Simon Says with LED sequences that get progressively longer

[View full Button Game guide](3-workshop-2/project-button-game/README.md)

---

### Project 4: Data Dashboard
**Difficulty:** ⭐⭐⭐⭐ Advanced | **Time:** 2 hours

Build a Python dashboard that reads sensor data from ESP32 and creates live graphs.

**You'll Learn:** Serial data logging to CSV, Python setup, data visualization with matplotlib, real-time graphing

**Requires:** Python installed on your computer, plus `pyserial` and `matplotlib` libraries

[View full Data Dashboard guide](3-workshop-2/project-data-dashboard/README.md)

---

## Project Comparison

| Project | LEDs | Buttons | Sensors | Python | Difficulty |
|---------|------|---------|---------|--------|------------|
| Sensor Logger | - | - | DHT11 + LDR | No | ⭐⭐ |
| LED Light Show | 3 | 2 | - | No | ⭐⭐ |
| Button Game | 4 | 4 | - | No | ⭐⭐⭐ |
| Data Dashboard | - | - | DHT11 + LDR | Yes | ⭐⭐⭐⭐ |

## Getting Started

1. **Review your homework** - Make sure you completed the inter-workshop homework
2. **Choose your project** - Pick one that matches your interests and skill level
3. **Gather components** - Check that you have everything needed
4. **Follow the guide** - Each project has detailed step-by-step instructions

## What's Next?

After Workshop 2, complete the [Inter-Workshop 2 Homework](inter-workshop-2.md) to prepare for Workshop 3's IoT projects!

## Extension Ideas

- Add sensors to the LED Light Show (react to light levels)
- Log Button Game scores to a dashboard
- Create a multi-sensor monitoring station
- Build a weather station with alerts

---

**Previous:** [Inter-Workshop Homework](inter-workshop.md) | **Next:** [Inter-Workshop 2 Homework](inter-workshop-2.md)
