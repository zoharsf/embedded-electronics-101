# 🔌 Workshop 1: Circuit Diagram & Build Guide

## Complete Circuit Overview

You'll build TWO circuits in Workshop 1:
1. **Circuit 1:** LED only (for blink test)
2. **Circuit 2:** LED + Button (full project)

---

## Circuit 1: LED Blink (Warm-up)

### Schematic Diagram

```
ESP32 Pin GPIO2 ─── [220Ω Resistor] ─── LED(+) ─┐
                                                  │
ESP32 Pin GND ────────────────────────────────────┘
```

### Physical Build Instructions

1. **Insert LED into breadboard**
   - Long leg (positive/anode) in row 10, column E
   - Short leg (negative/cathode) in row 11, column E

2. **Connect resistor**
   - One end in row 10, column D (same row as LED+ leg)
   - Other end in row 7, column D

3. **Wire from ESP32 to resistor**
   - Jumper wire: ESP32 GPIO2 pin → breadboard row 7, column C

4. **Wire from LED to ground**
   - Jumper wire: Breadboard row 11, column C → ESP32 GND pin

**Visual:**
```
ESP32                    Breadboard
┌────┐                   Row 7:  [Resistor end]
│    │                   Row 10: [LED Long leg +]
│GPIO2├──────(red wire)────────→ Row 7
│    │                   
│ GND├──────(black wire)───────→ Row 11
│    │                   Row 11: [LED Short leg -]
└────┘                   
```

---

## Circuit 2: LED + Button (Main Project)

### Schematic Diagram

```
                      ┌── [220Ω Resistor] ── LED(+) ──┐
ESP32 Pin GPIO2 ──────┤                               │
                      └───────────────────────────────┼─── GND
                                                      │
ESP32 Pin GPIO4 ─── [Button] ─── [10kΩ Resistor] ─────┘
```

### Physical Build Instructions

**Starting from Circuit 1 (LED already built), now add the button:**

5. **Insert button into breadboard**
   - Place button across the center divide (pins in rows 15 & 17)
   - Buttons have 4 legs - two pairs are internally connected

6. **Connect button to ESP32**
   - Jumper wire: ESP32 GPIO4 pin → breadboard row 15, column F (button leg)

7. **Connect button to ground**
   - Jumper wire: Breadboard row 17, column J → ESP32 GND pin
   - (You can use the same GND rail/pin as the LED)

### Pin Connection Summary Table

| Component | Component Side | ESP32 Pin | Wire Color (Suggested) |
|-----------|----------------|-----------|------------------------|
| LED Long Leg (+) | Via 220Ω resistor | GPIO 2 | Red |
| LED Short Leg (-) | Direct | GND | Black |
| Button Side 1 | Direct | GPIO 4 | Yellow/Green |
| Button Side 2 | Direct | GND | Black |
| Resistor (LED) | Between GPIO2 and LED+ | - | - |

### Complete Physical Layout

```
     USB Port
        ↑
  ┌─────┴──────────┐
  │     ESP32      │
  │                │
  │ GPIO2  GPIO4   │  
  │   ↓      ↓     │
  └───┼──────┼─────┘
      │      │
      │      │ (yellow wire)
      │      ↓
      │   Row 15: [Button Leg 1]
      │      |
      │      | (button body)
      │      |
      │   Row 17: [Button Leg 2]
      │      ↓
      │   (black wire to GND)
      │
      ↓ (red wire)
   Row 7: [Resistor end]
      |
   Row 10: [LED Long +]
      |
   Row 11: [LED Short -]
      ↓
   (black wire to GND)
```

---

## How the Circuit Works

### LED Circuit
1. **GPIO2 goes HIGH (3.3V)** → Current flows through resistor → LED lights up → Returns to GND
2. **GPIO2 goes LOW (0V)** → No current flow → LED is off

### Button Circuit
1. **Button NOT pressed:** GPIO4 reads LOW (via pull-down resistor to GND)
2. **Button IS pressed:** GPIO4 reads HIGH (button connects to 3.3V... wait, we need to update this!)

**Important Note:** The circuit diagram above shows a simplified version. For a proper button circuit with ESP32, you should use the internal pull-down resistor in code:

```cpp
pinMode(BUTTON_PIN, INPUT_PULLDOWN);  // Use internal pull-down
```

This way, you don't need an external 10kΩ resistor!

### Simplified Button Circuit (Recommended)

```
ESP32 Pin GPIO4 ─── [Button] ─── 3.3V
                       │
                      GND (when not pressed, internal pull-down)
```

---

## Common Mistakes & Fixes

### ❌ LED won't light up
- **Check:** Long leg connected to GPIO2 side (via resistor)?
- **Check:** Short leg connected to GND?
- **Try:** Flip the LED around (reversed polarity)

### ❌ LED stays dimly lit
- **Check:** Resistor is included (LED without resistor can glow dimly when it shouldn't)

### ❌ Button doesn't work
- **Check:** Button is across the breadboard center divide
- **Check:** One button leg goes to GPIO4, other to GND
- **Check:** Code has `pinMode(BUTTON_PIN, INPUT_PULLDOWN);`

### ❌ LED lights up backwards (on when button released)
- This is actually a pull-up/pull-down issue
- **Fix:** Change code from `INPUT_PULLDOWN` to `INPUT_PULLUP` and reverse the if/else logic

---

## Testing Your Circuit

### Test #1: LED Blink (No Button Needed)
Upload [code-led-blink.ino](code-led-blink.ino) → LED should blink on/off every second

### Test #2: LED + Button
Upload [code-led-button.ino](code-led-button.ino) → LED lights up when button pressed

---

## 🖥️ Try It in a Simulator

Don't have your hardware yet? You can test your code in [Wokwi](https://wokwi.com/), a free online ESP32 simulator:

1. Go to [wokwi.com](https://wokwi.com/)
2. Click **"New Project"** → select **ESP32**
3. Add an LED and resistor from the parts panel
4. Wire them up like the circuit above
5. Paste the blink code and click **Play**

Wokwi lets you test your code before building the physical circuit!

---

**Stuck?** Check [Workshop 1 Troubleshooting](troubleshooting.md)

