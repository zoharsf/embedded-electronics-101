# 📚 Glossary

Quick reference for electronics and programming terms used throughout this workshop series.

---

## A

### ADC (Analog-to-Digital Converter)
Hardware that converts analog voltages into digital numbers. The ESP32 ADC reads 0-3.3V and outputs values 0-4095 (12-bit).

### Analog
A range of values, like a volume knob. The ESP32 can read analog voltages (0-3.3V) as values from 0 to 4095.

### Anode
The positive terminal of a component like an LED. On an LED, the anode is the longer leg.

---

## B

### Baud Rate
How fast the board talks to your computer over Serial. Common values: 9600, 115200. Both sides must match!

### BLE (Bluetooth Low Energy)
A power-efficient version of Bluetooth designed for IoT devices. Uses less energy than Bluetooth Classic but has lower data throughput.

### Bluetooth
Short-range wireless technology (10-30m) for connecting devices. The ESP32 supports both Bluetooth Classic and BLE.

### Breadboard
A board with holes for testing circuits without soldering. Internal connections run in rows of 5, with power rails along the sides.

---

## C

### Cathode
The negative terminal of a component like an LED. On an LED, the cathode is the shorter leg (flat side of the rim).

### Client
A device or program that requests data from a server. Your web browser is a client when it loads a page from the ESP32.

### Cloud
Remote servers on the internet that store and process data. IoT devices can send sensor data to cloud services like ThingSpeak or Firebase.

### Current (I)
How much electricity flows. Measured in amps (A) or milliamps (mA). LEDs typically need about 20mA.

---

## D

### Debouncing
Filtering out rapid on/off signals from a mechanical button press. Buttons physically "bounce" for a few milliseconds when pressed, causing multiple false readings. Fixed with a short delay (10-50ms) in code.

### DHT11
A basic digital temperature and humidity sensor. Reads 0-50°C and 20-90% humidity. Needs at least 2 seconds between readings.

### Digital
On or off. 0 or 1. HIGH or LOW. Like a light switch. Digital signals have only two states.

---

## F

### Firmware
Software permanently stored on a microcontroller's flash memory. Your Arduino sketch becomes firmware when uploaded.

### Flash Memory
Non-volatile storage on the ESP32 (4 MB). Holds your uploaded program. Data persists when power is off.

---

## G

### GND (Ground)
The 0V reference point in a circuit. All voltages are measured relative to ground. Always connect GND between the ESP32 and your components.

### GPIO (General-Purpose Input/Output)
A pin on the ESP32 that can read or control voltage. Can be configured as input (read sensors/buttons) or output (control LEDs/motors).

---

## H

### HTTP (HyperText Transfer Protocol)
The protocol web browsers use to communicate with web servers. When you visit a web page, your browser sends an HTTP GET request.

---

## I

### I2C (Inter-Integrated Circuit)
A communication protocol using two wires (SDA for data, SCL for clock) to connect multiple sensors to a microcontroller. Used by OLED displays, some sensors, and more.

### Interrupt
A signal that pauses normal code execution to handle an urgent event (like a button press). More responsive than checking in a loop.

### IoT (Internet of Things)
Connecting everyday devices to the internet so they can send and receive data. Your ESP32 weather station is an IoT device!

### IP Address
A number that identifies a device on a network (e.g., 192.168.1.100). You need the ESP32's IP address to access its web server.

---

## J

### JSON (JavaScript Object Notation)
A lightweight data format used to send structured data between devices. Example: `{"temperature": 23.5, "humidity": 45}`.

---

## L

### LDR (Light-Dependent Resistor)
A resistor whose resistance changes with light. Dark = high resistance (~1MΩ), bright = low resistance (~1kΩ). Also called a photoresistor.

### LED (Light-Emitting Diode)
A component that lights up when current flows through it in the correct direction. Always use a current-limiting resistor (typically 220Ω).

---

## M

### mDNS (Multicast DNS)
A protocol that lets you access the ESP32 by name (like `esp32.local`) instead of memorizing an IP address.

### Microcontroller
A small computer on a single chip that runs one program repeatedly. The ESP32 is a microcontroller with WiFi and Bluetooth built in.

### MQTT (Message Queuing Telemetry Transport)
A lightweight messaging protocol for IoT. Devices publish messages to topics and subscribe to receive messages. More efficient than HTTP for frequent small updates.

---

## O

### Ohm's Law
The fundamental relationship: V = I × R (Voltage = Current × Resistance). Use it to calculate resistor values for LEDs: R = (V_source - V_LED) / I_LED.

---

## P

### Pull-down Resistor
A resistor connecting a pin to GND, ensuring it reads LOW when nothing is driving it HIGH. The ESP32 has built-in pull-downs: `pinMode(pin, INPUT_PULLDOWN)`.

### Pull-up Resistor
A resistor connecting a pin to VCC, ensuring it reads HIGH when nothing is driving it LOW. Common value: 10kΩ.

### PWM (Pulse Width Modulation)
Rapidly switching a pin on and off to simulate intermediate voltages. Used to control LED brightness and motor speed. Duty cycle 0-255 (0% to 100%).

---

## R

### Resistance (R)
Opposition to current flow. Measured in ohms (Ω). Resistors protect components (like LEDs) from too much current.

### REST API
A way to interact with a web server using standard HTTP methods (GET, POST, PUT, DELETE). Your ESP32's `/api/data` endpoint is a REST API.

---

## S

### Schematic
A diagram showing how components connect using standard symbols. Schematics show the logical connections, not the physical layout.

### Serial Monitor
Shows messages from your board in the Arduino IDE. Helpful for debugging! Open it with the magnifying glass icon. Make sure the baud rate matches your code.

### Sketch
An Arduino program (the code you write and upload). Consists of a `setup()` function (runs once) and `loop()` function (runs forever).

### SPI (Serial Peripheral Interface)
A fast communication protocol using 4 wires (MOSI, MISO, SCK, CS). Used for SD cards, displays, and high-speed sensors.

### SSID (Service Set Identifier)
The name of a WiFi network. You need the SSID and password to connect your ESP32 to WiFi.

---

## U

### UART (Universal Asynchronous Receiver-Transmitter)
A serial communication protocol using TX (transmit) and RX (receive) pins. The Serial Monitor uses UART over USB.

---

## V

### VCC
The positive power supply voltage. On ESP32 circuits this is typically 3.3V. Some components accept 5V (check datasheets!).

### Voltage (V)
The electrical "push" that makes electricity flow. Like water pressure. The ESP32 operates at 3.3V logic. Applying 5V to GPIO pins can damage it!

### Voltage Divider
A circuit with two resistors that produces an output voltage that is a fraction of the input. Used with the LDR to create a readable analog signal.

---

## W

### Web Server
Software that listens for HTTP requests and sends back web pages or data. The ESP32 can run a web server to host dashboards and APIs.

### WiFi
Wireless networking technology. The ESP32 supports 2.4 GHz WiFi (802.11 b/g/n). It cannot connect to 5 GHz networks.
