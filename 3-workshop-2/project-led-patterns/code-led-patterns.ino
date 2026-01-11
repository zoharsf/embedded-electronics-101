// =====================================
// Workshop 2: LED Light Show
// Multiple patterns with button control
// =====================================

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

// ===== SETUP =====
void setup() {
  Serial.begin(9600);
  
  // Configure LED pins as outputs
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  
  // Configure button pins as inputs with pull-down resistors
  pinMode(BUTTON_MODE, INPUT_PULLDOWN);
  pinMode(BUTTON_SPEED, INPUT_PULLDOWN);
  
  Serial.println("=== LED Light Show ===");
  Serial.println("Button 1: Change Pattern");
  Serial.println("Button 2: Change Speed");
  Serial.println("");
}

// ===== MAIN LOOP =====
void loop() {
  // Check for button presses
  checkButtons();
  
  // Run the current pattern
  switch (currentPattern) {
    case 1:
      patternAllBlink();
      break;
    case 2:
      patternChase();
      break;
    case 3:
      patternBreathing();
      break;
    case 4:
      patternRandom();
      break;
    case 5:
      patternColorMix();
      break;
  }
}

// ===== BUTTON HANDLING =====
void checkButtons() {
  // Read button states
  bool modeButtonState = digitalRead(BUTTON_MODE);
  bool speedButtonState = digitalRead(BUTTON_SPEED);
  
  // Mode button pressed (with simple debouncing)
  if (modeButtonState == HIGH && lastModeButtonState == LOW) {
    currentPattern++;
    if (currentPattern > 5) currentPattern = 1;
    
    Serial.print("Pattern changed to: ");
    Serial.println(currentPattern);
    
    // Turn off all LEDs when switching patterns
    allOff();
    delay(200);  // Debounce delay
  }
  
  // Speed button pressed (with simple debouncing)
  if (speedButtonState == HIGH && lastSpeedButtonState == LOW) {
    speedLevel++;
    if (speedLevel > 3) speedLevel = 1;
    
    // Update delay time based on speed level
    if (speedLevel == 1) delayTime = 1000;      // Slow
    else if (speedLevel == 2) delayTime = 500;  // Medium
    else delayTime = 200;                        // Fast
    
    Serial.print("Speed changed to: ");
    Serial.println(speedLevel);
    delay(200);  // Debounce delay
  }
  
  // Remember button states
  lastModeButtonState = modeButtonState;
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
  // Red
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  delay(delayTime);
  
  // Green
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, LOW);
  delay(delayTime);
  
  // Blue
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, HIGH);
  delay(delayTime);
}

// ===== PATTERN 3: BREATHING EFFECT (PWM) =====
void patternBreathing() {
  // Fade up
  for (int brightness = 0; brightness <= 255; brightness += 5) {
    analogWrite(LED_RED, brightness);
    analogWrite(LED_GREEN, brightness);
    analogWrite(LED_BLUE, brightness);
    delay(delayTime / 50);
  }
  
  // Fade down
  for (int brightness = 255; brightness >= 0; brightness -= 5) {
    analogWrite(LED_RED, brightness);
    analogWrite(LED_GREEN, brightness);
    analogWrite(LED_BLUE, brightness);
    delay(delayTime / 50);
  }
}

// ===== PATTERN 4: RANDOM DISCO =====
void patternRandom() {
  // Random combination of LEDs
  digitalWrite(LED_RED, random(0, 2));    // 0 or 1
  digitalWrite(LED_GREEN, random(0, 2));
  digitalWrite(LED_BLUE, random(0, 2));
  delay(delayTime);
}

// ===== PATTERN 5: COLOR MIXING =====
void patternColorMix() {
  // Red + Green = Yellow
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, LOW);
  delay(delayTime);
  
  // Green + Blue = Cyan
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  delay(delayTime);
  
  // Red + Blue = Magenta
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, HIGH);
  delay(delayTime);
  
  // All on = White
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  delay(delayTime);
}

// ===== HELPER FUNCTIONS =====
void allOn() {
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);
}

void allOff() {
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
}

// ===== TRY THIS =====
// 1. Add Pattern 6: Your own custom pattern!
// 2. Make patterns speed up over time
// 3. Add a "reverse" button to run patterns backwards
// 4. Combine patterns (e.g., chase + breathing)
