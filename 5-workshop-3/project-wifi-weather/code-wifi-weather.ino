// =====================================
// Workshop 3: WiFi Weather Station
// Web-based sensor dashboard
// =====================================

#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

// ===== WIFI CREDENTIALS =====
const char* ssid = "YOUR_NETWORK_NAME";      // Change this!
const char* password = "YOUR_PASSWORD";       // Change this!

// ===== PIN DEFINITIONS =====
#define DHT_PIN 5
#define DHT_TYPE DHT11
#define LIGHT_PIN 34

// ===== SENSOR INITIALIZATION =====
DHT dht(DHT_PIN, DHT_TYPE);
WebServer server(80);

// ===== SENSOR VARIABLES =====
float temperature = 0;
float humidity = 0;
int lightLevel = 0;
unsigned long lastSensorRead = 0;

// ===== SETUP =====
void setup() {
  Serial.begin(9600);
  dht.begin();
  
  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\n✓ Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Open browser to: http://");
  Serial.println(WiFi.localIP());
  
  // Set up web server routes
  server.on("/", handleRoot);
  server.on("/api/data", handleAPI);
  
  // Start server
  server.begin();
  Serial.println("Web server started!");
}

// ===== MAIN LOOP =====
void loop() {
  server.handleClient();
  
  // Read sensors every 2 seconds
  if (millis() - lastSensorRead > 2000) {
    lastSensorRead = millis();
    readSensors();
  }
}

// ===== READ SENSORS =====
void readSensors() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  lightLevel = analogRead(LIGHT_PIN);
  
  // Validate readings
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read DHT sensor!");
  }
}

// ===== WEB PAGE HANDLER =====
void handleRoot() {
  String html = R"(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ESP32 Weather Station</title>
  <style>
    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }
    body {
      font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Arial, sans-serif;
      background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
      min-height: 100vh;
      display: flex;
      align-items: center;
      justify-content: center;
      padding: 20px;
    }
    .container {
      background: white;
      border-radius: 20px;
      box-shadow: 0 20px 60px rgba(0,0,0,0.3);
      padding: 40px;
      max-width: 500px;
      width: 100%;
    }
    h1 {
      color: #333;
      text-align: center;
      margin-bottom: 30px;
      font-size: 28px;
    }
    .sensor-card {
      background: #f8f9fa;
      border-radius: 15px;
      padding: 25px;
      margin-bottom: 20px;
      border-left: 5px solid #667eea;
    }
    .sensor-label {
      color: #666;
      font-size: 14px;
      text-transform: uppercase;
      letter-spacing: 1px;
      margin-bottom: 8px;
    }
    .sensor-value {
      color: #333;
      font-size: 36px;
      font-weight: bold;
      margin-bottom: 5px;
    }
    .sensor-unit {
      color: #999;
      font-size: 18px;
    }
    .last-update {
      text-align: center;
      color: #999;
      font-size: 12px;
      margin-top: 20px;
    }
    .status-indicator {
      display: inline-block;
      width: 10px;
      height: 10px;
      background: #4CAF50;
      border-radius: 50%;
      margin-right: 5px;
      animation: pulse 2s infinite;
    }
    @keyframes pulse {
      0%, 100% { opacity: 1; }
      50% { opacity: 0.5; }
    }
  </style>
  <script>
    function updateData() {
      fetch('/api/data')
        .then(response => response.json())
        .then(data => {
          document.getElementById('temp-c').innerText = data.temperature.toFixed(1);
          document.getElementById('temp-f').innerText = data.temperatureF.toFixed(1);
          document.getElementById('humidity').innerText = data.humidity.toFixed(1);
          document.getElementById('light').innerText = data.light;
          document.getElementById('time').innerText = new Date().toLocaleTimeString();
        });
    }
    setInterval(updateData, 5000);  // Update every 5 seconds
    updateData();  // Initial load
  </script>
</head>
<body>
  <div class="container">
    <h1>🌤️ Weather Station</h1>
    
    <div class="sensor-card">
      <div class="sensor-label">Temperature</div>
      <div class="sensor-value">
        <span id="temp-c">--</span><span class="sensor-unit">°C</span>
      </div>
      <div class="sensor-unit">
        <span id="temp-f">--</span>°F
      </div>
    </div>
    
    <div class="sensor-card">
      <div class="sensor-label">Humidity</div>
      <div class="sensor-value">
        <span id="humidity">--</span><span class="sensor-unit">%</span>
      </div>
    </div>
    
    <div class="sensor-card">
      <div class="sensor-label">Light Level</div>
      <div class="sensor-value">
        <span id="light">--</span><span class="sensor-unit"></span>
      </div>
      <div class="sensor-unit">0 (dark) - 4095 (bright)</div>
    </div>
    
    <div class="last-update">
      <span class="status-indicator"></span>
      Last updated: <span id="time">--</span>
    </div>
  </div>
</body>
</html>
  )";
  
  server.send(200, "text/html", html);
}

// ===== JSON API HANDLER =====
void handleAPI() {
  float tempF = (temperature * 9.0 / 5.0) + 32.0;
  
  String json = "{";
  json += "\"temperature\":" + String(temperature) + ",";
  json += "\"temperatureF\":" + String(tempF) + ",";
  json += "\"humidity\":" + String(humidity) + ",";
  json += "\"light\":" + String(lightLevel);
  json += "}";
  
  server.send(200, "application/json", json);
}

// ===== TRY THIS =====
// 1. Change colors in CSS (search for #667eea and #764ba2)
// 2. Add more sensors
// 3. Change refresh rate (currently 5000ms)
// 4. Add min/max tracking
// 5. Log data to SD card
