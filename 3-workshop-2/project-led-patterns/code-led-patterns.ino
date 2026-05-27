// =====================================
// Workshop 2: LED Light Show
// Multiple patterns with button control
// =====================================
//
// Hardware: 3x LEDs + 3x 220 ohm resistors + 2x push buttons
// Pins: GPIO 2,4,5 -> LEDs, GPIO 18 -> mode button, GPIO 19 -> speed button
// Libraries: None (built-in only)

// ===== PIN DEFINITIONS =====
const int LED_RED = 2;
const int LED_GREEN = 4;
const int LED_BLUE = 5;
const int BUTTON_MODE = 18;    // Changes pattern
const int BUTTON_SPEED = 19;   // Changes speed

// ===== PATTERN & SPEED VARIABLES =====
int currentPattern = 1;        // Which pattern is active (1-5)
int speedLevel = 2;            // Speed: 1=slow, 2=medium, 3=fast
int delayTime = 500;           // Milliseconds between steps

// Button state tracking (for debouncing)
bool lastModeButtonState = LOW;
bool lastSpeedButtonState = LOW;

// ===== PWM CONFIG =====
// On ESP32 Arduino core 3.x, analogWrite() was removed and PWM moved to
// the LEDC API. We attach each LED pin to a PWM channel at 5 kHz, 8-bit
// resolution. ledcWrite(pin, 0..255) replaces both analogWrite and
// digitalWrite for these pins (255 = fully on, 0 = off).
const int PWM_FREQ_HZ = 5000;
const int PWM_RES_BITS = 8;
const int LED_ON  = 255;
const int LED_OFF = 0;

// Helper: write any value 0..255 to one of our LEDs.
inline void ledWrite(int pin, int value) { ledcWrite(pin, value); }

// ===== SETUP =====
void setup() {
  Serial.begin(9600);

  // Attach each LED pin to a PWM channel.
  ledcAttach(LED_RED,   PWM_FREQ_HZ, PWM_RES_BITS);
  ledcAttach(LED_GREEN, PWM_FREQ_HZ, PWM_RES_BITS);
  ledcAttach(LED_BLUE,  PWM_FREQ_HZ, PWM_RES_BITS);

  // Buttons use the ESP32 internal pull-down.
  pinMode(BUTTON_MODE, INPUT_PULLDOWN);
  pinMode(BUTTON_SPEED, INPUT_PULLDOWN);

  Serial.println("=== LED Light Show ===");
  Serial.println("Button 1 (GPIO 18): change pattern");
  Serial.println("Button 2 (GPIO 19): change speed");
  Serial.println();
}

// ===== MAIN LOOP =====
void loop() {
  checkButtons();

  switch (currentPattern) {
    case 1: patternAllBlink();  break;
    case 2: patternChase();     break;
    case 3: patternBreathing(); break;
    case 4: patternRandom();    break;
    case 5: patternColorMix();  break;
  }
}

// ===== BUTTON HANDLING =====
void checkButtons() {
  bool modeButtonState  = digitalRead(BUTTON_MODE);
  bool speedButtonState = digitalRead(BUTTON_SPEED);

  // Mode button - rising-edge detect
  if (modeButtonState == HIGH && lastModeButtonState == LOW) {
    currentPattern++;
    if (currentPattern > 5) currentPattern = 1;
    Serial.print("Pattern: ");
    Serial.println(currentPattern);
    allOff();
    delay(200);  // basic debounce
  }

  // Speed button - rising-edge detect
  if (speedButtonState == HIGH && lastSpeedButtonState == LOW) {
    speedLevel++;
    if (speedLevel > 3) speedLevel = 1;
    if      (speedLevel == 1) delayTime = 1000;
    else if (speedLevel == 2) delayTime = 500;
    else                      delayTime = 200;
    Serial.print("Speed: ");
    Serial.println(speedLevel);
    delay(200);
  }

  lastModeButtonState  = modeButtonState;
  lastSpeedButtonState = speedButtonState;
}

// ===== PATTERN 1: ALL BLINK TOGETHER =====
void patternAllBlink() {
  allOn();
  delay(delayTime);
  allOff();
  delay(delayTime);
}

// ===== PATTERN 2: CHASE SEQUENCE =====
void patternChase() {
  ledWrite(LED_RED, LED_ON);   ledWrite(LED_GREEN, LED_OFF); ledWrite(LED_BLUE, LED_OFF);
  delay(delayTime);
  ledWrite(LED_RED, LED_OFF);  ledWrite(LED_GREEN, LED_ON);  ledWrite(LED_BLUE, LED_OFF);
  delay(delayTime);
  ledWrite(LED_RED, LED_OFF);  ledWrite(LED_GREEN, LED_OFF); ledWrite(LED_BLUE, LED_ON);
  delay(delayTime);
}

// ===== PATTERN 3: BREATHING EFFECT (PWM) =====
void patternBreathing() {
  for (int b = 0; b <= 255; b += 5) {
    ledWrite(LED_RED, b); ledWrite(LED_GREEN, b); ledWrite(LED_BLUE, b);
    delay(delayTime / 50);
  }
  for (int b = 255; b >= 0; b -= 5) {
    ledWrite(LED_RED, b); ledWrite(LED_GREEN, b); ledWrite(LED_BLUE, b);
    delay(delayTime / 50);
  }
}

// ===== PATTERN 4: RANDOM DISCO =====
void patternRandom() {
  ledWrite(LED_RED,   random(0, 2) ? LED_ON : LED_OFF);
  ledWrite(LED_GREEN, random(0, 2) ? LED_ON : LED_OFF);
  ledWrite(LED_BLUE,  random(0, 2) ? LED_ON : LED_OFF);
  delay(delayTime);
}

// ===== PATTERN 5: COLOR MIXING =====
void patternColorMix() {
  // Yellow = Red + Green
  ledWrite(LED_RED, LED_ON);  ledWrite(LED_GREEN, LED_ON);  ledWrite(LED_BLUE, LED_OFF);
  delay(delayTime);
  // Cyan = Green + Blue
  ledWrite(LED_RED, LED_OFF); ledWrite(LED_GREEN, LED_ON);  ledWrite(LED_BLUE, LED_ON);
  delay(delayTime);
  // Magenta = Red + Blue
  ledWrite(LED_RED, LED_ON);  ledWrite(LED_GREEN, LED_OFF); ledWrite(LED_BLUE, LED_ON);
  delay(delayTime);
  // White = all
  ledWrite(LED_RED, LED_ON);  ledWrite(LED_GREEN, LED_ON);  ledWrite(LED_BLUE, LED_ON);
  delay(delayTime);
}

// ===== HELPERS =====
void allOn() {
  ledWrite(LED_RED, LED_ON);
  ledWrite(LED_GREEN, LED_ON);
  ledWrite(LED_BLUE, LED_ON);
}

void allOff() {
  ledWrite(LED_RED, LED_OFF);
  ledWrite(LED_GREEN, LED_OFF);
  ledWrite(LED_BLUE, LED_OFF);
}

// ===== TRY THIS =====
// 1. Add Pattern 6: your own custom pattern.
// 2. Make patterns speed up over time (decay delayTime in loop).
// 3. Add a "reverse" feature so chase runs backwards.
// 4. Combine patterns (chase with breathing instead of solid on).
// 5. Smooth color crossfade: interpolate between two colors using ledcWrite.
