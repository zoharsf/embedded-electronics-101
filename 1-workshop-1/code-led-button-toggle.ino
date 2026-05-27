// ==========================================
// WORKSHOP 1 (BONUS): LED TOGGLED BY BUTTON
// Press once = LED on. Press again = LED off.
// ==========================================
//
// Hardware: 1x LED + 1x 220 ohm resistor + 1x push button
// Pins: GPIO 2 -> LED, GPIO 4 -> Button
// Libraries: None (built-in only)
//
// This is the SAME circuit as code-led-button.ino. Only the code changes.
//
// HOW IT DIFFERS FROM THE MAIN PROJECT:
//   Main project (code-led-button.ino): LED is on ONLY while the button is held.
//   This bonus build:                   LED toggles - one press turns it on and
//                                       it STAYS on; the next press turns it off.
//
// The trick is "edge detection": instead of reacting to the button being HIGH,
// we react to the *moment* it changes from LOW to HIGH (the "rising edge" - the
// instant of the press). We do that by remembering the previous reading.

// ===== PIN DEFINITIONS =====
const int LED_PIN = 2;      // LED connected to GPIO pin 2
const int BUTTON_PIN = 4;   // Button connected to GPIO pin 4

// ===== STATE VARIABLES =====
// These keep their value between loop() runs.
bool ledOn = false;             // Is the LED currently on? Starts off.
int lastButtonState = LOW;      // What the button read on the previous loop.

// ===== SETUP (runs once at startup) =====
void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);            // LED is something we control (output)
  pinMode(BUTTON_PIN, INPUT_PULLDOWN); // Button is an input; internal pull-down
                                       // keeps it LOW until the button is pressed

  digitalWrite(LED_PIN, LOW);          // Make sure the LED starts off

  Serial.println("=== LED Toggle (bonus build) ===");
  Serial.println("Press the button to toggle the LED on and off.");
  Serial.println("");
}

// ===== MAIN PROGRAM (runs forever) =====
void loop() {
  // Read the button right now.
  int buttonState = digitalRead(BUTTON_PIN);

  // Rising edge: it was LOW last time, and it is HIGH now.
  // That means the button was just pressed THIS loop.
  if (buttonState == HIGH && lastButtonState == LOW) {
    ledOn = !ledOn;                       // Flip the LED state (on->off, off->on)
    digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
    Serial.println(ledOn ? "Press detected - LED ON" : "Press detected - LED OFF");

    // Small wait so a single press isn't read as several presses
    // (a cheap form of "debouncing" - see Stretch 4 in the main project
    // for a more robust, non-blocking approach).
    delay(50);
  }

  // Remember this reading so the next loop can compare against it.
  lastButtonState = buttonState;
}

// ===== HOW THIS WORKS =====
// 1. We track two things across loops: whether the LED is on (ledOn) and what
//    the button read last time (lastButtonState).
// 2. Every loop we read the button. If it just went from LOW to HIGH, that is
//    a fresh press, so we flip ledOn and update the LED.
// 3. Because we only act on the *change*, holding the button down does nothing
//    extra - the LED stays in whatever state the last press set.

// ===== TRY THIS =====
// Experiment 1: Remove the `&& lastButtonState == LOW` check. Now the LED flips
//               every loop while held - it flickers. That check is what makes
//               one press equal one toggle.
// Experiment 2: Replace the delay(50) debounce with a millis()-based debounce
//               so the loop never blocks (see Stretch 4 in code-led-button.ino).
