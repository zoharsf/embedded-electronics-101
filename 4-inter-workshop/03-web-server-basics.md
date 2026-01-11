# 🌐 Web Server Fundamentals: Hosting Pages on ESP32

## What is a Web Server?

A **web server** is software that serves web pages over HTTP. Your ESP32 can be a web server!

**How it works:**
1. ESP32 connects to WiFi
2. ESP32 listens on port 80 (HTTP)
3. Browser requests page from ESP32's IP
4. ESP32 sends HTML page back
5. Browser displays the page

**Mind-blowing fact:** Your tiny microcontroller can host websites!

---

## HTTP Basics

### Request-Response Cycle

**Client (Browser) Request:**
```
GET / HTTP/1.1
Host: 192.168.1.100
```

**Server (ESP32) Response:**
```
HTTP/1.1 200 OK
Content-Type: text/html

<html>
  <body>
    <h1>Hello from ESP32!</h1>
  </body>
</html>
```

### HTTP Methods

- **GET:** Request data (view a page)
- **POST:** Send data (submit a form)
- **PUT:** Update data
- **DELETE:** Remove data

**For Workshop 3, we'll use GET and POST**

---

## Simple Web Server Code

```cpp
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YourNetwork";
const char* password = "YourPassword";

WebServer server(80);  // Port 80 (HTTP)

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Hello from ESP32!</h1>";
  html += "<p>This page is hosted on a microcontroller!</p>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(9600);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected!");
  Serial.print("Visit: http://");
  Serial.println(WiFi.localIP());
  
  // Set up web server routes
  server.on("/", handleRoot);
  
  // Start server
  server.begin();
}

void loop() {
  server.handleClient();  // Listen for requests
}
```

**What this does:**
1. Connects to WiFi
2. Starts web server on port 80
3. When someone visits `/`, serves HTML page
4. Keeps listening for requests in loop()

**To test:** Open browser, go to `http://ESP32_IP_ADDRESS`

---

## HTML Crash Course

### Basic Structure

```html
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 Dashboard</title>
</head>
<body>
  <h1>Main Heading</h1>
  <p>This is a paragraph.</p>
  <button>Click Me</button>
</body>
</html>
```

### Common Tags

| Tag | Purpose | Example |
|-----|---------|---------|
| `<h1>` to `<h6>` | Headings | `<h1>Title</h1>` |
| `<p>` | Paragraph | `<p>Text here</p>` |
| `<br>` | Line break | `Line 1<br>Line 2` |
| `<a>` | Link | `<a href="/page">Click</a>` |
| `<button>` | Button | `<button>Press</button>` |
| `<div>` | Container | `<div>Content</div>` |

### Forms (User Input)

```html
<form action="/led" method="POST">
  <label>LED Control:</label>
  <button type="submit" name="state" value="on">Turn ON</button>
  <button type="submit" name="state" value="off">Turn OFF</button>
</form>
```

---

## Multiple Routes

```cpp
void handleRoot() {
  server.send(200, "text/html", "<h1>Home Page</h1>");
}

void handleAbout() {
  server.send(200, "text/html", "<h1>About Page</h1>");
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Page not found");
}

void setup() {
  // ... WiFi connection code ...
  
  server.on("/", handleRoot);
  server.on("/about", handleAbout);
  server.onNotFound(handleNotFound);
  
  server.begin();
}
```

**URLs:**
- `http://192.168.1.100/` → Home page
- `http://192.168.1.100/about` → About page
- `http://192.168.1.100/anything` → 404 error

---

## Interactive Example: LED Control

```cpp
#include <WiFi.h>
#include <WebServer.h>

const int LED_PIN = 2;
WebServer server(80);

void handleRoot() {
  String html = "<!DOCTYPE html><html><body>";
  html += "<h1>ESP32 LED Control</h1>";
  html += "<p>LED is currently: ";
  html += digitalRead(LED_PIN) ? "ON" : "OFF";
  html += "</p>";
  html += "<a href='/on'><button>Turn ON</button></a>";
  html += "<a href='/off'><button>Turn OFF</button></a>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void handleLEDOn() {
  digitalWrite(LED_PIN, HIGH);
  server.sendHeader("Location", "/");  // Redirect to home
  server.send(303);  // Redirect status code
}

void handleLEDOff() {
  digitalWrite(LED_PIN, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  
  // WiFi connection code here...
  
  server.on("/", handleRoot);
  server.on("/on", handleLEDOn);
  server.on("/off", handleLEDOff);
  server.begin();
}

void loop() {
  server.handleClient();
}
```

**How it works:**
1. Visit home page → Shows LED status and buttons
2. Click "Turn ON" → Goes to `/on`, LED turns on, redirects to home
3. Click "Turn OFF" → Goes to `/off`, LED turns off, redirects to home

---

## Displaying Sensor Data

```cpp
#include <DHT.h>

DHT dht(5, DHT11);

void handleSensors() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  String html = "<!DOCTYPE html><html><body>";
  html += "<h1>Sensor Dashboard</h1>";
  html += "<p>Temperature: " + String(temp) + " &deg;C</p>";
  html += "<p>Humidity: " + String(humidity) + " %</p>";
  html += "<meta http-equiv='refresh' content='5'>";  // Auto-refresh every 5 seconds
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void setup() {
  dht.begin();
  // ... WiFi and server setup ...
  server.on("/", handleSensors);
  server.begin();
}
```

**Features:**
- Shows real-time sensor data
- Auto-refreshes every 5 seconds
- No app needed - just a browser!

---

## JSON APIs

**Send data as JSON instead of HTML:**

```cpp
void handleAPI() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  String json = "{";
  json += "\"temperature\":" + String(temp) + ",";
  json += "\"humidity\":" + String(humidity);
  json += "}";
  
  server.send(200, "application/json", json);
}

void setup() {
  // ... WiFi setup ...
  server.on("/api/sensors", handleAPI);
  server.begin();
}
```

**Output:**
```json
{
  "temperature": 23.5,
  "humidity": 45.2
}
```

**Use case:** Mobile apps, JavaScript fetch(), data logging

---

## Adding Style with CSS

```cpp
void handleRoot() {
  String html = R"(
<!DOCTYPE html>
<html>
<head>
  <style>
    body {
      font-family: Arial, sans-serif;
      max-width: 600px;
      margin: 50px auto;
      background: #f0f0f0;
    }
    .card {
      background: white;
      padding: 20px;
      border-radius: 10px;
      box-shadow: 0 2px 10px rgba(0,0,0,0.1);
    }
    button {
      background: #4CAF50;
      color: white;
      padding: 15px 30px;
      border: none;
      border-radius: 5px;
      font-size: 16px;
      cursor: pointer;
      margin: 5px;
    }
    button:hover {
      background: #45a049;
    }
  </style>
</head>
<body>
  <div class="card">
    <h1>ESP32 Dashboard</h1>
    <p>Temperature: 23.5°C</p>
    <button>Turn LED ON</button>
    <button>Turn LED OFF</button>
  </div>
</body>
</html>
  )";
  
  server.send(200, "text/html", html);
}
```

**Result:** Beautiful, modern-looking dashboard!

---

## JavaScript for Interactivity

**Update data without page reload:**

```cpp
String html = R"(
<!DOCTYPE html>
<html>
<body>
  <h1>Temperature: <span id="temp">--</span>°C</h1>
  <script>
    function updateData() {
      fetch('/api/sensors')
        .then(response => response.json())
        .then(data => {
          document.getElementById('temp').innerText = data.temperature;
        });
    }
    
    setInterval(updateData, 2000);  // Update every 2 seconds
    updateData();  // Initial load
  </script>
</body>
</html>
)";
```

**Features:**
- Data updates in real-time
- No page flicker
- Professional-looking dashboard

---

## mDNS: Easy Access

**Instead of remembering `192.168.1.100`, use `esp32.local`:**

```cpp
#include <ESPmDNS.h>

void setup() {
  // ... WiFi connection ...
  
  if (MDNS.begin("esp32")) {
    Serial.println("mDNS started! Access at http://esp32.local");
  }
  
  server.begin();
}
```

**Now access your ESP32 at:** `http://esp32.local`

---

## Security Basics

### Authentication

```cpp
void handleRoot() {
  if (!server.authenticate("admin", "password123")) {
    return server.requestAuthentication();
  }
  
  // Show page only if authenticated
  server.send(200, "text/html", "<h1>Secret Dashboard</h1>");
}
```

**Browser will prompt for username and password!**

### HTTPS (Advanced)

- Requires SSL certificate
- More complex setup
- Better security for sensitive data
- Covered in advanced projects

---

## Common Web Server Issues

### "Can't access ESP32 page"
- Check IP address is correct
- Make sure computer is on same WiFi network
- Try http:// not https://
- Check ESP32 is still connected to WiFi

### "Page loads slowly"
- Too much HTML (keep it simple)
- No delay() in handlers
- Use async server (advanced)

### "ESP32 crashes when accessing page"
- Out of memory (too much HTML)
- Use PROGMEM for large strings
- Reduce HTML size

---

## Best Practices

1. **Keep HTML simple** - ESP32 has limited memory
2. **Use String reserve()** - Prevent memory fragmentation
3. **Handle errors** - Check WiFi status regularly
4. **Security** - Don't expose to internet without protection
5. **Testing** - Test on multiple browsers/devices

---

## What You Can Build

With web servers, you can create:
- ✅ Sensor dashboards
- ✅ Smart home control panels
- ✅ Data loggers with visualization
- ✅ Configuration interfaces
- ✅ Remote monitoring systems
- ✅ IoT device management

---

## Try This Before Workshop 3

1. **Set up basic web server**
2. **Access it from your computer**
3. **Try controlling an LED** through the web page
4. **Display sensor data** on a web page
5. **Bookmark the IP address** - you'll need it for Workshop 3!

---

**Next →** [Pick Your Workshop 3 Project](/4-inter-workshop/project-picker.md)
