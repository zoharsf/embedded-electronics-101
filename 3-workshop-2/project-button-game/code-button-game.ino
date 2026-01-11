// =====================================
// Workshop 2: Button Reaction Game
// Test your reflexes and memory!
// =====================================

// ===== PIN DEFINITIONS =====
const int LED_PINS[] = {2, 4, 5, 12};       // LED pins
const int BUTTON_PINS[] = {18, 19, 21, 22}; // Button pins
const int NUM_LEDS = 4;

// ===== GAME VARIABLES =====
int gameMode = 1;           // 1 = Reaction Timer, 2 = Memory Game
int sequence[50];           // Memory game sequence storage
int sequenceLength = 0;     // Current sequence length
int currentRound = 1;       // Current round number
unsigned long reactionTime; // Reaction time in ms
unsigned long bestTime = 999999; // Best reaction time

// ===== SETUP =====
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));  // Seed random number generator
  
  // Configure LED pins
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  
  // Configure button pins
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLDOWN);
  }
  
  Serial.println("=== BUTTON GAME ===");
  Serial.println("Get ready!");
  
  // Startup animation
  startupAnimation();
  
  Serial.println("\nMODE 1: Reaction Timer");
  Serial.println("Press the button that lights up as fast as you can!\n");
  
  delay(2000);
}

// ===== MAIN LOOP =====
void loop() {
  if (gameMode == 1) {
    reactionMode();
  } else {
    memoryMode();
  }
}

// ===== STARTUP ANIMATION =====
void startupAnimation() {
  // Chase pattern
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], HIGH);
    delay(100);
    digitalWrite(LED_PINS[i], LOW);
  }
  
  // All blink
  for (int j = 0; j < 3; j++) {
    allLEDs(HIGH);
    delay(200);
    allLEDs(LOW);
    delay(200);
  }
}

// ===== MODE 1: REACTION TIMER =====
void reactionMode() {
  // Random delay before LED lights up
  delay(random(1000, 3000));
  
  // Pick random LED
  int targetLED = random(0, NUM_LEDS);
  
  // Light it up and start timer
  digitalWrite(LED_PINS[targetLED], HIGH);
  unsigned long startTime = millis();
  
  // Wait for correct button press
  bool buttonPressed = false;
  while (!buttonPressed) {
    if (digitalRead(BUTTON_PINS[targetLED]) == HIGH) {
      buttonPressed = true;
      reactionTime = millis() - startTime;
      
      // Turn off LED
      digitalWrite(LED_PINS[targetLED], LOW);
      
      // Display result
      Serial.print("Reaction time: ");
      Serial.print(reactionTime);
      Serial.println(" ms");
      
      // Feedback
      if (reactionTime < 200) {
        Serial.println("AMAZING! 🚀");
      } else if (reactionTime < 400) {
        Serial.println("Great! 😎");
      } else if (reactionTime < 600) {
        Serial.println("Good! 👍");
      } else {
        Serial.println("Keep trying! 💪");
      }
      
      // Check for best time
      if (reactionTime < bestTime) {
        bestTime = reactionTime;
        Serial.print("NEW BEST TIME: ");
        Serial.print(bestTime);
        Serial.println(" ms!");
      }
      
      Serial.println();
      delay(1000);
    }
    
    // Check if wrong button pressed
    for (int i = 0; i < NUM_LEDS; i++) {
      if (i != targetLED && digitalRead(BUTTON_PINS[i]) == HIGH) {
        Serial.println("Wrong button! Try again.");
        digitalWrite(LED_PINS[targetLED], LOW);
        delay(500);
        digitalWrite(LED_PINS[targetLED], HIGH);
        delay(100);
      }
    }
  }
}

// ===== MODE 2: MEMORY GAME (SIMON-SAYS) =====
void memoryMode() {
  Serial.println("=== MEMORY GAME ===");
  Serial.println("Watch and repeat the pattern!\n");
  
  currentRound = 1;
  sequenceLength = 0;
  
  while (true) {
    Serial.print("Round ");
    Serial.println(currentRound);
    
    // Add new LED to sequence
    sequence[sequenceLength] = random(0, NUM_LEDS);
    sequenceLength++;
    
    // Show sequence
    delay(1000);
    showSequence();
    
    // Wait for player input
    Serial.println("Your turn!");
    if (!checkPlayerInput()) {
      // Game over
      Serial.println("\n❌ WRONG! Game Over!");
      Serial.print("Final Score: ");
      Serial.print(currentRound - 1);
      Serial.println(" rounds");
      
      // Game over animation
      gameOverAnimation();
      
      delay(3000);
      Serial.println("\nRestarting...\n");
      return;  // Restart game
    }
    
    // Success!
    Serial.println("✅ Correct!\n");
    successAnimation();
    currentRound++;
    delay(1500);
  }
}

// ===== SHOW LED SEQUENCE =====
void showSequence() {
  int delayTime = 500;
  
  // Speed up after round 4
  if (currentRound > 4) delayTime = 300;
  if (currentRound > 7) delayTime = 200;
  
  for (int i = 0; i < sequenceLength; i++) {
    digitalWrite(LED_PINS[sequence[i]], HIGH);
    delay(delayTime);
    digitalWrite(LED_PINS[sequence[i]], LOW);
    delay(200);
  }
}

// ===== CHECK PLAYER INPUT =====
bool checkPlayerInput() {
  for (int i = 0; i < sequenceLength; i++) {
    // Wait for button press
    bool buttonPressed = false;
    while (!buttonPressed) {
      for (int j = 0; j < NUM_LEDS; j++) {
        if (digitalRead(BUTTON_PINS[j]) == HIGH) {
          // Button pressed - light up LED
          digitalWrite(LED_PINS[j], HIGH);
          delay(300);
          digitalWrite(LED_PINS[j], LOW);
          
          // Check if correct
          if (j != sequence[i]) {
            return false;  // Wrong button!
          }
          
          buttonPressed = true;
          
          // Debounce
          while (digitalRead(BUTTON_PINS[j]) == HIGH) {
            delay(10);
          }
          delay(100);
          break;
        }
      }
    }
  }
  return true;  // All correct!
}

// ===== ANIMATIONS =====
void successAnimation() {
  for (int i = 0; i < 2; i++) {
    allLEDs(HIGH);
    delay(100);
    allLEDs(LOW);
    delay(100);
  }
}

void gameOverAnimation() {
  for (int i = 0; i < 3; i++) {
    allLEDs(HIGH);
    delay(200);
    allLEDs(LOW);
    delay(200);
  }
}

void allLEDs(int state) {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], state);
  }
}

// ===== TRY THIS =====
// 1. Add Mode 3: Speed Round (as many correct presses in 30 seconds)
// 2. Add difficulty selector at startup
// 3. Save high scores to EEPROM
// 4. Add multiplayer mode (2 players alternate)
// 5. Add sound effects using a buzzer
