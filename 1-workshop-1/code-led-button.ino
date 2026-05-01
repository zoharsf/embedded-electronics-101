// =====================================
// WORKSHOP 1: LED CONTROLLED BY BUTTON
// Your first real interactive circuit!
// =====================================
//
// Hardware: 1x LED + 1x 220 ohm resistor + 1x push button
// Pins: GPIO 2 -> LED, GPIO 4 -> Button
// Libraries: None (built-in only)

// ===== PIN DEFINITIONS =====
const int LED_PIN = 2;      // LED connected to GPIO pin 2
const int BUTTON_PIN = 4;   // Button connected to GPIO pin 4

// ===== SETUP (runs once at startup) =====
void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  
  // Configure pins
  pinMode(LED_PIN, OUTPUT);           // LED is something we control (output)
  pinMode(BUTTON_PIN, INPUT_PULLDOWN); // Button is something we read (input with internal pull-down resistor)
  
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

// ===== TRY THIS - WARM-UP =====
// Experiment 1: Change delay(100) to delay(500). Notice how the Serial output slows down.
// Experiment 2: Add a second LED on GPIO 5 with a 220Ω resistor. Make both LEDs follow the button.

// ===== TRY THIS - REAL STRETCH GOALS =====
// Each one has an acceptance criterion. If your code does the thing, you're done.

// Stretch 1: TOGGLE-ON-PRESS
// Make the LED toggle each time the button is *pressed* (not while held).
// You'll need to detect the rising edge: the moment when button goes LOW->HIGH.
// Hint: store the previous button state in a variable.
// Done when: one press = LED on, next press = LED off.

// Stretch 2: NON-BLOCKING BLINK
// While the button is *not* pressed, blink the LED at 2 Hz.
// While the button *is* pressed, the LED stays steady on.
// Constraint: don't use delay() in your main loop - use millis() instead.
// Done when: the button responds instantly even mid-blink (no perceptible lag).

// Stretch 3: PRESS-DURATION BRIGHTNESS
// Use ledcAttach() / ledcWrite() (LEDC PWM API) to control LED brightness.
// The longer you hold the button, the brighter the LED gets (0-255).
// On release, the brightness resets to 0 over 1 second.
// Done when: tap = dim, hold 2 seconds = full brightness, release = smooth fade-down.

// Stretch 4: DEBOUNCE COUNTER
// Print a counter to Serial that increments by exactly 1 per physical press,
// even though digitalRead() may bounce 5-20 times per real press.
// Approach: ignore button state changes within ~30 ms of the previous change.
// Done when: 10 presses prints exactly 1..10 in Serial, never skipping or doubling.

