# Workshop 1: Basics & First Circuit

**Duration:** 1.5 hours
**Difficulty:** Beginner

## What You'll Build

Two interactive circuits:
1. **LED Blink** - Your first circuit with a blinking LED
2. **LED + Button** - Interactive circuit where a button controls an LED

## Learning Objectives

By the end of this workshop, you'll be able to:
- Build circuits on a breadboard
- Connect LEDs with proper resistors
- Wire buttons with proper pull-down configuration
- Write Arduino code for digital input/output
- Debug basic circuit issues

## Workshop Structure

### Part 1: Understanding the Hardware (15 min)
- ESP32 pinout and capabilities
- Breadboard basics and power rails
- Component identification

### Part 2: LED Blink Circuit (30 min)
- Build your first circuit
- Upload the blink code
- Understand the code structure
- Modify timing and experiment

### Part 3: Adding a Button (30 min)
- Add button to your circuit
- Learn about INPUT_PULLDOWN mode
- Write interactive code
- Test and debug

### Part 4: Experimentation (15 min)
- Try different LED patterns
- Add multiple LEDs
- Explore button debouncing

---

## Circuit 1: LED Blink

### Schematic

```
ESP32 Pin GPIO2 ─── [220Ω Resistor] ─── LED(+) ─── GND
```

### Build Steps

1. Insert LED into breadboard (long leg = positive)
2. Connect 220Ω resistor in series with the LED's positive leg
3. Wire ESP32 GPIO2 to the resistor
4. Wire LED's negative leg to ESP32 GND

### Code

```cpp
void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  Serial.println("LED Blink starting...");
}

void loop() {
  digitalWrite(2, HIGH);  // Turn LED on
  Serial.println("LED ON");
  delay(1000);            // Wait 1 second

  digitalWrite(2, LOW);   // Turn LED off
  Serial.println("LED OFF");
  delay(1000);            // Wait 1 second
}
```

---

## Circuit 2: LED + Button

### Schematic

```
ESP32 GPIO2 ── [220Ω] ── LED(+) ── GND

ESP32 GPIO4 ── [Button] ── GND
```

The ESP32's internal pull-down resistor keeps GPIO4 LOW until the button is pressed.

### Code

```cpp
const int LED_PIN = 2;
const int BUTTON_PIN = 4;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
  Serial.println("LED + Button ready!");
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Button pressed - LED ON");
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}
```

---

## Detailed Materials

For full step-by-step build instructions with breadboard layouts:

- [Circuit diagram guide](1-workshop-1/circuit-diagram.md)
- [LED blink code](https://github.com/zoharsf/embedded-electronics-101/blob/main/1-workshop-1/code-led-blink.ino)
- [LED button code](https://github.com/zoharsf/embedded-electronics-101/blob/main/1-workshop-1/code-led-button.ino)

### Troubleshooting

Common issues and solutions:
[View Workshop 1 troubleshooting](1-workshop-1/troubleshooting.md)

## What's Next?

After Workshop 1, complete the [Inter-Workshop Homework](inter-workshop.md) to prepare for Workshop 2!

## Extension Challenges

Want to go further? Try these:
1. **Multiple LEDs** - Add 2 more LEDs and create patterns
2. **Button Counter** - Count button presses and display with LEDs
3. **Reaction Game** - LED lights up randomly, press button quickly!
4. **Morse Code** - Blink messages in Morse code

---

**Previous:** [Pre-Workshop Homework](pre-workshop.md) | **Next:** [Inter-Workshop Homework](inter-workshop.md)
