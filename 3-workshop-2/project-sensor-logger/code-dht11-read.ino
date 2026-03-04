// =====================================
// Workshop 2: Sensor Data Logger
// Read DHT11 temperature & humidity
// =====================================
//
// Hardware: 1x DHT11 sensor
// Pins: GPIO 5 -> DHT11 DATA, 3.3V -> DHT11 VCC, GND -> DHT11 GND
// Libraries: DHT sensor library by Adafruit, Adafruit Unified Sensor

#include <DHT.h>

#define DHT_PIN 5
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println("=== DHT11 Sensor Logger ===");
  Serial.println("Temp (C) | Humidity (%)");
  Serial.println("---------|----------");
}

void loop() {
  // Read temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Check if reads are valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    // Print in nice format
    Serial.print(temperature);
    Serial.print(" C      | ");
    Serial.print(humidity);
    Serial.println(" %");
  }
  
  // Wait 2 seconds (DHT11 is slow)
  delay(2000);
}

