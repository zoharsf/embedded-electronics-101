# Workshop 3: Troubleshooting

Find your symptom by Ctrl-F (or Cmd-F). Headings match the literal error or behavior you're seeing.

---

## WiFi: "Connecting to WiFi....." never finishes

The most common cause in our workshop is the hotspot being on **5 GHz**. The ESP32 only supports 2.4 GHz.

**Fixes, in order:**
1. **iPhone:** Settings → Personal Hotspot → enable **"Maximize Compatibility"**. This forces 2.4 GHz.
2. **Android:** Settings → Network → Hotspot → set band to **"2.4 GHz"** (some phones default to 5 GHz or auto).
3. **iPhone hotspot keeps sleeping:** keep the Personal Hotspot screen open until the ESP32 connects. Once connected, you can lock the phone.
4. **Typo in SSID or password:** both are case-sensitive. No spaces. No quotes inside the values in the sketch.
5. **Hotspot password too short:** some Android variants reject passwords under 8 characters.
6. **The phone isn't broadcasting yet:** turn the hotspot off, wait 5 seconds, turn it back on.

After fixing, re-upload (or hit the EN/RESET button) to make the ESP32 re-attempt the connection.

---

## WiFi: "I'm connected, but the IP address won't load in my browser"

**Fixes:**
1. Confirm your phone is connected to **its own hotspot** (some phones don't list it - check Settings → WiFi).
2. Use the IP exactly as printed in Serial Monitor. iPhone hotspots usually give `172.20.10.x`. Android usually `192.168.x.x`.
3. Use `http://` not `https://` (the ESP32 only serves plain HTTP).
4. Try a different browser (Safari + Chrome).
5. Make sure your laptop/phone isn't on a separate WiFi (toggle WiFi off/on, reconnect to the hotspot).

---

## WiFi: "Wrong password" or `WL_CONNECT_FAILED`

**Fix:** retype the password in the sketch. Watch out for:
- Special characters that look the same (`l` vs `1`, `O` vs `0`).
- Trailing whitespace from a copy-paste.
- Curly quotes `"` instead of straight quotes `"`.

---

## WiFi: SSID not found / `WL_NO_SSID_AVAIL`

**Fix:**
1. Phone hotspot is off. Turn it on.
2. SSID is not exactly what the sketch expects. Check the SSID in your phone's hotspot settings (it's often the phone's name, like "Sam's iPhone"). Apostrophes count.
3. The phone's WiFi is set to 5 GHz only. Force 2.4 GHz (see top section).

---

## Web server: "Page loads but shows `--` for all values"

**Fixes:**
1. Browse directly to `http://<ESP32_IP>/api/data`. If you see `"temperature":nan`, the DHT11 isn't responding.
2. Check that the DHT data wire is on **GPIO 5** (not 4 or 2).
3. Make sure the DHT library by Adafruit is installed.
4. Open Serial Monitor - if you see "Failed to read DHT sensor!", the wiring is the issue.

---

## Web server: "ESP32 crashes / restarts when I open the page"

Symptoms: the ESP32 reboots and Serial Monitor shows a stack trace or `Guru Meditation Error`.

**Fixes:**
- The HTML payload is too large for the available stack. Reduce the size of any custom HTML you added.
- Don't open the page from many devices at once - the simple `WebServer` library handles one client at a time best.
- Make sure you're using ESP32, not ESP8266 (which has less RAM).
- Use a real USB power source. Some laptop USB ports brown out the ESP32 under WiFi load.

---

## Web server: "LED toggle buttons don't change the LED"

**Fixes:**
1. Open the browser developer tools / console. Look for a failed `POST /api/led` request.
2. Confirm the LED's long leg goes to the GPIO (25 or 26), short leg via 220Ω to GND.
3. Verify the LED isn't burned out by swapping in another from the kit.

---

## Bluetooth: "Can't find ESP32 device on my phone"

**Fixes:**
1. Open Serial Monitor. You should see `Bluetooth started. Pair with: ESP32_BT`. If not, the sketch didn't reach `BluetoothSerial.begin()` - upload again.
2. Toggle Bluetooth off/on on the phone.
3. In the phone's Bluetooth settings, "Forget" any prior ESP32 pairings.
4. Move within 1-2 meters.
5. Reset the ESP32 (EN button).

---

## Bluetooth: "Paired but Serial Bluetooth Terminal won't send commands"

**Fixes:**
1. In the app, make sure you're connected (top bar usually says "Connected" with a colored dot).
2. App settings: send mode = "Newline" or "CR+LF" so the ESP32 sees a complete line.
3. Try sending the literal text `HELP` - the sketch should reply with the command list.

---

## Bluetooth: "I have an iPhone and the device never appears"

**This is a hard limitation.** iOS does not support the legacy Bluetooth Classic Serial profile that this project uses. Pick the WiFi Weather Station or IoT Dashboard project instead.

---

## Sensors: "Temperature/humidity shows `NaN`"

**Fixes:**
1. Wait 2 seconds after power-on - the DHT11 is slow.
2. Confirm the data wire is on GPIO 5 and tightly seated.
3. The DHT11 needs 3.3V, not 5V (the ESP32 board's pin labelled 3.3V).
4. Install the Adafruit DHT library (Library Manager → "DHT sensor library" by Adafruit).
5. Try a different jumper wire - cheap dupont wires can have intermittent contact.

---

## Sensors: "LDR always reads 0 or 4095"

**Fixes:**
1. Confirm wiring: 3.3V → LDR → GPIO 34 → 10kΩ → GND. The 10kΩ is critical (it's the other half of the voltage divider).
2. GPIO 34 is **input-only** - if you wired to a different pin, change `LIGHT_PIN` in the sketch or rewire.
3. Cover and uncover the LDR while watching Serial Monitor - the value should change. If it doesn't, the LDR is in backwards or one leg is loose.

---

## Upload: "A fatal error occurred: Failed to connect to ESP32"

**Fixes:**
1. Press and hold the **BOOT** button on the ESP32 while upload starts. Release after upload begins ("Connecting...." → "Writing...").
2. Try a different USB port. Avoid USB hubs.
3. Lower upload speed: Tools → Upload Speed → 115200.
4. Check the USB cable is a **data** cable, not charge-only. Try a different cable.

---

## Upload: "Sketch too large"

**Fixes:**
- Tools → Partition Scheme → "Huge APP (3MB No OTA / 1MB SPIFFS)".
- Remove unused libraries from `#include`s.
- For very large HTML strings, store them in `PROGMEM`.

---

## Upload: "Compilation errors"

**Most common causes:**
- DHT library not installed (Library Manager → "DHT sensor library" by Adafruit).
- Board not set to "ESP32 Dev Module" (Tools → Board).
- ESP32 board package out of date (Boards Manager → update "esp32 by Espressif Systems").
- For Bluetooth: BluetoothSerial only exists on the classic ESP32 (WROOM-32). It does not exist on ESP32-S3 / C3 / C6 / H2.

---

## Python (Data Dashboard, Workshop 2): `ModuleNotFoundError: No module named 'serial'`

**Fix:** install pyserial.

```bash
pip install pyserial matplotlib pandas
```

If `pip` complains about permissions or you're on a managed Python:

```bash
python3 -m pip install --user pyserial matplotlib pandas
```

---

## Python (Data Dashboard): "Could not open serial port"

**Fix:** the `dashboard.py` script auto-detects the ESP32 port via `pyserial.tools.list_ports`. If detection fails:
1. Make sure the Arduino IDE Serial Monitor is **closed** (it holds the port open exclusively).
2. List ports manually: `python3 -m serial.tools.list_ports -v`.
3. Set the port explicitly in `dashboard.py` by editing the `SERIAL_PORT` value at the top.

---

## Network: "Can't remember the IP address"

1. Open Serial Monitor and reset the ESP32 - it prints the IP on connect.
2. On Android: hotspot settings usually show connected device IPs.
3. iPhone doesn't show device IPs from the hotspot UI - just check Serial Monitor.

---

## General Tips

- Always check Serial Monitor first - the ESP32 prints what it's doing.
- The EN button is "reset". Press it after every WiFi-related code change.
- A flaky USB cable causes more "weird" issues than any software bug. Swap it as your first move.
- If something half-works, restart the ESP32 once. WiFi state can stick.

---

**Still stuck?** Open an [Issue](https://github.com/zoharsf/embedded-electronics-101/issues).
