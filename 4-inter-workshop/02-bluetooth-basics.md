# 🔵 Bluetooth Basics: Wireless Communication

## What is Bluetooth?

Bluetooth is a **short-range wireless technology** perfect for connecting your ESP32 to phones, tablets, and computers.

**Range:** Typically 10-30 meters (30-100 feet)
**Speed:** Fast enough for sensor data and control signals
**Power:** Low power consumption

---

## Two Types of Bluetooth

### Bluetooth Classic (BR/EDR)
- **Best for:** Streaming data, file transfer, audio
- **Speed:** Fast (up to 3 Mbps)
- **Power:** Higher consumption
- **Use case:** Serial communication with phones/computers

### Bluetooth Low Energy (BLE)
- **Best for:** Sensors, beacons, periodic data
- **Speed:** Slower (up to 1 Mbps)
- **Power:** Very low consumption (runs on coin battery for months!)
- **Use case:** Fitness trackers, smart watches, IoT sensors

**For Workshop 3:** We'll use **Bluetooth Classic** (easier for beginners)

---

## Bluetooth Serial Communication

The easiest way to use Bluetooth: **Serial communication** (just like USB Serial, but wireless!)

### Basic Code Example

```cpp
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32_Device");  // Bluetooth device name
  Serial.println("Bluetooth started! Pair with 'ESP32_Device'");
}

void loop() {
  // Check if data received from Bluetooth
  if (SerialBT.available()) {
    char received = SerialBT.read();
    Serial.print("Received via Bluetooth: ");
    Serial.println(received);
    
    // Echo it back
    SerialBT.print("You sent: ");
    SerialBT.println(received);
  }
  
  // Check if data received from USB Serial
  if (Serial.available()) {
    char received = Serial.read();
    SerialBT.println(received);  // Forward to Bluetooth
  }
}
```

**What this does:**
1. Creates a Bluetooth device named "ESP32_Device"
2. Receives data from Bluetooth → prints to Serial Monitor
3. Receives data from Serial Monitor → sends to Bluetooth
4. Acts as a wireless bridge!

---

## Pairing Your ESP32

### On Android:
1. Settings → Bluetooth
2. Look for "ESP32_Device"
3. Tap to pair (no PIN needed by default)
4. Use "Serial Bluetooth Terminal" app to communicate

### On iOS:
1. iOS doesn't support Bluetooth Classic Serial 😞
2. Use BLE instead (more complex, covered in advanced projects)

### On Computer:
1. Bluetooth settings
2. Add device → "ESP32_Device"
3. Use terminal program (PuTTY, Arduino Serial Monitor, etc.)

---

## Controlling Hardware via Bluetooth

**Example: LED control from phone**

```cpp
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
const int LED_PIN = 2;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  SerialBT.begin("ESP32_LED");
  Serial.begin(9600);
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    
    if (command == '1') {
      digitalWrite(LED_PIN, HIGH);
      SerialBT.println("LED ON");
    } 
    else if (command == '0') {
      digitalWrite(LED_PIN, LOW);
      SerialBT.println("LED OFF");
    }
  }
}
```

**Usage:**
- Send '1' from phone → LED turns on
- Send '0' from phone → LED turns off

---

## Sending Sensor Data via Bluetooth

**Example: Temperature monitoring**

```cpp
#include <BluetoothSerial.h>
#include <DHT.h>

BluetoothSerial SerialBT;
DHT dht(5, DHT11);

void setup() {
  SerialBT.begin("ESP32_Temp");
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Send as formatted string
  SerialBT.print("Temp: ");
  SerialBT.print(temp);
  SerialBT.print("C, Humidity: ");
  SerialBT.print(humidity);
  SerialBT.println("%");
  
  delay(2000);  // Update every 2 seconds
}
```

**On your phone:** You'll see real-time temperature updates!

---

## Protocol Design: Commands

For more complex projects, design a simple protocol:

```cpp
// Command format: "CMD:VALUE\n"
// Examples:
//   LED:ON\n
//   LED:OFF\n
//   MOTOR:150\n  (motor speed 0-255)
//   STATUS?\n    (request status)

void loop() {
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('\n');
    
    if (command.startsWith("LED:")) {
      String value = command.substring(4);
      if (value == "ON") {
        digitalWrite(LED_PIN, HIGH);
        SerialBT.println("OK:LED_ON");
      } else if (value == "OFF") {
        digitalWrite(LED_PIN, LOW);
        SerialBT.println("OK:LED_OFF");
      }
    }
    else if (command == "STATUS?") {
      SerialBT.print("LED:");
      SerialBT.println(digitalRead(LED_PIN) ? "ON" : "OFF");
    }
    else {
      SerialBT.println("ERROR:UNKNOWN_COMMAND");
    }
  }
}
```

**Benefits:**
- Clear command structure
- Easy to parse
- Error handling
- Extensible (add more commands)

---

## Mobile Apps for Bluetooth

### Android:
- **Serial Bluetooth Terminal** (free, simple)
- **Bluetooth Electronics** (GUI builder)
- **MIT App Inventor** (create your own app!)

### iOS:
- **LightBlue** (BLE only, for testing)
- Need custom app for Bluetooth Classic

### Create Your Own:
- **MIT App Inventor** (drag-and-drop app builder)
- **Flutter** (cross-platform development)
- **React Native** (JavaScript-based)

---

## Bluetooth vs WiFi

| Feature | Bluetooth | WiFi |
|---------|-----------|------|
| Range | 10-30m | 50-100m |
| Speed | 1-3 Mbps | 50-150 Mbps |
| Power | Low | Higher |
| Setup | Easy pairing | Need router |
| Best for | Direct control | Internet access |
| Mobile | Native support | Need network |

**When to use Bluetooth:**
- Direct phone control
- No WiFi available
- Low power needed
- Short range OK

**When to use WiFi:**
- Need internet access
- Multiple devices
- Longer range
- Higher data rates

---

## Security Considerations

### Pairing PIN
```cpp
SerialBT.begin("ESP32", true);  // Enable PIN
SerialBT.setPin("1234");        // Set PIN code
```

### Encryption
- Bluetooth Classic has built-in encryption
- Always use for sensitive data
- Consider additional app-level encryption for critical applications

### Best Practices
- Change default device name
- Use PIN for pairing
- Don't transmit passwords in plain text
- Implement authentication in your app

---

## Common Bluetooth Issues

### "Can't find ESP32 device"
- Make sure Bluetooth is enabled
- Check if already paired to another device
- Try restarting ESP32
- Some phones cache Bluetooth devices (unpair old ones)

### "Connection keeps dropping"
- Too far away (move closer)
- Interference from other devices
- Phone Bluetooth in power-saving mode
- Try resetting Bluetooth on both devices

### "Garbage characters received"
- Baud rate mismatch (not applicable to Bluetooth, but check your code)
- Buffer overflow (send data slower)
- Check string termination

---

## Bluetooth Low Energy (BLE) Preview

**BLE is more complex but more powerful:**

```cpp
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

// Requires:
// - Service UUID
// - Characteristic UUID
// - Callbacks for read/write
// - Advertising

// BLE is great for:
// - iOS compatibility
// - Ultra-low power
// - Standardized profiles (heart rate, battery, etc.)
```

**We'll cover BLE in advanced projects!**

---

## Try This Before Workshop 3

1. **Upload Bluetooth Serial example**
2. **Pair your phone** with ESP32
3. **Install Serial Bluetooth Terminal app** (Android)
4. **Send some test messages**
5. **Think about your project:** What would you control via Bluetooth?

---

**Next →** [Web Server Fundamentals](/4-inter-workshop/03-web-server-basics.md)
