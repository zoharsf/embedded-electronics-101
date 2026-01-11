# 📡 WiFi Basics: Connecting ESP32 to the Internet

## What is WiFi?

WiFi is a **wireless networking technology** that lets devices communicate over radio waves. Your ESP32 has built-in WiFi!

**Key concepts:**
- **SSID:** Network name (like "Home WiFi")
- **Password:** Security key to access network
- **IP Address:** Unique identifier for your ESP32 (like "192.168.1.100")
- **Client vs Server:** Your ESP32 can be both!

---

## How ESP32 WiFi Works

### Three Modes

1. **Station Mode (STA):** ESP32 connects to existing WiFi (like your home network)
2. **Access Point Mode (AP):** ESP32 creates its own WiFi network
3. **Both:** Can do both simultaneously!

**For Workshop 3, we'll use Station Mode** (connecting to your home WiFi)

---

## Basic WiFi Connection Code

```cpp
#include <WiFi.h>

const char* ssid = "YourNetworkName";
const char* password = "YourPassword";

void setup() {
  Serial.begin(9600);
  
  // Start WiFi connection
  WiFi.begin(ssid, password);
  
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // WiFi stays connected automatically
}
```

**What this does:**
1. Connects to specified WiFi network
2. Waits until connected (prints dots while waiting)
3. Prints the IP address once connected

---

## Understanding IP Addresses

### Local vs Public IP

**Local IP (Private):** Used within your home network
- Format: `192.168.x.x` or `10.x.x.x`
- Only accessible on your local network
- This is what your ESP32 gets

**Public IP (External):** Used on the internet
- Assigned by your ISP
- Accessible from anywhere (with proper setup)
- Requires port forwarding or cloud service

**For Workshop 3:** We'll use local IP addresses (simpler and more secure)

---

## WiFi Status Codes

Your ESP32 reports connection status:

```cpp
WL_CONNECTED      // Successfully connected
WL_NO_SSID_AVAIL  // Network not found
WL_CONNECT_FAILED // Wrong password
WL_DISCONNECTED   // Not connected
```

**Example: Check if still connected**
```cpp
if (WiFi.status() == WL_CONNECTED) {
  Serial.println("Still connected!");
} else {
  Serial.println("Connection lost, reconnecting...");
  WiFi.reconnect();
}
```

---

## Scanning for Networks

**Want to see available WiFi networks?**

```cpp
#include <WiFi.h>

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  Serial.println("Scanning for networks...");
  int n = WiFi.scanNetworks();
  
  Serial.print(n);
  Serial.println(" networks found:");
  
  for (int i = 0; i < n; i++) {
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(WiFi.SSID(i));
    Serial.print(" (");
    Serial.print(WiFi.RSSI(i));
    Serial.println(" dBm)");
  }
}
```

**Output example:**
```
5 networks found:
1: Home WiFi (-45 dBm)
2: Neighbor WiFi (-72 dBm)
3: Coffee Shop (-80 dBm)
```

**Signal strength:**
- **-30 to -50 dBm:** Excellent
- **-50 to -60 dBm:** Good
- **-60 to -70 dBm:** Fair
- **-70+ dBm:** Weak

---

## WiFi Events (Advanced)

ESP32 can react to WiFi events:

```cpp
void WiFiEvent(WiFiEvent_t event) {
  switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.println("Connected! IP: " + WiFi.localIP().toString());
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("Disconnected!");
      break;
  }
}

void setup() {
  WiFi.onEvent(WiFiEvent);
  WiFi.begin(ssid, password);
}
```

---

## Common WiFi Issues

### "Can't connect to network"
- Check SSID spelling (case-sensitive!)
- Check password
- Make sure you're using 2.4 GHz WiFi (ESP32 doesn't support 5 GHz)
- Move closer to router

### "Connection keeps dropping"
- Weak signal (check RSSI)
- Router too far away
- Power supply issues (use good USB cable)
- Too many devices on network

### "Can't find ESP32 on network"
- Check IP address in Serial Monitor
- Make sure computer is on same network
- Try pinging the IP address

---

## Security Best Practices

⚠️ **Never hardcode passwords in public code!**

**Bad (password visible):**
```cpp
const char* password = "MySecretPassword123";
```

**Better (use separate file):**
```cpp
// In secrets.h file (add to .gitignore)
const char* ssid = "YourNetwork";
const char* password = "YourPassword";

// In main code
#include "secrets.h"
```

**Best (for production):**
- Use WPA2-Enterprise
- Store credentials in EEPROM
- Use HTTPS instead of HTTP
- Implement authentication

---

## What You Can Do With WiFi

Once connected, your ESP32 can:
- ✅ Host web pages (web server)
- ✅ Send data to cloud services (IoT platforms)
- ✅ Fetch data from APIs (weather, stocks, etc.)
- ✅ Send email/SMS notifications
- ✅ Control other smart devices
- ✅ Remote monitoring and control

---

## Try This Before Workshop 3

1. **Modify the connection code** to use your home WiFi
2. **Upload and test** - does it connect?
3. **Note your ESP32's IP address** - you'll need it!
4. **Try the network scanner** - how many networks do you see?

---

**Next →** [Bluetooth Basics](/4-inter-workshop/02-bluetooth-basics.md)
