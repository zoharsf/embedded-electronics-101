# 🎮 Project 3: Button Game

## What You'll Build

An interactive reaction-time game or Simon-Says memory game using LEDs and buttons!

**Two game modes:**
1. **Reaction Timer:** How fast can you press the button when the LED lights up?
2. **Memory Game:** Repeat the LED pattern that the game shows you

---

## Hardware Setup

### Components Needed
- 4x LEDs (different colors recommended)
- 4x 220Ω resistors
- 4x Push buttons
- Jumper wires

### Circuit Connections

| Component | ESP32 Pin | Notes |
|-----------|-----------|-------|
| LED 1 (Red) | GPIO 2 | Via 220Ω resistor |
| LED 2 (Green) | GPIO 4 | Via 220Ω resistor |
| LED 3 (Blue) | GPIO 5 | Via 220Ω resistor |
| LED 4 (Yellow) | GPIO 12 | Via 220Ω resistor |
| Button 1 | GPIO 18 | With internal pull-down |
| Button 2 | GPIO 19 | With internal pull-down |
| Button 3 | GPIO 21 | With internal pull-down |
| Button 4 | GPIO 22 | With internal pull-down |
| All components GND | GND | Common ground |

### Breadboard Layout

```
ESP32                    Components
┌────┐                   
│GPIO2 ├──[220Ω]──[LED1 +]───┐
│GPIO4 ├──[220Ω]──[LED2 +]───┤
│GPIO5 ├──[220Ω]──[LED3 +]───┼──→ All to GND
│GPIO12├──[220Ω]──[LED4 +]───┘
│      │
│GPIO18├──[BTN1]──→ GND
│GPIO19├──[BTN2]──→ GND
│GPIO21├──[BTN3]──→ GND
│GPIO22├──[BTN4]──→ GND
└────┘
```

---

## The Code

See [code-button-game.ino](code-button-game.ino) for complete sketch.

---

## Step-by-Step Build

### Step 1: Build LED Array (10 min)

1. Insert 4 LEDs into breadboard in a row
2. Connect resistors to each LED positive leg
3. Wire resistors to ESP32: GPIO 2, 4, 5, 12
4. Connect all LED negative legs to GND

**Test:** Upload code, all LEDs should light up in sequence during startup!

### Step 2: Add Button Array (10 min)

1. Insert 4 buttons below each corresponding LED
2. Wire buttons to ESP32: GPIO 18, 19, 21, 22
3. Connect other side of all buttons to GND

**Test:** Press buttons, corresponding LED should light up!

---

## Game Modes

### Mode 1: Reaction Timer

**How it works:**
1. Wait for a random LED to light up
2. Press the matching button as FAST as possible
3. See your reaction time in milliseconds
4. Try to beat your best score!

**Scoring:**
- Under 200ms: "AMAZING! 🚀"
- 200-400ms: "Great! 😎"
- 400-600ms: "Good! 👍"
- Over 600ms: "Keep trying! 💪"

### Mode 2: Memory Game (Simon-Says)

**How it works:**
1. Watch the LED sequence (starts with 1 LED)
2. Repeat the sequence by pressing buttons
3. Each round adds one more LED to the sequence
4. Wrong button = game over!

**Difficulty levels:**
- Round 1-3: Easy (slow speed)
- Round 4-6: Medium (faster)
- Round 7+: Hard (very fast!)

---

## How to Play

1. **Upload the code**
2. **Open Serial Monitor** (shows instructions and scores)
3. **Game starts automatically** in Reaction Timer mode
4. **Press Button 4 during game over** to switch to Memory mode
5. **Have fun!**

---

## Experiments to Try

### Beginner
- Change LED blink speed
- Change color assignments
- Add victory sound (if you have a buzzer)

### Intermediate
- Add difficulty levels (user selects at start)
- Track high scores across rounds
- Add 2-player competitive mode

### Advanced
- Save high scores to EEPROM (persists after power off)
- Add LCD display for scores
- Create a "sudden death" mode (one mistake = game over)
- Add WiFi leaderboard

---

## Code Walkthrough

### Key Functions

```cpp
void reactionMode()     // Reaction timer game logic
void memoryMode()       // Simon-says game logic
void showSequence()     // Display LED pattern
bool checkInput()       // Verify button presses
void gameOver()         // End game and show score
```

### Understanding Timing

```cpp
unsigned long startTime = millis();  // Start timer
unsigned long endTime = millis();    // End timer
int reactionTime = endTime - startTime;  // Calculate difference
```

---

## Troubleshooting

### LEDs light up in wrong order
- Check pin assignments in code
- Verify wiring matches the pin definitions

### Buttons don't respond
- Check `INPUT_PULLDOWN` is set
- Test buttons individually using Serial Monitor debug messages
- Ensure buttons are across center divide of breadboard

### Game doesn't start
- Open Serial Monitor (might be waiting for serial connection)
- Check baud rate is 9600
- Press reset button on ESP32

### Memory game is too hard/easy
- Adjust `delayTime` variable in code
- Change the number of rounds before speed increases

---

## Take It Further

**Ideas for home:**
- Build an enclosure (3D print or cardboard)
- Add LCD screen for better score display
- Create multiplayer mode (pass the board)
- Add different game modes (whack-a-mole, speed round)
- Make it portable with battery pack

---

**Questions?** Check [Resources](../../resources/) or open an [Issue](https://github.com/zoharsf/embedded-electronics-101/issues)!
