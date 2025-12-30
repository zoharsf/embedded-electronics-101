# 🌡️ Sensor Basics: DHT11 & Light Sensors

## DHT11 Temperature & Humidity Sensor

### What It Does
Reads two things:
1. **Temperature** (in Celsius)
2. **Humidity** (percentage of moisture in air)

### How It Works
- Built-in microchip reads ambient conditions
- Sends data via one wire (DATA pin)
- Takes ~2 seconds between readings (it's slow!)

### Pins
```
DHT11 (from left to right when facing the sensor):
├─ VCC (red) → 3.3V
├─ DATA (yellow) → GPIO5
├─ [not used]
└─ GND (black) → GND
```

### Code Example
```cpp
#include <DHT.h>

#define DHT_PIN 5
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print("C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  
  delay(2000);  // Wait 2 seconds before next read
}
```

---

## Light Sensitive Resistor (LDR)

### What It Does
Detects brightness. Changes resistance based on light.

- **Bright light** → Low resistance (~1kΩ)
- **Darkness** → High resistance (~1MΩ)

### How It Works
Think of it like a dimmer switch:
- More light = less resistance
- Less light = more resistance

### Code Example
```cpp
int lightPin = A0;  // Analog pin

void setup() {
  Serial.begin(9600);
}

void loop() {
  int lightValue = analogRead(lightPin);
  Serial.println(lightValue);  // 0-4095
  delay(100);
}
```

### Reading Values
- **0-1000** = Dark
- **1000-2500** = Normal lighting
- **2500-4095** = Bright

---

Next: [Code Tweaking](/inter-workshop/03-code-tweaking.md)

