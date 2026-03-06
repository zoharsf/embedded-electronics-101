// =====================================
// Workshop 3: Bluetooth Controller
// Phone-controlled LEDs + sensor reading
// =====================================
//
// Hardware needed:
//   - 3x LEDs (red, yellow, green) with 220 ohm resistors
//   - 1x DHT11 temperature & humidity sensor
//
// Required libraries:
//   - BluetoothSerial (built-in with ESP32)
//   - DHT sensor library by Adafruit
//
// Pin connections:
//   GPIO 25 -> Red LED (through 220 ohm resistor)
//   GPIO 26 -> Yellow LED (through 220 ohm resistor)
//   GPIO 27 -> Green LED (through 220 ohm resistor)
//   GPIO 5  -> DHT11 DATA
//   3.3V    -> DHT11 VCC
//   GND     -> DHT11 GND

#include <BluetoothSerial.h>
#include <DHT.h>

// ===== BLUETOOTH SETUP =====
BluetoothSerial SerialBT;
const char* deviceName = "ESP32_Controller";  // Change this if you want!

// ===== PIN DEFINITIONS =====
const int RED_PIN = 25;
const int YELLOW_PIN = 26;
const int GREEN_PIN = 27;

#define DHT_PIN 5
#define DHT_TYPE DHT11

// ===== SENSOR INITIALIZATION =====
DHT dht(DHT_PIN, DHT_TYPE);

// ===== SETUP =====
void setup() {
  Serial.begin(9600);

  // Set up LED pins
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  // Start DHT sensor
  dht.begin();

  // Start Bluetooth
  SerialBT.begin(deviceName);
  Serial.print("Bluetooth started! Pair with '");
  Serial.print(deviceName);
  Serial.println("'");

  // Startup animation
  startupAnimation();

  Serial.println("Ready for commands.");
}

// ===== MAIN LOOP =====
void loop() {
  // Check for Bluetooth data
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('\n');
    command.trim();          // Remove whitespace
    command.toUpperCase();   // Make case-insensitive

    Serial.print("Received: ");
    Serial.println(command);

    handleCommand(command);
  }
}

// ===== COMMAND HANDLER =====
void handleCommand(String command) {
  // --- LED Control ---
  if (command == "RED:ON") {
    digitalWrite(RED_PIN, HIGH);
    SerialBT.println("OK: Red LED ON");
  }
  else if (command == "RED:OFF") {
    digitalWrite(RED_PIN, LOW);
    SerialBT.println("OK: Red LED OFF");
  }
  else if (command == "YELLOW:ON") {
    digitalWrite(YELLOW_PIN, HIGH);
    SerialBT.println("OK: Yellow LED ON");
  }
  else if (command == "YELLOW:OFF") {
    digitalWrite(YELLOW_PIN, LOW);
    SerialBT.println("OK: Yellow LED OFF");
  }
  else if (command == "GREEN:ON") {
    digitalWrite(GREEN_PIN, HIGH);
    SerialBT.println("OK: Green LED ON");
  }
  else if (command == "GREEN:OFF") {
    digitalWrite(GREEN_PIN, LOW);
    SerialBT.println("OK: Green LED OFF");
  }
  else if (command == "ALL:ON") {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(YELLOW_PIN, HIGH);
    digitalWrite(GREEN_PIN, HIGH);
    SerialBT.println("OK: All LEDs ON");
  }
  else if (command == "ALL:OFF") {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    SerialBT.println("OK: All LEDs OFF");
  }
  else if (command == "BLINK") {
    blinkAll();
    SerialBT.println("OK: Blink done");
  }

  // --- Sensor Commands ---
  else if (command == "TEMP") {
    float temp = dht.readTemperature();
    if (isnan(temp)) {
      SerialBT.println("ERROR: Could not read temperature");
    } else {
      SerialBT.print("Temperature: ");
      SerialBT.print(temp, 1);
      SerialBT.println(" C");
    }
  }
  else if (command == "HUMIDITY") {
    float hum = dht.readHumidity();
    if (isnan(hum)) {
      SerialBT.println("ERROR: Could not read humidity");
    } else {
      SerialBT.print("Humidity: ");
      SerialBT.print(hum, 1);
      SerialBT.println(" %");
    }
  }

  // --- Status ---
  else if (command == "STATUS") {
    sendStatus();
  }

  // --- Help ---
  else if (command == "HELP") {
    sendHelp();
  }

  // --- Unknown Command ---
  else {
    SerialBT.print("ERROR: Unknown command '");
    SerialBT.print(command);
    SerialBT.println("'. Type HELP for commands.");
  }
}

// ===== SEND STATUS =====
void sendStatus() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  SerialBT.println("--- STATUS ---");
  SerialBT.print("Red LED:    ");
  SerialBT.println(digitalRead(RED_PIN) ? "ON" : "OFF");
  SerialBT.print("Yellow LED: ");
  SerialBT.println(digitalRead(YELLOW_PIN) ? "ON" : "OFF");
  SerialBT.print("Green LED:  ");
  SerialBT.println(digitalRead(GREEN_PIN) ? "ON" : "OFF");

  if (!isnan(temp)) {
    SerialBT.print("Temperature: ");
    SerialBT.print(temp, 1);
    SerialBT.println(" C");
  }
  if (!isnan(hum)) {
    SerialBT.print("Humidity:    ");
    SerialBT.print(hum, 1);
    SerialBT.println(" %");
  }
  SerialBT.println("--------------");
}

// ===== SEND HELP =====
void sendHelp() {
  SerialBT.println("--- COMMANDS ---");
  SerialBT.println("RED:ON / RED:OFF");
  SerialBT.println("YELLOW:ON / YELLOW:OFF");
  SerialBT.println("GREEN:ON / GREEN:OFF");
  SerialBT.println("ALL:ON / ALL:OFF");
  SerialBT.println("BLINK  - Blink all LEDs");
  SerialBT.println("TEMP   - Read temperature");
  SerialBT.println("HUMIDITY - Read humidity");
  SerialBT.println("STATUS - Show all states");
  SerialBT.println("HELP   - This message");
  SerialBT.println("----------------");
}

// ===== BLINK ALL LEDS =====
void blinkAll() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(YELLOW_PIN, HIGH);
    digitalWrite(GREEN_PIN, HIGH);
    delay(200);
    digitalWrite(RED_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    delay(200);
  }
}

// ===== STARTUP ANIMATION =====
void startupAnimation() {
  // Quick chase pattern to show everything works
  int pins[] = {RED_PIN, YELLOW_PIN, GREEN_PIN};
  for (int i = 0; i < 3; i++) {
    digitalWrite(pins[i], HIGH);
    delay(150);
    digitalWrite(pins[i], LOW);
  }
  delay(100);
  // Flash all once
  for (int i = 0; i < 3; i++) {
    digitalWrite(pins[i], HIGH);
  }
  delay(300);
  for (int i = 0; i < 3; i++) {
    digitalWrite(pins[i], LOW);
  }
}

// ===== TRY THIS =====
// 1. Add PWM brightness control: "RED:128" for half brightness
//    Hint: Use analogWrite(RED_PIN, value) with values 0-255
// 2. Add a CHASE command that runs a light chase pattern
// 3. Add a RAINBOW command that cycles through LED combinations
// 4. Add a button and send a notification to the phone when pressed
// 5. Build a custom phone app with MIT App Inventor
