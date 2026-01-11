# 🔧 Workshop 3: Troubleshooting

## WiFi Connection Issues

### "Can't connect to WiFi"

**Possible causes:**
1. Wrong SSID or password
2. Using 5 GHz network (ESP32 only supports 2.4 GHz)
3. Network security settings

**Fixes:**
- Double-check SSID and password (case-sensitive!)
- Make sure your router has 2.4 GHz enabled
- Try connecting to phone hotspot first (for testing)
- Check Serial Monitor for error messages

### "Connected but can't access webpage"

**Debug steps:**
1. Note the IP address from Serial Monitor
2. Make sure computer is on same WiFi network
3. Try `ping IP_ADDRESS` from terminal
4. Use `http://` not `https://`
5. Try different browser

---

## Web Server Issues

### "Page loads but shows '--' for all values"

**Fixes:**
- Check `/api/data` endpoint: `http://ESP32_IP/api/data`
- Open browser console (F12) and check for errors
- Verify sensors are connected correctly
- Check DHT library is installed

### "ESP32 crashes when accessing page"

**Possible causes:**
- Out of memory
- Too many simultaneous connections

**Fixes:**
- Reduce HTML size
- Restart ESP32
- Access from one device at a time

---

## Bluetooth Issues

### "Can't find ESP32 device"

**Debug steps:**
1. Check Serial Monitor - is Bluetooth started?
2. Turn Bluetooth off/on on phone
3. Forget old pairings
4. Move phone closer to ESP32
5. Restart ESP32

### "Connected but can't send/receive data"

**Fixes:**
- Make sure Serial Bluetooth Terminal app is connected
- Check baud rate settings
- Try sending data from Serial Monitor first
- Look for errors in Serial Monitor

---

## Sensor Issues

### "Temperature/humidity shows NaN"

**Fixes:**
- Check DHT11 connections
- Verify DHT library is installed
- Wait 2 seconds after power-on
- Try different GPIO pin

### "Light sensor always reads 0 or 4095"

**Fixes:**
- Check LDR connections
- Verify 10kΩ resistor is in place
- Test with voltmeter
- Cover/uncover sensor and check if value changes

---

## Code Upload Issues

### "Sketch too large"

**Fixes:**
- Reduce HTML size in strings
- Use PROGMEM for large strings
- Remove unnecessary libraries

### "Compilation errors"

**Fixes:**
- Install required libraries (WiFi, WebServer, DHT, BluetoothSerial)
- Check board is set to "ESP32 Dev Module"
- Update ESP32 board package

---

## Network Discovery

### Can't remember IP address?

**Solutions:**
1. Check Serial Monitor (it prints on startup)
2. Check your router's DHCP client list
3. Use network scanner app
4. Use mDNS: `http://esp32.local` (if configured)

---

## General Tips

- **Always check Serial Monitor first** - it shows helpful debug info
- **Restart ESP32** - fixes many issues
- **Test WiFi connection separately** before adding web server
- **Use simple HTML first** then add features gradually
- **Check power supply** - USB cable quality matters!

---

**Still stuck?** Open an [Issue](https://github.com/zoharsf/embedded-electronics-101/issues)!
