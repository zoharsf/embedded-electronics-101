# 💡 Project 2: LED Light Show

## What You'll Build

A programmable light show using multiple colored LEDs and buttons. Create custom patterns, animations, and effects!

**Finished product:** Press buttons to cycle through different light patterns (disco mode, breathing effect, chase sequence, etc.)

---

## Hardware Setup

### Components Needed
- 3x LEDs (different colors: red, green, blue recommended)
- 3x 220Ω resistors (one for each LED)
- 2x Push buttons
- Jumper wires

### Circuit Connections

| Component | ESP32 Pin | Notes |
|-----------|-----------|-------|
| LED 1 (Red) | GPIO 2 | Via 220Ω resistor |
| LED 2 (Green) | GPIO 4 | Via 220Ω resistor |
| LED 3 (Blue) | GPIO 5 | Via 220Ω resistor |
| Button 1 (Mode) | GPIO 18 | With internal pull-down |
| Button 2 (Speed) | GPIO 19 | With internal pull-down |
| All LED cathodes (-) | GND | Common ground |

### Breadboard Layout

```
ESP32                    LEDs (via resistors)
┌────┐                   
│GPIO2├──[220Ω]──[LED Red +]───┐
│GPIO4├──[220Ω]──[LED Green +]─┤
│GPIO5├──[220Ω]──[LED Blue +]──┼──→ All to GND
│ GND ├───────────────────────┘
│     │
│GPIO18├──[Button 1]──→ GND (Mode button)
│GPIO19├──[Button 2]──→ GND (Speed button)
└────┘
```

---

## The Code

See [code-led-patterns.ino](code-led-patterns.ino) for complete sketch.

---

## Step-by-Step Build

### Step 1: Build LED Circuit (10 min)

1. Insert 3 LEDs into breadboard (different rows)
2. Connect resistors to each LED positive leg
3. Wire from resistor to ESP32 pins: GPIO2, GPIO4, GPIO5
4. Connect all LED negative legs to GND rail
5. Wire GND rail to ESP32 GND pin

**Test:** Upload code, LEDs should light up!

### Step 2: Add Buttons (5 min)

1. Insert 2 buttons into breadboard (across center divide)
2. Wire button 1 to GPIO18
3. Wire button 2 to GPIO19
4. Connect other side of both buttons to GND

**Test:** Press buttons, pattern should change!

---

## Light Patterns Included

The code includes these patterns:

### Pattern 1: All Blink Together
All 3 LEDs turn on/off in sync. Classic!

### Pattern 2: Chase Sequence
LEDs light up one at a time in sequence (red → green → blue → repeat)

### Pattern 3: Breathing Effect
LEDs fade in and out smoothly using PWM (looks very cool!)

### Pattern 4: Random Disco
Random combinations of LEDs flash at random intervals. Party mode!

### Pattern 5: Color Mixing
Slowly cycles through color combinations

---

## How to Use

1. **Upload the code**
2. **Press Button 1** to cycle through patterns (1 → 2 → 3 → 4 → 5 → 1...)
3. **Press Button 2** to change speed (slow → medium → fast)
4. **Watch Serial Monitor** to see which pattern is active

---

## Experiments to Try

### Beginner
- Change the colors (swap red/green/blue pins)
- Change the blink timing (modify `delay()` values)
- Add a 4th LED!

### Intermediate
- Create your own pattern (add Pattern 6!)
- Make patterns speed up over time
- Add a "freeze" button to pause

### Advanced
- Add sound effects (buzzer on another pin)
- Use analog input to control brightness
- Create a music-reactive mode (using sound sensor)

---

## Troubleshooting

### LEDs don't light up
- Check polarity (long leg = positive!)
- Check resistors are connected
- Test each LED individually first

### Buttons don't change patterns
- Check `INPUT_PULLDOWN` is set in code
- Check button connections (across center divide?)
- Check Serial Monitor to see if button presses are detected

### LEDs are too bright/dim
- Adjust resistor values (220Ω is standard, try 330Ω or 470Ω)
- Or use PWM to control brightness in code

### Pattern looks wrong
- Check which LED is on which pin (red=GPIO2, green=GPIO4, blue=GPIO5)
- Swap wires if colors are mixed up

---

## Take It Further

**Ideas for home:**
- Mount LEDs in a 3D-printed case
- Add more patterns
- Control via smartphone (Blynk app + WiFi)
- Sync to music using FFT
- Build a wearable LED badge

---

**Questions?** Check [Resources](../../resources/) or open an [Issue](https://github.com/zoharsf/embedded-electronics-101/issues)!
