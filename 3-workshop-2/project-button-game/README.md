# Project 3: Button Game

## What You'll Build

An interactive reaction-time game and a Simon-Says memory game using LEDs and buttons.

**Two game modes:**
1. **Reaction Timer** - how fast can you press the button when its LED lights up?
2. **Memory Game** - repeat the LED pattern that the game shows you, getting longer each round.

The whole thing runs on the ESP32 with output in the Serial Monitor for scores and prompts.

---

## Hardware Setup

### Components Needed (all in your kit)
- 3x LEDs (use red, green, blue)
- 3x 220Ω resistors
- 3x Push buttons
- Jumper wires

### Circuit Connections

| Component | ESP32 Pin | Notes |
|-----------|-----------|-------|
| LED 1 (Red)   | GPIO 2 | Via 220Ω resistor to GND |
| LED 2 (Green) | GPIO 4 | Via 220Ω resistor to GND |
| LED 3 (Blue)  | GPIO 5 | Via 220Ω resistor to GND |
| Button 1 | GPIO 18 | Other side to 3.3V, uses internal pull-down |
| Button 2 | GPIO 19 | Other side to 3.3V, uses internal pull-down |
| Button 3 | GPIO 21 | Other side to 3.3V, uses internal pull-down |

The "red" button (GPIO 18) doubles as a mode-switch button between rounds (see "How to Play").

### Breadboard Layout

```
ESP32                    Components
┌────┐
│GPIO2 ├──[220Ω]──[Red LED +]───┐
│GPIO4 ├──[220Ω]──[Grn LED +]───┼──→ All LED – legs to GND
│GPIO5 ├──[220Ω]──[Blu LED +]───┘
│      │
│GPIO18├──[BTN1]──→ 3.3V
│GPIO19├──[BTN2]──→ 3.3V
│GPIO21├──[BTN3]──→ 3.3V
└────┘
```

Place each button directly under its matching LED so the player can map button-to-LED at a glance.

---

## The Code

See [code-button-game.ino](code-button-game.ino) for the complete sketch.

---

## Step-by-Step Build

### Step 1: Build the LED row (8 min)
1. Insert the 3 LEDs in a row on the breadboard.
2. Connect a 220Ω resistor from each LED's long leg to ESP32 GPIO 2, 4, and 5.
3. Connect each LED's short leg to the GND rail.

**Self-test:** upload the sketch. During startup all three LEDs should chase, then flash three times together.

### Step 2: Add the buttons (8 min)
1. Insert 3 buttons below the LEDs, each spanning the breadboard center divide.
2. Wire one side of each button to the 3.3V rail.
3. Wire the other side to GPIO 18, 19, 21.

**Self-test:** after the startup animation, press a button - the matching LED should already be lit and counting your reaction time.

---

## Game Modes

### Mode 1: Reaction Timer (default)
1. Wait for a random LED to light up.
2. Press the matching button as fast as possible.
3. Your reaction time prints to the Serial Monitor in milliseconds.
4. New best times are tracked across rounds.

**Scoring:**
- under 200 ms - "AMAZING!"
- 200-400 ms - "Great!"
- 400-600 ms - "Good!"
- over 600 ms - "Keep trying!"

### Mode 2: Memory Game (Simon-Says)
1. Watch the LED sequence (round 1 starts with one LED).
2. Press the buttons in the same order.
3. Each round adds another LED. Speed increases at rounds 5 and 8.
4. Wrong button = game over with your final score.

---

## How to Play

1. Upload the code.
2. Open Serial Monitor at 9600 baud.
3. The game starts in Reaction Timer mode automatically.
4. To switch modes: at any "round complete" or "game over" prompt, **hold the RED button** (GPIO 18) for 1 second.
5. Have fun.

---

## Experiments to Try

### Beginner
- Reassign LED colors by swapping the values in `LED_PINS[]`.
- Make the Reaction Timer give 5 attempts and print an average.
- Speed up the Memory Game faster (lower the `delayTime` floor).

### Intermediate
- Add a "Speed Round" mode: count correct presses in 30 seconds.
- Add a difficulty selector: at startup, read which button is held to choose easy/medium/hard.
- Display a running tally of (round, reaction_ms, mode) as CSV so you can paste it into a spreadsheet.

### Advanced
- Persist the best reaction time across reboots using `Preferences.h` (NVS-backed).
- Two-player alternating mode with separate scores per player.
- "Sudden death" mode: one mistake ends the entire session.
- Send scores over Serial in JSON for a future host-side leaderboard.

Each experiment has a clear acceptance criterion - if it does the thing, you're done. Show it to the facilitator and grab the next one.

---

## Troubleshooting

### LEDs light up but the wrong one when I press
- Verify pin assignments in code vs wiring. The button on GPIO 18 must be under the LED on GPIO 2, etc.
- Re-seat each LED's long leg into the resistor row.

### Buttons don't respond
- Confirm you wired the button between GPIO and **3.3V** (not GND). The code uses `INPUT_PULLDOWN`, which expects HIGH when pressed.
- Check the button straddles the breadboard's center divide (otherwise the legs are shorted).
- Press firmly - cheap tactile buttons sometimes need a real click.

### Game seems frozen
- Open Serial Monitor at 9600 baud (the game prints prompts there).
- Press the EN/RESET button on the ESP32 to restart.

### Memory game is too hard / too easy
- Adjust the `delayTime` thresholds inside `showSequence()`.

For anything else, see [the Workshop 2 troubleshooting tips](../README.md) or the [master troubleshooting guide](../../resources/troubleshooting-master.md).

---

## Take It Further (at home)

- Build a cardboard or 3D-printed enclosure with cutouts for buttons and LEDs.
- Add a small piezo buzzer for win/lose tones (no buzzer in the kit, but they're under $2).
- Multiplayer "pass the board" mode where players alternate turns.
- Whack-a-mole variant: a target LED moves randomly and you score for each hit within a window.

---

**Questions?** Open an [Issue](https://github.com/zoharsf/embedded-electronics-101/issues).
