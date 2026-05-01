# Workshop 1: Troubleshooting

Find your symptom by Ctrl-F (or Cmd-F). Headings match the literal error or behavior you're seeing.

---

## "Port not found" / no port appears in the IDE port list

**Fixes:**
1. Try a different USB cable. The cables in our kit are confirmed data-capable, but spare cables you bring may be charge-only.
2. Try a different USB port on your laptop. Avoid USB-C dongles where possible - if you must use one, plug the ESP32 directly first to confirm it works, then plug the dongle back in.
3. Restart the IDE (Arduino Cloud reload, or quit/relaunch Arduino IDE).
4. Unplug and replug the ESP32 - watch the port list before and after to spot the new entry.
5. Driver missing: this kit's ESP32 boards use either the CH340 or the CP2102 USB-serial chip.
   - macOS Sonoma+ usually auto-installs both.
   - Older macOS or any Windows: you may need the CH340 driver from `https://www.wch-ic.com/downloads/CH341SER_MAC_ZIP.html` or CP2102 from Silicon Labs.
   - Ask the facilitator if you're unsure which chip your board has.

---

## "Board not selected" or wrong board errors

**Fix:** Tools → Board → ESP32 Arduino → **ESP32 Dev Module**. There are dozens of similar entries; the exact one is "ESP32 Dev Module".

---

## "A fatal error occurred: Failed to connect to ESP32"

**Fix:** hold the **BOOT** button on the ESP32 while upload starts. Release once you see "Connecting...." → "Writing...". Some boards need this every upload.

If that doesn't work:
1. Try a different USB cable.
2. Lower upload speed: Tools → Upload Speed → 115200.
3. Press EN (reset) once before uploading.

---

## LED won't light up

**Fixes, in order:**
1. **Polarity.** The long leg (anode, +) must be on the GPIO 2 side via the resistor. The short leg goes to GND. If reversed, the LED simply won't light.
2. **Resistor missing or unseated.** No resistor + bright LED + 3.3V will burn the LED out within seconds. Always include the 220Ω.
3. **Wrong pin.** Code says `LED_PIN = 2`. Verify the wire goes to GPIO 2.
4. **Loose breadboard connection.** Push wires in firmly. Wiggle each leg - if anything moves, reseat it.
5. **Dead LED.** Swap with another LED from the kit.

---

## LED stays dimly lit (won't fully turn off)

**Fix:** you skipped the resistor or the resistor is shorted. The 220Ω needs to be in series between GPIO 2 and the LED's long leg.

---

## Button doesn't do anything

**Fixes:**
1. The button must straddle the breadboard's center divide. If both legs are on the same side, the button is shorting itself.
2. With `INPUT_PULLDOWN` (what the sketch uses), one button leg goes to **GPIO 4** and the other to **3.3V**. Pressing should pull GPIO 4 HIGH.
3. Confirm `pinMode(BUTTON_PIN, INPUT_PULLDOWN);` in the sketch (already set).
4. Cheap tactile buttons sometimes need a real click - press firmly.
5. Test by adding a print: `Serial.println(digitalRead(BUTTON_PIN));` in `loop()` and watch the value flip when you press.

---

## LED is on when button is released, off when pressed (inverted)

**Fix:** you wired the button to GND instead of 3.3V (or the code uses `INPUT_PULLUP` when wiring expects pulldown). Two ways to fix:
- Rewire so the button connects GPIO 4 to **3.3V** (matches the sketch's `INPUT_PULLDOWN`).
- Or switch the sketch to `INPUT_PULLUP` and invert the `if (buttonState == HIGH)` to `LOW`.

---

## Serial Monitor shows nothing

**Fixes:**
1. Set the baud rate to **9600** (bottom-right of Serial Monitor). This must match `Serial.begin(9600)` in the sketch.
2. Click the magnifying glass / Serial Monitor icon to open it (top-right in Arduino IDE).
3. Make sure no other program (Arduino Cloud, another IDE window, the dashboard.py script from Workshop 2) has the serial port open - only one process at a time.

---

## Serial Monitor shows garbage characters (e.g., `xõ½ÿ4`)

**Fix:** baud rate mismatch. The sketch uses 9600 baud - set Serial Monitor to 9600.

---

## Code compiles, uploads, but nothing happens

**Fixes:**
1. Press the EN (reset) button on the ESP32 - sometimes the chip needs a kick after upload.
2. Confirm the LED's polarity (see above).
3. Add a `Serial.println("alive")` at the top of `loop()` - if you see it, the chip is running and the issue is wiring; if you don't, re-upload.

---

**Still stuck?** Open an [Issue](https://github.com/zoharsf/embedded-electronics-101/issues).
