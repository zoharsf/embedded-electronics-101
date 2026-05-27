// =====================================
// Workshop 2: Button Reaction Game
// Test your reflexes and memory!
// =====================================
//
// Hardware: 3x LEDs + 3x 220 ohm resistors + 3x push buttons
// Pins: GPIO 2,4,5 -> LEDs (red, green, blue)
//       GPIO 18,19,21 -> buttons (matched to LEDs)
// Libraries: None (built-in only)

// ===== PIN DEFINITIONS =====
const int LED_PINS[]    = {2, 4, 5};      // Red, Green, Blue
const int BUTTON_PINS[] = {18, 19, 21};   // One per LED
const int NUM_LEDS = 3;

// Button 0 (GPIO 18) doubles as the "switch mode" button between rounds.

// ===== GAME VARIABLES =====
int gameMode = 1;                  // 1 = Reaction Timer, 2 = Memory Game
int sequence[64];                  // Memory game sequence storage
int sequenceLength = 0;
int currentRound = 1;
unsigned long reactionTime = 0;
unsigned long bestTime = 999999;

// ===== SETUP =====
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    pinMode(BUTTON_PINS[i], INPUT_PULLDOWN);
  }

  Serial.println("=== BUTTON GAME ===");
  startupAnimation();

  Serial.println("MODE 1: Reaction Timer");
  Serial.println("Press the button under the LED that lights up - as fast as you can!");
  Serial.println("Hold Button 1 (red) at any game-over to switch to Memory Mode.\n");
  delay(1500);
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
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], HIGH);
    delay(120);
    digitalWrite(LED_PINS[i], LOW);
  }
  for (int j = 0; j < 3; j++) {
    allLEDs(HIGH);
    delay(150);
    allLEDs(LOW);
    delay(150);
  }
}

// ===== MODE 1: REACTION TIMER =====
void reactionMode() {
  delay(random(1000, 3000));

  int targetLED = random(0, NUM_LEDS);
  digitalWrite(LED_PINS[targetLED], HIGH);
  unsigned long startTime = millis();

  while (true) {
    // Correct button
    if (digitalRead(BUTTON_PINS[targetLED]) == HIGH) {
      reactionTime = millis() - startTime;
      digitalWrite(LED_PINS[targetLED], LOW);

      Serial.print("Reaction time: ");
      Serial.print(reactionTime);
      Serial.println(" ms");

      if (reactionTime < 200)      Serial.println("AMAZING!");
      else if (reactionTime < 400) Serial.println("Great!");
      else if (reactionTime < 600) Serial.println("Good!");
      else                         Serial.println("Keep trying!");

      if (reactionTime < bestTime) {
        bestTime = reactionTime;
        Serial.print("NEW BEST TIME: ");
        Serial.print(bestTime);
        Serial.println(" ms");
      }
      Serial.println();

      // Offer mode switch on a long-hold of button 0
      if (waitForRelease(targetLED, 800)) {
        Serial.println("Switching to MEMORY MODE...\n");
        gameMode = 2;
      }
      delay(700);
      return;
    }

    // Wrong button
    for (int i = 0; i < NUM_LEDS; i++) {
      if (i != targetLED && digitalRead(BUTTON_PINS[i]) == HIGH) {
        Serial.println("Wrong button! Try again.");
        digitalWrite(LED_PINS[targetLED], LOW);
        delay(400);
        digitalWrite(LED_PINS[targetLED], HIGH);
        delay(80);
      }
    }
  }
}

// ===== MODE 2: MEMORY GAME (SIMON-SAYS) =====
void memoryMode() {
  Serial.println("=== MEMORY GAME ===");
  Serial.println("Watch the sequence, then press the buttons in order.\n");

  currentRound = 1;
  sequenceLength = 0;

  while (true) {
    Serial.print("Round ");
    Serial.println(currentRound);

    sequence[sequenceLength++] = random(0, NUM_LEDS);

    delay(800);
    showSequence();

    Serial.println("Your turn!");
    if (!checkPlayerInput()) {
      Serial.println("\nWRONG! Game Over.");
      Serial.print("Final Score: ");
      Serial.print(currentRound - 1);
      Serial.println(" rounds");

      gameOverAnimation();
      delay(2000);

      // Hold button 0 (red) during this window to flip back to Reaction Mode.
      Serial.println("Hold the RED button now to switch back to Reaction Mode...");
      unsigned long holdStart = millis();
      while (millis() - holdStart < 2000) {
        if (digitalRead(BUTTON_PINS[0]) == HIGH) {
          Serial.println("Switching to REACTION MODE...\n");
          gameMode = 1;
          return;
        }
      }
      Serial.println("Restarting Memory Mode...\n");
      return;
    }

    Serial.println("Correct!\n");
    successAnimation();
    currentRound++;
    delay(1200);
  }
}

void showSequence() {
  int delayTime = 500;
  if (currentRound > 4) delayTime = 350;
  if (currentRound > 7) delayTime = 220;

  for (int i = 0; i < sequenceLength; i++) {
    digitalWrite(LED_PINS[sequence[i]], HIGH);
    delay(delayTime);
    digitalWrite(LED_PINS[sequence[i]], LOW);
    delay(180);
  }
}

bool checkPlayerInput() {
  for (int i = 0; i < sequenceLength; i++) {
    while (true) {
      for (int j = 0; j < NUM_LEDS; j++) {
        if (digitalRead(BUTTON_PINS[j]) == HIGH) {
          digitalWrite(LED_PINS[j], HIGH);
          delay(250);
          digitalWrite(LED_PINS[j], LOW);

          if (j != sequence[i]) return false;

          // wait for release
          while (digitalRead(BUTTON_PINS[j]) == HIGH) delay(10);
          delay(80);
          goto next;
        }
      }
    }
    next: ;
  }
  return true;
}

// ===== HELPERS =====
void successAnimation() {
  for (int i = 0; i < 2; i++) {
    allLEDs(HIGH); delay(120);
    allLEDs(LOW);  delay(120);
  }
}

void gameOverAnimation() {
  for (int i = 0; i < 3; i++) {
    allLEDs(HIGH); delay(220);
    allLEDs(LOW);  delay(220);
  }
}

void allLEDs(int state) {
  for (int i = 0; i < NUM_LEDS; i++) digitalWrite(LED_PINS[i], state);
}

// Returns true if the given button was held for `holdMs` after pressing.
bool waitForRelease(int idx, unsigned long holdMs) {
  unsigned long pressedAt = millis();
  bool stillHeld = false;
  while (digitalRead(BUTTON_PINS[idx]) == HIGH) {
    if (millis() - pressedAt > holdMs) stillHeld = true;
    delay(10);
  }
  return stillHeld;
}

// ===== TRY THIS =====
// 1. Speed Round mode: count correct presses in 30 seconds.
// 2. Difficulty selector at startup (read which button is held during boot).
// 3. Persist best time across reboots using Preferences.h.
// 4. Two-player alternating mode with separate scores.
