// =====================================
// WORKSHOP 1: LED CONTROLLED BY BUTTON
// Your first real interactive circuit!
// =====================================

// ===== PIN DEFINITIONS =====
const int LED_PIN = 2;      // LED connected to GPIO pin 2
const int BUTTON_PIN = 4;   // Button connected to GPIO pin 4

// ===== SETUP (runs once at startup) =====
void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  
  // Configure pins
  pinMode(LED_PIN, OUTPUT);     // LED is something we control
  pinMode(BUTTON_PIN, INPUT);   // Button is something we read
  
  // Print welcome message
  Serial.println("=== LED + Button Circuit ===");
  Serial.println("Press the button to control the LED!");
  Serial.println("");
}

// ===== MAIN PROGRAM (runs forever) =====
void loop() {
  // Read the button state
  // HIGH = pressed (button makes connection)
  // LOW = released (button breaks connection)
  int buttonState = digitalRead(BUTTON_PIN);
  
  // If button is pressed
  if (buttonState == HIGH) {
    digitalWrite(LED_PIN, HIGH);  // Turn LED on
    Serial.println("🔘 Button pressed - LED ON");
    
  } else {
    // Button is not pressed
    digitalWrite(LED_PIN, LOW);   // Turn LED off
    Serial.println("Button released - LED OFF");
  }
  
  // Wait a bit before checking again
  // (prevents Serial from printing too fast)
  delay(100);
}

// ===== HOW THIS WORKS =====
// 1. setup() tells Arduino: "Make pin 2 an output, pin 4 an input"
// 2. loop() runs continuously:
//    - Read pin 4: Is button pressed (HIGH) or released (LOW)?
//    - If pressed: Set pin 2 to HIGH (turn LED on)
//    - If not pressed: Set pin 2 to LOW (turn LED off)
// 3. Print messages so you can see what's happening

// ===== TRY THIS =====
// Experiment 1: Change delay(100) to delay(500) - prints slower
// Experiment 2: Remove the if/else to always turn LED on
// Experiment 3: Add another LED on pin 5 - control 2 LEDs!

