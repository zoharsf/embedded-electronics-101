# Facilitator Guide

This file is for **you, the facilitator**. It is not in the participant-facing site nav. Treat it as a private cheat sheet for the day-of.

Audience profile this guide assumes:
- ~25 participants, mostly developers, mixed electronics experience.
- 3 workshops × 90 minutes, in person, you are solo.
- Fixed kit (see `KIT_CONTENTS.md`), no soldering.
- Phone hotspot model for Workshop 3 (each participant uses their own phone hotspot).

The math: with 25 people and a 90-minute slot, **you have ~3.6 minutes of attention per person**. The whole guide is structured around that constraint - getting people self-sufficient as fast as possible so your time goes to the genuinely stuck.

---

## One Week Before: Pre-Flight Checklist

- [ ] Send participants the [pre-workshop homework](0-pre-workshop/README.md) link.
- [ ] **Send a one-question poll:** "Do you have an Android phone you can bring on the day?" Tally responses.
  - If <80% answer yes, plan to drop the Bluetooth Controller from W3 (replace with a guided extension to one of the WiFi projects).
- [ ] **Test the full pipeline yourself on a clean corporate laptop** (borrow one if your daily driver is privileged):
  - Arduino Cloud + Arduino Create Agent install (does it ask for an admin password?).
  - Local Arduino IDE 2.x install (have this as a fallback).
  - Driver install for both CH340 and CP2102 (kit ships with either).
  - Upload a blink sketch to a board.
- [ ] **Pre-test your phone hotspot at 2.4 GHz** with one ESP32. Confirm the ESP32 connects within 30 seconds, gets an IP, serves a webpage you can open from the phone's browser. Note the typical IP range (`172.20.10.x` on iPhone, varies on Android).
- [ ] Build each workshop's circuits yourself, end-to-end. Don't skip this even if you've taught it before. Component substitutions and Arduino core updates break things silently.
- [ ] Prepare a printed or PDF cheat sheet (this file) on your phone for quick reference.

## Day-Of Materials Kit (your bag)

- A spare ESP32 dev board (in case one is DOA).
- Two spare USB-C cables (data-capable, tested).
- One CH340 driver installer + one CP2102 driver installer on a USB stick or in your Downloads folder.
- A laptop with the working setup, ready to swap in if a participant's laptop is hosed.
- A second phone with a hotspot, named something like `WORKSHOP_BACKUP`, password handy. If a participant's phone hotspot won't cooperate, they can join yours.
- Spare 220Ω and 10kΩ resistors, spare LEDs, spare buttons, spare DHT11. Cheap insurance.

---

## Common Day-Of Triage (Top 10)

These are roughly ranked by how often they'll come up. The fix on the right is what you say or do; the longer explanations are in [troubleshooting-master.md](resources/troubleshooting-master.md).

| Symptom | First move |
|---|---|
| "Port doesn't show up" | Swap the USB cable. If still nothing, swap to my laptop or check the driver. |
| "Failed to connect to ESP32" during upload | Hold BOOT button while upload starts. |
| "Board not selected" | Tools → Board → ESP32 Dev Module. |
| "Arduino Cloud isn't working" | Switch them to local Arduino IDE 2.x (have it pre-staged). |
| LED dim or doesn't light | LED reversed or resistor missing. |
| Button does nothing | Button wired to GND instead of 3.3V (we use INPUT_PULLDOWN). |
| Serial Monitor blank/garbage | Set baud to 9600. |
| W2: DHT shows NaN | DHT library not installed; data wire not on GPIO 5; reseat. |
| W3: WiFi never connects | Hotspot is 5 GHz - force 2.4 GHz (iPhone "Maximize Compatibility", Android band setting). |
| W3: iPhone hotspot keeps disconnecting | Keep the Personal Hotspot screen open until ESP32 is paired. |

---

## Group Strategy

You can't debug 25 people one at a time. Engineer the room so people help each other.

- **Seat in pods of 3-4.** Mix experience: at least one person who's clearly comfortable with code per pod.
- **Rule one:** "If your pod neighbor is stuck and you've finished the current step, help them before grabbing a stretch goal." Reinforce this verbally at the start.
- **Rule two:** "If you're stuck for more than 5 minutes, raise your hand and pair with a neighbor first. Flag me only if you and your pod can't figure it out."
- **Visible progress markers.** At each timing checkpoint, ask the room: "Hands up if your LED is blinking." Stragglers self-identify; you walk to them.
- **Recruit ad-hoc TAs.** When you spot someone who clearly knows what they're doing, ask them quietly to help their pod and the next pod over. Most developers say yes if asked directly.

---

## Workshop 1 - Cheat Sheet

**Goal:** every participant has uploaded a sketch, has an LED toggling on a button press, and has tried at least one stretch goal.

**Timing checkpoints:**

| Clock | Should be | If behind |
|---|---|---|
| 0:15 | Everyone has the IDE open and an ESP32 plugged in with a port detected. | Stop and triage as a group. Walk through driver/cable issues at the front of the room. Don't proceed until at least 80% are connected. |
| 0:30 | Most people have uploaded the LED blink sketch and seen it work. | Skip the long "how the code works" explanation. Move to wiring the button. |
| 0:55 | Button + LED working for ~70%. | Cut "experiments & variations" short. Send fast finishers to stretch goals (in `code-led-button.ino`). |
| 1:15 | Demo round: anyone show a working stretch goal? | If only blinks, that's fine. The point is everyone has *something* working. |
| 1:30 | Wrap. | - |

**Expected serial output (LED blink):**
```
LED Blink starting...
LED ON
LED OFF
LED ON
...
```

**Expected serial output (LED + button), idle:**
```
=== LED + Button Circuit ===
Press the button to control the LED!
Button released - LED OFF
Button released - LED OFF
```
On press: lines flip to `Button pressed - LED ON`.

**The 3 questions you'll get most:**

1. *"Why doesn't the LED light up?"* - 90% of the time it's polarity. Ask them to flip it. If still dark, check the resistor is in series, not parallel.
2. *"My port disappears when I unplug and replug."* - The ESP32 sometimes appears as a different port name. Re-select Tools → Port. If still nothing, swap the cable.
3. *"What does `INPUT_PULLDOWN` actually do?"* - "It's a weak resistor inside the chip pulling the pin to GND so it reads LOW when nothing is connected. The button overrides it by connecting to 3.3V when pressed." Then move on.

**Skip-logic if you're behind:**
- The "experiments & variations" 1:00-1:15 block is the easiest to compress. Stretch goals are now in the sketch and README, so participants find them themselves later.
- The "Q&A & wrap-up" 1:15-1:30 block can shrink to 5 minutes if needed.

**Do NOT skip:** the live circuit build (rows 0:10-0:45). If you skip building, you have lost the workshop.

---

## Inter-Workshop 1 - What to Push After W1

In a follow-up message:
- Link to [2-inter-workshop/README.md](2-inter-workshop/README.md).
- Remind them: **install the DHT library** before W2 (Library Manager → search "DHT sensor library" by Adafruit). This is the most common W2 blocker.
- Ask them to **pick their W2 project** in advance. Send them to [project-picker.md](2-inter-workshop/project-picker.md).
- For Data Dashboard pickers: install Python 3 and `pip install pyserial matplotlib pandas`. Most of your devs already have Python; for the rest, point at python.org.

---

## Workshop 2 - Cheat Sheet

**Goal:** every participant has built one of the four projects end-to-end.

The four W2 projects each have unique gotchas:

### Sensor Logger (easiest, Difficulty ⭐)
- DHT library installed? (Library Manager → "DHT sensor library" by Adafruit)
- DHT data on GPIO 5? Power 3.3V (not 5V).
- "NaN" on first reading is normal - DHT11 needs ~2 seconds to wake up.

### LED Light Show (medium, Difficulty ⭐⭐)
- Code now uses LEDC PWM API (`ledcAttach` / `ledcWrite`). Requires ESP32 Arduino core 2.x or 3.x. If a participant has core 1.x, the breathing pattern won't compile.
- Fix: Boards Manager → update "esp32 by Espressif Systems".
- Patterns 1, 2, 4, 5 use the same ledcWrite API now (255=on, 0=off) - this is by design, not a bug.

### Button Game (medium, Difficulty ⭐⭐) - rewritten to 3 buttons
- The kit has 3 buttons. The current sketch matches.
- "Hold the red button" is the mode-switch mechanism between Reaction and Memory modes.
- Buttons go to **3.3V** (not GND), uses INPUT_PULLDOWN.

### Data Dashboard (hardest, Difficulty ⭐⭐⭐)
- Python install issues will eat 5-10 min/person who doesn't have Python set up.
- The dashboard.py auto-detects the serial port. If detection fails, set `SERIAL_PORT` at the top of the file manually.
- **Critical:** the Arduino IDE Serial Monitor must be **closed** before running dashboard.py - it holds the port exclusively.

**Timing checkpoints:**

| Clock | Should be | If behind |
|---|---|---|
| 0:15 | Pods chosen, projects assigned, code starting to be read/uploaded. | Skip the recap, get hands on hardware. |
| 0:45 | Most circuits wired, first serial output seen. | Cut the "demo & debugging" block to 8 minutes. |
| 1:10 | Most projects basically working. Stretch goals starting. | Skip stretch announcements; let pods self-direct. |
| 1:25 | Demo lap. | - |

**Recurring questions:**
- *"My DHT shows NaN forever."* - Wire reseat + library check + power. 2-second wait. If still NaN, swap DHT11 from your spare bag.
- *"Python can't find the port."* - Close Arduino Serial Monitor. Then run `python3 -m serial.tools.list_ports -v` to confirm the OS sees the port at all.
- *"My LED Light Show won't compile - `ledcAttach` undefined."* - They're on an old ESP32 core. Update via Boards Manager.

---

## Inter-Workshop 2 - What to Push After W2

- Link to [4-inter-workshop/README.md](4-inter-workshop/README.md).
- Tell them W3 uses **their phone's hotspot**, not office or home WiFi. They don't need to wire anything up at home.
- Pre-W3 task: pick their W3 project. Bluetooth project requires Android.
- For iPhone users: read about "Maximize Compatibility" toggle in Personal Hotspot settings.

---

## Workshop 3 - Cheat Sheet

**Goal:** every participant connected over their own phone hotspot, ESP32 serving content, browser open on the phone.

**This is the hardest workshop to keep on schedule.** WiFi friction is the variable that determines whether you ship.

**Timing checkpoints:**

| Clock | Should be | If behind |
|---|---|---|
| 0:13 | Hotspots up. ESP32s starting to receive new sketches. | Front-of-room clinic for hotspot setup. Specifically: iPhone "Maximize Compatibility", Android 2.4 GHz band setting. |
| 0:30 | Circuits built. SSID/password pasted into sketches. | Pivot fast finishers to help neighbors with circuit wiring. |
| 0:50 | Most ESP32s have connected to a hotspot and printed their IP. | This is the danger zone. If lots are stuck on `Connecting to WiFi.....`, suspect 5 GHz hotspots. Walk the room and force-toggle the iPhone "Maximize Compatibility" setting. Have your backup hotspot named `WORKSHOP_BACKUP` ready. |
| 1:15 | Most have their dashboard open in their phone browser, customizing. | Skip stretch goals; close the workshop. |
| 1:28 | Wrap. | - |

**Expected serial output (WiFi project), success path:**
```
Connecting to WiFi....
Connected!
IP Address: 172.20.10.5
Open browser to: http://172.20.10.5
Web server started!
```

**Expected serial output, common stall:**
```
Connecting to WiFi.................
```
(dots forever) - hotspot is 5 GHz, or wrong password, or hotspot is asleep.

**Hotspot setup live walkthrough (read this aloud at 0:05):**

1. "Open your phone's settings. Find Personal Hotspot (iPhone) or Hotspot & tethering (Android)."
2. "Turn it on. Set or note the password."
3. "iPhone users: enable **Maximize Compatibility**. This forces 2.4 GHz - the ESP32 cannot connect to 5 GHz."
4. "Android users: set the band to **2.4 GHz**. Some phones default to 5 GHz."
5. "iPhone users: keep the Personal Hotspot screen open until your ESP32 is connected. The hotspot goes to sleep otherwise."
6. "Now copy your hotspot's name and password. We'll paste them into the sketch in a minute."

**Recurring questions:**
- *"It's stuck on 'Connecting to WiFi....'"* - 99% chance it's 5 GHz. Force 2.4 GHz.
- *"It connected but the page doesn't load."* - Use `http://` not `https://`. Confirm phone is on its own hotspot.
- *"I have an iPhone, can I do Bluetooth?"* - No. iOS doesn't support Bluetooth Classic Serial. Pivot to a WiFi project.

**The fallback path if hotspots are catastrophically failing:** turn on `WORKSHOP_BACKUP` and have everyone connect to that. Sketches need re-uploading with the backup SSID/password. This costs 10 minutes; it's the floor of how bad it can get.

---

## Wrap-up Routine (every workshop)

Last 2 minutes:

1. "What's one thing you learned today?" - one-word answers from the room.
2. Show the next homework link. Say: "Two things to do before next time: [X] and [Y]." Be that specific.
3. "Take your kit home. It's yours." (W1 only.)
4. Slack/email channel reminder for async questions.

---

## Self-Care Reminders

- You will not get to everyone. That's fine. The pod structure is supposed to absorb the long tail.
- A 75% success rate is good. 100% is not the goal.
- The participants who are quietly working are succeeding. The loud ones are not always the most stuck.
- Take a 10-second breath every checkpoint.

---

## Post-Workshop Tasks

- [ ] Push a "what to do next" message within 24 hours (the homework, the project picker, links).
- [ ] Note in this file what broke. The point is to keep the cheat sheet accurate for next time.
- [ ] If something cropped up that's missing here, add it. This is a living doc.
