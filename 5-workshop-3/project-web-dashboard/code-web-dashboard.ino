// =====================================
// Workshop 3: IoT Dashboard
// Full-featured web dashboard with
// sensor data, LED control, and JSON API
// =====================================
//
// Hardware needed:
//   - 1x DHT11 temperature & humidity sensor
//   - 1x LDR (light-dependent resistor)
//   - 1x 10k ohm resistor (for LDR)
//   - 2x LEDs (red, green) with 220 ohm resistors
//
// Required libraries:
//   - WiFi (built-in with ESP32)
//   - WebServer (built-in with ESP32)
//   - DHT sensor library by Adafruit
//
// Pin connections:
//   GPIO 5  -> DHT11 DATA
//   GPIO 34 -> LDR (analog input via voltage divider)
//   GPIO 25 -> Red LED (through 220 ohm resistor)
//   GPIO 26 -> Green LED (through 220 ohm resistor)
//   3.3V    -> DHT11 VCC, LDR one end
//   GND     -> DHT11 GND, 10k resistor to GPIO 34

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
const int RED_PIN = 25;
const int GREEN_PIN = 26;

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

  // Set up pins
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  dht.begin();

  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("Dashboard URL: http://");
  Serial.println(WiFi.localIP());

  // Set up web server routes
  server.on("/", handleRoot);
  server.on("/api/data", handleAPIData);
  server.on("/api/led", HTTP_POST, handleAPILed);

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

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read DHT sensor!");
  }
}

// ===== JSON API: GET SENSOR DATA =====
void handleAPIData() {
  float tempF = (temperature * 9.0 / 5.0) + 32.0;

  String json = "{";
  json += "\"temperature\":" + String(temperature, 1) + ",";
  json += "\"temperatureF\":" + String(tempF, 1) + ",";
  json += "\"humidity\":" + String(humidity, 1) + ",";
  json += "\"light\":" + String(lightLevel) + ",";
  json += "\"redLed\":" + String(digitalRead(RED_PIN)) + ",";
  json += "\"greenLed\":" + String(digitalRead(GREEN_PIN));
  json += "}";

  server.send(200, "application/json", json);
}

// ===== JSON API: TOGGLE LED =====
void handleAPILed() {
  String led = server.arg("led");
  String state = server.arg("state");

  int pin = -1;
  if (led == "red") pin = RED_PIN;
  else if (led == "green") pin = GREEN_PIN;

  if (pin == -1) {
    server.send(400, "application/json", "{\"error\":\"Invalid LED\"}");
    return;
  }

  if (state == "on") {
    digitalWrite(pin, HIGH);
  } else if (state == "off") {
    digitalWrite(pin, LOW);
  } else if (state == "toggle") {
    digitalWrite(pin, !digitalRead(pin));
  }

  server.send(200, "application/json", "{\"ok\":true}");
}

// ===== WEB PAGE HANDLER =====
void handleRoot() {
  String html = R"(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ESP32 IoT Dashboard</title>
  <style>
    * { margin: 0; padding: 0; box-sizing: border-box; }
    body {
      font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Arial, sans-serif;
      background: linear-gradient(135deg, #0f2027 0%, #203a43 50%, #2c5364 100%);
      min-height: 100vh;
      padding: 20px;
      color: #e0e0e0;
    }
    .header {
      text-align: center;
      margin-bottom: 30px;
    }
    .header h1 {
      font-size: 28px;
      color: #fff;
      margin-bottom: 5px;
    }
    .header .subtitle {
      color: #90caf9;
      font-size: 14px;
    }
    .grid {
      display: grid;
      grid-template-columns: repeat(auto-fit, minmax(280px, 1fr));
      gap: 20px;
      max-width: 900px;
      margin: 0 auto;
    }
    .card {
      background: rgba(255,255,255,0.08);
      border-radius: 16px;
      padding: 25px;
      backdrop-filter: blur(10px);
      border: 1px solid rgba(255,255,255,0.1);
    }
    .card-label {
      font-size: 12px;
      text-transform: uppercase;
      letter-spacing: 2px;
      color: #90caf9;
      margin-bottom: 12px;
    }
    .card-value {
      font-size: 42px;
      font-weight: bold;
      color: #fff;
    }
    .card-unit {
      font-size: 18px;
      color: #90caf9;
    }
    .card-detail {
      font-size: 13px;
      color: #78909c;
      margin-top: 8px;
    }
    .led-controls {
      display: flex;
      gap: 15px;
      margin-top: 10px;
    }
    .led-btn {
      flex: 1;
      padding: 14px;
      border: 2px solid rgba(255,255,255,0.2);
      border-radius: 12px;
      background: rgba(255,255,255,0.05);
      color: #fff;
      font-size: 15px;
      cursor: pointer;
      transition: all 0.2s;
      text-align: center;
    }
    .led-btn:hover { background: rgba(255,255,255,0.12); }
    .led-btn.on-red {
      background: rgba(244,67,54,0.3);
      border-color: #f44336;
    }
    .led-btn.on-green {
      background: rgba(76,175,80,0.3);
      border-color: #4CAF50;
    }
    .status-bar {
      text-align: center;
      margin-top: 25px;
      font-size: 12px;
      color: #546e7a;
    }
    .dot {
      display: inline-block;
      width: 8px; height: 8px;
      background: #4CAF50;
      border-radius: 50%;
      margin-right: 5px;
      animation: pulse 2s infinite;
    }
    @keyframes pulse {
      0%,100% { opacity: 1; }
      50% { opacity: 0.4; }
    }
    .light-bar {
      width: 100%;
      height: 8px;
      background: rgba(255,255,255,0.1);
      border-radius: 4px;
      margin-top: 12px;
      overflow: hidden;
    }
    .light-fill {
      height: 100%;
      background: linear-gradient(90deg, #ffb74d, #fff176);
      border-radius: 4px;
      transition: width 0.5s;
    }
  </style>
  <script>
    function updateData() {
      fetch('/api/data')
        .then(r => r.json())
        .then(d => {
          document.getElementById('temp').innerText = d.temperature.toFixed(1);
          document.getElementById('tempF').innerText = d.temperatureF.toFixed(1);
          document.getElementById('hum').innerText = d.humidity.toFixed(1);
          document.getElementById('light').innerText = d.light;

          // Light bar
          var pct = Math.min(100, (d.light / 4095) * 100);
          document.getElementById('lightBar').style.width = pct + '%';

          // Light description
          var desc = d.light < 1000 ? 'Dark' : d.light < 2500 ? 'Dim' : 'Bright';
          document.getElementById('lightDesc').innerText = desc;

          // Humidity status
          var hDesc = d.humidity < 30 ? 'Dry' : d.humidity < 60 ? 'Comfortable' : 'Humid';
          document.getElementById('humDesc').innerText = hDesc;

          // LED buttons
          var redBtn = document.getElementById('redBtn');
          var greenBtn = document.getElementById('greenBtn');
          redBtn.className = 'led-btn' + (d.redLed ? ' on-red' : '');
          redBtn.innerText = 'Red ' + (d.redLed ? 'ON' : 'OFF');
          greenBtn.className = 'led-btn' + (d.greenLed ? ' on-green' : '');
          greenBtn.innerText = 'Green ' + (d.greenLed ? 'ON' : 'OFF');

          document.getElementById('time').innerText = new Date().toLocaleTimeString();
        });
    }

    function toggleLed(led) {
      fetch('/api/led', {
        method: 'POST',
        headers: {'Content-Type': 'application/x-www-form-urlencoded'},
        body: 'led=' + led + '&state=toggle'
      }).then(() => updateData());
    }

    setInterval(updateData, 3000);
    updateData();
  </script>
</head>
<body>
  <div class="header">
    <h1>IoT Dashboard</h1>
    <div class="subtitle">ESP32 Sensor Monitor & Control</div>
  </div>

  <div class="grid">
    <div class="card">
      <div class="card-label">Temperature</div>
      <div class="card-value"><span id="temp">--</span><span class="card-unit"> C</span></div>
      <div class="card-detail"><span id="tempF">--</span> F</div>
    </div>

    <div class="card">
      <div class="card-label">Humidity</div>
      <div class="card-value"><span id="hum">--</span><span class="card-unit"> %</span></div>
      <div class="card-detail"><span id="humDesc">--</span></div>
    </div>

    <div class="card">
      <div class="card-label">Light Level</div>
      <div class="card-value"><span id="light">--</span></div>
      <div class="card-detail"><span id="lightDesc">--</span></div>
      <div class="light-bar"><div class="light-fill" id="lightBar" style="width:0%"></div></div>
    </div>

    <div class="card">
      <div class="card-label">LED Control</div>
      <div class="led-controls">
        <button id="redBtn" class="led-btn" onclick="toggleLed('red')">Red OFF</button>
        <button id="greenBtn" class="led-btn" onclick="toggleLed('green')">Green OFF</button>
      </div>
    </div>
  </div>

  <div class="status-bar">
    <span class="dot"></span> Live &mdash; Last update: <span id="time">--</span>
  </div>
</body>
</html>
  )";

  server.send(200, "text/html", html);
}

// ===== TRY THIS =====
// 1. Add a historical chart using Chart.js CDN
// 2. Add more sensors (e.g., a second DHT11, a soil moisture sensor)
// 3. Add authentication: server.authenticate("admin", "password")
// 4. Store data in SPIFFS and add a /api/history endpoint
// 5. Add a settings page to configure WiFi credentials
