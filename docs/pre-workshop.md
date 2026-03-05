# Pre-Workshop Homework

**Time Required:** 30-45 minutes
**When to Complete:** Before Workshop 1

## Overview

Before attending Workshop 1, you'll need to set up your development environment and learn some basic concepts. This homework ensures everyone starts on the same page!

## What You'll Do

1. **Learn basic electronics concepts** (10 min) - Understand voltage, current, and circuits
2. **Set up Arduino Cloud** (15 min) - Create your development environment
3. **Write your first sketch** (10 min) - Test your setup

---

## 1. Electronics Basics

Three core concepts — master these and you're good to go.

### Voltage (V) — The "Push"

Think of electricity like water flowing through a pipe:

- **Voltage = Water Pressure** (how hard it's pushing)
- Our projects use **3.3V or 5V** (low, safe voltages)

### Current (I) — The "Flow"

- **Current = Water Flow** (how much water moves)
- Measured in **Amps (A)** or **Milliamps (mA)**
- Typical LED: ~20mA

### Resistance (R) — The "Brake"

- **Resistance = Narrow Pipe** (slows down flow)
- Measured in **Ohms (Ω)**
- 220Ω resistor = perfect for LEDs

**The magic formula (Ohm's Law):**
```
Voltage = Current × Resistance
V = I × R
```

### LEDs: Two Key Rules

1. **Polarity matters:** Long leg (+) goes to the GPIO pin side, short leg (-) goes to ground
2. **Always use a resistor:** Without one, the LED draws too much current and burns out. Use 220Ω.

[View full electronics basics guide](0-pre-workshop/01-basics.md)

---

## 2. Arduino Cloud Setup

Set up your development environment:

1. Go to [Arduino Cloud](https://create.arduino.cc/) and create an account
2. Install the Arduino Create Agent when prompted
3. Connect your ESP32 via USB-C
4. Select **ESP32 Dev Module** as your board
5. Verify the connection works (green checkmark)

**Troubleshooting:**
- Make sure you're using a **data** cable, not a charge-only cable
- Try a different USB port if the board isn't detected
- On Windows, you may need to install CP2102 drivers

[View detailed Arduino setup guide](0-pre-workshop/02-arduino-setup.md)

---

## 3. First Sketch (Optional but Recommended)

Write and upload your first program to test everything works:

```cpp
void setup() {
  Serial.begin(9600);
  Serial.println("Hello from ESP32!");
}

void loop() {
  Serial.println("I'm alive!");
  delay(2000);
}
```

**Key concepts:**
- `setup()` — runs once when the board powers on
- `loop()` — runs forever, over and over
- `Serial.println()` — sends text to Serial Monitor for debugging

[View first sketch tutorial](0-pre-workshop/03-first-sketch.md)

---

## Homework Checklist

- [ ] Understand voltage, current, and resistance
- [ ] Arduino Cloud account created
- [ ] ESP32 connected and recognized
- [ ] (Optional) First sketch uploaded and running

[View full homework checklist](0-pre-workshop/homework-checklist.md)

## Ready for Workshop 1?

Once you've completed the homework:
- ✅ You have Arduino Cloud set up
- ✅ Your ESP32 can connect and upload code
- ✅ You understand basic electronics concepts

**Next Step:** [Workshop 1: Basics & First Circuit](workshop-1.md)

## Need Help?

Check the [troubleshooting guide](resources.md#troubleshooting) if you encounter issues.
