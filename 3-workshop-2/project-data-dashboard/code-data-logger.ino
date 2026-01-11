// =====================================
// Workshop 2: Data Logger
// Collect sensor data in CSV format
// =====================================

#include <DHT.h>

// ===== PIN DEFINITIONS =====
#define DHT_PIN 5
#define DHT_TYPE DHT11
#define LIGHT_PIN 34      // Analog pin (A0)

// ===== SENSOR INITIALIZATION =====
DHT dht(DHT_PIN, DHT_TYPE);

// ===== TIMING VARIABLES =====
unsigned long lastReadTime = 0;
const unsigned long READ_INTERVAL = 2000;  // Read every 2 seconds

// ===== SETUP =====
void setup() {
  Serial.begin(9600);
  dht.begin();
  
  // Wait for Serial connection
  while (!Serial) {
    delay(10);
  }
  
  Serial.println("=== Data Logger Starting ===");
  delay(1000);
  
  // Print CSV header
  Serial.println("timestamp,temperature,humidity,light");
  
  lastReadTime = millis();
}

// ===== MAIN LOOP =====
void loop() {
  unsigned long currentTime = millis();
  
  // Check if it's time to read sensors
  if (currentTime - lastReadTime >= READ_INTERVAL) {
    lastReadTime = currentTime;
    
    // Read sensors
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int lightLevel = analogRead(LIGHT_PIN);
    
    // Validate DHT readings
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("ERROR: Failed to read DHT sensor");
      return;
    }
    
    // Output as CSV: timestamp,temperature,humidity,light
    Serial.print(currentTime);
    Serial.print(",");
    Serial.print(temperature, 1);  // 1 decimal place
    Serial.print(",");
    Serial.print(humidity, 1);     // 1 decimal place
    Serial.print(",");
    Serial.println(lightLevel);
  }
}

// ===== HOW THIS WORKS =====
// 1. Reads DHT11 (temp & humidity) and LDR (light) every 2 seconds
// 2. Outputs data in CSV format: timestamp,temp,humidity,light
// 3. Python script can read this data and create graphs
// 4. Timestamp is in milliseconds since ESP32 started

// ===== TRY THIS =====
// 1. Change READ_INTERVAL to log more/less frequently
// 2. Add more sensors (pressure, sound, etc.)
// 3. Add data validation (skip outliers)
// 4. Calculate moving averages for smoother data
