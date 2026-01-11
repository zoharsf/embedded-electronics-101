# 💡 Your First Sketch: The Blink Program (Optional)

A "sketch" is Arduino code. Here's what "Hello World" looks like in Arduino.

## The Simplest Arduino Program

```cpp
void setup() {
  // Runs ONCE when board powers on
  pinMode(2, OUTPUT);  // Set pin 2 as output
}

void loop() {
  // Runs forever, over and over
  digitalWrite(2, HIGH);  // Pin 2 = ON
  delay(1000);            // Wait 1 second
  digitalWrite(2, LOW);   // Pin 2 = OFF
  delay(1000);            // Wait 1 second
}
```

## Breaking It Down

| Line | Means |
|------|-------|
| `void setup() { }` | Runs once at start |
| `pinMode(2, OUTPUT)` | Pin 2 will control something (output) |
| `void loop() { }` | Runs forever (main program) |
| `digitalWrite(2, HIGH)` | Turn pin 2 on (3.3V) |
| `delay(1000)` | Wait 1000 milliseconds (1 second) |
| `digitalWrite(2, LOW)` | Turn pin 2 off (0V) |

**Result:** Pin 2 turns on/off every second. If you had an LED on pin 2, it would blink!

## How to Test This

1. Open [Arduino Create](https://create.arduino.cc/)
2. Click **"Create → Sketch"**
3. Paste the code above into the editor
4. Click **"Verify"** (checkmark)
5. Should say "Compilation successful" ✅

**You don't need to upload this yet.** We'll do that with actual hardware in Workshop 1!

---

**Ready?** → [Homework Checklist](/0-pre-workshop/homework-checklist.md)

