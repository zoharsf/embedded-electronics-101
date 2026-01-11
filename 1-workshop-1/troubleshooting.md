# 🔧 Workshop 1: Troubleshooting

## LED Won't Light Up

**Possible causes:**

1. **Wrong polarity**
   - Check: Long leg (+) should be on GPIO2 side
   - Fix: Flip the LED around

2. **Broken LED**
   - Fix: Try a different LED

3. **Wrong pin**
   - Check: Code says `pinMode(2, OUTPUT)`
   - Fix: Make sure LED wire is on GPIO2

4. **Loose connection**
   - Fix: Push wires firmly into breadboard

5. **Bad resistor connection**
   - Check: Resistor is between GPIO2 and LED long leg
   - Fix: Reseat the resistor

## Button Doesn't Work

1. **Wrong wiring**
   - Button should connect GPIO4 and GND
   - Fix: Check circuit diagram

2. **Loose connection**
   - Fix: Push button wires in firmly

3. **Button broken**
   - Fix: Test with different button

## Code Won't Upload

1. **"Port not found"**
   - Fix: Check USB cable is plugged in
   - Fix: Try a different USB port
   - Fix: Restart Arduino Create

2. **"Board not selected"**
   - Fix: Make sure "ESP32 Dev Module" is selected (top left)

## Serial Monitor Not Showing Text

1. **Baud rate mismatch**
   - Check: Set Serial Monitor to 9600 baud (bottom right)
   - Fix: Match the `Serial.begin(9600)` in code

2. **Serial Monitor not open**
   - Fix: Click magnifying glass (top right)

---

**Still stuck?** Open an [Issue](https://github.com/zoharsf/embedded-electronics-101/issues)!

