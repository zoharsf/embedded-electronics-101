# 🧪 Code Tweaking: Hands-On Experiments (15 minutes)

Now that you understand how sensors work, let's get hands-on! Time to experiment with real code.

## Your Mission

Take the DHT11 sensor code and **modify it** to do something different. This builds confidence!

## Starting Code

Here's the basic DHT11 example from Workshop 2:

```cpp
#include <DHT.h>

#define DHT_PIN 5
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("=== DHT11 Sensor Logger ===");
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Temp: ");
    Serial.print(temperature);
    Serial.print(" C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }
  
  delay(2000);
}
```

## Experiment #1: Add Fahrenheit Conversion (Easy)

**Challenge:** Display temperature in both Celsius AND Fahrenheit.

**Hint:** Formula is `F = C × 9/5 + 32`

**Your code:**
```cpp
// Add this in loop(), after reading temperature:
float tempF = (temperature * 9.0/5.0) + 32.0;

// Then print both:
Serial.print("Temp: ");
Serial.print(temperature);
Serial.print(" C / ");
Serial.print(tempF);
Serial.println(" F");
```

---

## Experiment #2: Comfort Zone Alert (Medium)

**Challenge:** Print a message if temperature is in the "comfort zone" (18-24°C).

**Your code:**
```cpp
// Add this after reading temperature:
if (temperature >= 18 && temperature <= 24) {
  Serial.println("✅ Comfort zone!");
} else if (temperature < 18) {
  Serial.println("🥶 Too cold!");
} else {
  Serial.println("🥵 Too hot!");
}
```

---

## Experiment #3: Only Alert on Changes (Harder)

**Challenge:** Only print when temperature changes by more than 1°C.

**Your code:**
```cpp
// Add this BEFORE setup():
float lastTemp = 0;

// Add this in loop(), after reading temperature:
if (abs(temperature - lastTemp) > 1.0) {
  Serial.print("Temperature changed! Now: ");
  Serial.println(temperature);
  lastTemp = temperature;
}
```

---

## Experiment #4: Light Sensor Threshold (Medium)

**Challenge:** Read a light sensor (LDR) and print "DARK" or "BRIGHT".

**Your code:**
```cpp
int lightPin = 34;  // Analog pin

void setup() {
  Serial.begin(9600);
}

void loop() {
  int lightValue = analogRead(lightPin);
  
  if (lightValue < 1000) {
    Serial.println("🌙 DARK");
  } else {
    Serial.println("☀️ BRIGHT");
  }
  
  delay(500);
}
```

---

## Experiment #5: Combine Sensors (Advanced)

**Challenge:** Read BOTH temperature and light, print a combined status.

**Example output:**
```
Hot & Bright → "☀️ Summer day!"
Cold & Dark → "🌙 Winter night!"
```

**Try building this yourself!** Use what you learned above.

---

## What You're Learning

These experiments teach you:
- ✅ How to modify existing code
- ✅ How to add conditional logic (if/else)
- ✅ How to combine multiple sensors
- ✅ How to make your projects more useful

## Tips

- **Test one change at a time** - Don't change everything at once
- **Use Serial Monitor** - Always check your output
- **Copy before modifying** - Keep the original code safe
- **Don't worry about breaking it** - That's how you learn!

---

**Done experimenting?** → [Pick Your Workshop 2 Project](./project-picker.md)
