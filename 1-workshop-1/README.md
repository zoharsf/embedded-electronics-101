# 🎯 Workshop 1: Basics & First Circuit (1.5 hours)

## 🎓 Learning Objectives

By the end of this workshop, you will:
- ✅ Understand how circuits work
- ✅ Build your first real circuit (LED + button)
- ✅ Write code to control hardware
- ✅ Troubleshoot when things don't work
- ✅ Know how to extend this to more complex projects

## 📋 What You'll Build

**A button-controlled LED circuit:**
- Push the button → LED lights up
- Release the button → LED turns off
- (Bonus) Hold button 2+ seconds → LED blinks

## 📅 Workshop Timeline

| Time | Activity | Duration |
|------|----------|----------|
| 0:00 | Welcome, safety, kit intro | 10 min |
| 0:10 | Build LED + button circuit (hands-on) | 35 min |
| 0:45 | Upload code & test | 15 min |
| 1:00 | Experiments & variations | 15 min |
| 1:15 | Q&A & wrap-up | 15 min |

## 🛠️ What You Get Today

Complete kit with everything you need:
- 1x ESP32 development board
- 1x Breadboard
- Jumper wires
- 1x LED (any color)
- 1x Push button
- 1x 220Ω resistor
- USB-C cable
- **Keep this kit!** You'll use it in Workshop 2 and beyond

## 📚 Materials for Today

- [Circuit Diagram & How to Build](./circuit-diagram.md)
- [Code: Basic LED Blink](./code-led-blink.ino) (warm-up)
- [Code: LED + Button (main project)](./code-led-button.ino)
- [Troubleshooting Guide](./troubleshooting.md)

## 🚀 Stretch Goals (if you finish early)

If your circuit is working before the experiments block ends, pick one of these from inside `code-led-button.ino`:

1. **Toggle-on-press** - one press = LED on, next press = LED off. (Detect the rising edge.)
2. **Non-blocking blink** - the LED blinks at 2 Hz when idle, stays solid while button is held. No `delay()` allowed.
3. **Press-duration brightness** - the longer you hold the button, the brighter the LED (uses LEDC PWM).
4. **Debounce counter** - print a clean integer per physical press. Ten presses must print 1..10 exactly.

Each one has an acceptance criterion at the bottom of the sketch. If your code does the thing, you're done - move to the next.

## 🚨 If Something Doesn't Work

**First: Check the troubleshooting guide**
→ [Workshop 1 Troubleshooting](./troubleshooting.md)

**Still stuck?**
→ Open an [Issue](https://github.com/zoharsf/embedded-electronics-101/issues) with:
- What you tried
- What error you got
- A photo of your circuit (if possible)

## 🎯 After Workshop 1

You'll get **inter-workshop homework** to:
- Learn about sensors (DHT11, light sensor)
- Pick which project you want to build in Workshop 2

**Start here when you get it:**
→ [Inter-Workshop Homework](../2-inter-workshop/README.md)

---

**Questions before the workshop?** Check [Troubleshooting](./troubleshooting.md)

**Ready to learn?** Let's build something! 🚀

---

**Previous:** [Pre-Workshop Homework](../0-pre-workshop/README.md) | **Next:** [Inter-Workshop Homework](../2-inter-workshop/README.md)

