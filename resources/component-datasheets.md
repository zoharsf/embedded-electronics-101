# 📋 Component Datasheets & Specifications

## ESP32 Development Board

**Microcontroller:** Espressif ESP32-WROOM-32

### Key Specifications
- **CPU:** Dual-core Xtensa LX6, up to 240 MHz
- **Memory:** 520 KB SRAM, 4 MB Flash
- **WiFi:** 802.11 b/g/n (2.4 GHz)
- **Bluetooth:** v4.2 BR/EDR and BLE
- **GPIO Pins:** 34 programmable pins
- **Analog Inputs:** 18 channels, 12-bit ADC
- **PWM Channels:** 16 channels
- **Operating Voltage:** 3.3V (input: 5V via USB)
- **Current:** Up to 240mA per pin

### Pinout Diagram
[Official ESP32 Pinout Reference](https://randomnerdtutorials.com/esp32-pinout-reference-gpios/)

### Important Notes
- Use 3.3V logic (NOT 5V!)
- Some pins are input-only (GPIO 34-39)
- Avoid using GPIO 6-11 (connected to flash)
- Built-in LED usually on GPIO 2

### Datasheet
[ESP32-WROOM-32 Datasheet (PDF)](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf)

---

## DHT11 Temperature & Humidity Sensor

### Specifications
- **Temperature Range:** 0-50°C (±2°C accuracy)
- **Humidity Range:** 20-90% RH (±5% accuracy)
- **Operating Voltage:** 3-5.5V
- **Current:** 0.5-2.5mA
- **Sampling Rate:** 1 Hz (one reading per second)
- **Response Time:** 6-15 seconds

### Pinout (Left to Right, facing sensor)
1. **VCC** → 3.3V or 5V
2. **DATA** → GPIO pin
3. **NC** → Not connected
4. **GND** → Ground

### Usage Notes
- Wait at least 2 seconds between readings
- Sensor needs 1 second to stabilize on power-up
- Not suitable for outdoor use (not waterproof)
- Poor accuracy compared to DHT22 (but cheaper!)

### Library
Use Adafruit DHT Sensor Library in Arduino IDE

### Datasheet
[DHT11 Datasheet (PDF)](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf)

---

## LED (Light-Emitting Diode)

### Standard 5mm LED Specifications
- **Forward Voltage:** 1.8-3.3V (varies by color)
  - Red: ~2.0V
  - Green: ~2.1V
  - Blue: ~3.2V
  - White: ~3.2V
- **Forward Current:** 20mA (typical)
- **Max Current:** 30mA (absolute maximum)
- **Viewing Angle:** 30-60° (typical)
- **Lifespan:** 50,000+ hours

### Polarity
- **Anode (+):** Long leg, connects to positive/GPIO
- **Cathode (-):** Short leg, flat side of rim, connects to GND

### Current-Limiting Resistor Calculation
Using Ohm's Law: `R = (V_source - V_led) / I_led`

For ESP32 (3.3V) with red LED (2.0V) at 20mA:
```
R = (3.3V - 2.0V) / 0.020A = 65Ω
```
Use 220Ω resistor (safe standard value, LED will be slightly dimmer)

---

## Push Button (Tactile Switch)

### Specifications
- **Type:** SPST Momentary
- **Operating Force:** 100-160gf
- **Contact Resistance:** < 100mΩ
- **Lifespan:** 100,000+ cycles
- **Mounting:** Through-hole (breadboard-friendly)

### How It Works
- **Normally Open (NO):** Circuit is open (no connection)
- **When Pressed:** Circuit closes (makes connection)
- **When Released:** Returns to open state

### Pin Configuration
- 4 pins (2 pairs)
- Each pair is internally connected
- Pressing button connects the two pairs

### Best Practices
- Use pull-down or pull-up resistor (10kΩ typical)
- Or use ESP32 internal pull-down: `pinMode(pin, INPUT_PULLDOWN)`
- Software debouncing recommended (10-50ms delay)

---

## Resistors

### 220Ω Resistor (Red-Red-Brown-Gold)
- **Resistance:** 220Ω
- **Tolerance:** ±5% (gold band)
- **Power Rating:** 1/4W (0.25W)
- **Common Use:** LED current limiting

### 10kΩ Resistor (Brown-Black-Orange-Gold)
- **Resistance:** 10,000Ω (10kΩ)
- **Tolerance:** ±5%
- **Power Rating:** 1/4W
- **Common Use:** Pull-up/pull-down resistors

### Color Code Reference
| Color | Digit | Multiplier |
|-------|-------|------------|
| Black | 0 | ×1 |
| Brown | 1 | ×10 |
| Red | 2 | ×100 |
| Orange | 3 | ×1k |
| Yellow | 4 | ×10k |
| Green | 5 | ×100k |
| Blue | 6 | ×1M |
| Violet | 7 | ×10M |
| Gray | 8 | - |
| White | 9 | - |
| Gold | - | ±5% |
| Silver | - | ±10% |

---

## LDR (Light-Dependent Resistor / Photoresistor)

### Specifications
- **Type:** CdS photocell
- **Resistance Range:** 
  - Dark: 1MΩ (1,000,000Ω)
  - Light: 1kΩ (1,000Ω)
- **Operating Voltage:** Up to 150V
- **Power:** 100mW max
- **Response Time:** 20-30ms (rising), 30-40ms (falling)
- **Spectral Peak:** ~540nm (green light)

### Voltage Divider Circuit
```
3.3V ──[LDR]──┬──→ Analog Input
              │
           [10kΩ]
              │
             GND
```

Output voltage = 3.3V × (R2 / (R_LDR + R2))

### Usage Notes
- No polarity (works either way)
- Response is logarithmic (not linear)
- Affected by temperature
- Slow response time (not for fast light changes)

---

## Breadboard (Solderless Prototyping Board)

### Standard 400-Point Breadboard

**Dimensions:** ~84mm × 55mm

**Connection Pattern:**
- **Power Rails:** 50 holes vertically connected (both + and -)
- **Terminal Strips:** 5 holes horizontally connected (rows A-E and F-J)
- **Center Gap:** Left and right sides NOT connected

### Best Practices
- Use solid-core wire (22-24 AWG)
- Push components firmly (but don't break them!)
- Keep wires short and organized
- Use consistent color coding (red=power, black=ground)
- Test connections with multimeter if unsure

### Typical Lifespan
- Good quality: 10,000+ insertions per hole
- Connections may loosen over time
- Clean with isopropyl alcohol if needed

---

## Jumper Wires

### Types
- **Male-to-Male (M-M):** Connect two breadboard points
- **Male-to-Female (M-F):** Breadboard to components with pins
- **Female-to-Female (F-F):** Connect two components with pins

### Wire Gauge
- Typically 22-26 AWG
- 22 AWG = thicker, more durable
- 26 AWG = thinner, more flexible

### Color Conventions
- **Red:** Power (+3.3V, +5V)
- **Black:** Ground (GND, 0V)
- **Yellow/Green:** Signal/Data
- **Blue:** Other signals
- **White/Gray:** General connections

---

## Additional Resources

### Official Documentation
- [ESP32 Technical Reference](https://www.espressif.com/en/support/documents/technical-documents)
- [Arduino Language Reference](https://www.arduino.cc/reference/en/)

### Component Sellers
- [Adafruit](https://www.adafruit.com/) - Quality components, great tutorials
- [SparkFun](https://www.sparkfun.com/) - Wide selection, learning resources
- [Mouser](https://www.mouser.com/) - Electronics distributor
- [DigiKey](https://www.digikey.com/) - Comprehensive inventory

### Calculators
- [LED Resistor Calculator](https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-led-series-resistor)
- [Ohm's Law Calculator](https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-ohms-law)
- [Voltage Divider Calculator](https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-voltage-divider)

---

**Need a specific datasheet?** Open an [Issue](https://github.com/zoharsf/embedded-electronics-101/issues) and we'll add it!
