# 🔌 Workshop 1: Circuit Diagram

## LED + Button Circuit

### Physical Layout (Breadboard View)

```
     USB Port
        ↑
  ┌─────┴─────┐
  │   ESP32   │
  │           │
  │ GND  3.3V │
  │ ↑    ↑    │
  │ │    │    │
  │ │    │    │
  └─┼────┼────┘
    │    │
    │    │
    │   [Resistor 220Ω]
    │    │
    │    ↓
    │  [LED Long leg]
    │    │
    │  [LED Short leg]
    │    │
    ├────┴─→ GND
    │
    └──[Button]──→ GPIO4
          │
          └─→ GND
```

### How It Works

1. **Button Connection:**
   - One side → GPIO4 (reads button press)
   - Other side → GND (ground)

2. **LED Connection:**
   - Long leg (+) → GPIO2 (via resistor)
   - Short leg (-) → GND (ground)

3. **Resistor:** Limits current to safe level (~20mA)

### Pin Connections

| Component | ESP32 Pin | Wire Color |
|-----------|-----------|-----------|
| Button | GPIO 4 | Green |
| LED Long Leg | GPIO 2 | Red |
| LED Short Leg | GND | Black |
| Resistor (to LED) | GPIO 2 | Red |
| Resistor (to GND) | GND | Black |

---

**Notes:**
- All GND connections go to the same point
- 3.3V pin provides power (don't use for this project)
- Double-check LED polarity!

