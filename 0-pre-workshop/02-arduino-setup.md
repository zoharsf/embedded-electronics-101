# 🛠️ Arduino Web IDE Setup (10 minutes)

Get your development environment ready. This is the software you'll use to write and upload code.

## 🎬 Video: What Is Arduino Cloud? (2 min)

**Watch this first:** [What Is Arduino Cloud?](https://youtu.be/27S-XI_zHQc?si=LQLqwQ3bwIbajM_U) by Arduino

**What you'll learn:**
- What is Arduino cloud
- Templates
- Abilities

⏱️ **2 minutes.**

After watching, come back and follow the step-by-step guide below.

## Step 1: Create Arduino Account (2 min)

1. Go to **[https://create.arduino.cc/](https://create.arduino.cc/)**
2. Click **"Sign Up"** (or "Log In" if you already have an account)
3. Enter your email and create a password
4. **Verify your email** (check your inbox and spam folder)

✅ Done! You now have an Arduino account.

## Step 2: Install ESP32 Board Support (5 min)

1. In Arduino Create, click **Preferences** (⚙️ icon, top right)
2. Find "Additional Boards Manager URLs" field
3. **Paste this entire link:**
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Click **Save**
5. Go to **Boards Manager** (left sidebar, second icon)
6. Search for **"ESP32"**
7. Find **"esp32 by Espressif Systems"**
8. Click **Install**
9. Wait 1-2 minutes for download
10. When done, you should see "INSTALLED" next to it

✅ Done! ESP32 is now ready to use.

---

## Step 3: Select Your Board (1 min)

1. Click **"Select Board"** (top left)
2. Search for **"ESP32"**
3. Choose **"ESP32 Dev Module"**
4. Close the popup

✅ Done! Board is selected.

---

## Step 4: Quick Test (Optional, 2 min)

1. Go to **File → Examples → 01.Basics → Blink**
2. You should see code appear
3. Click **Verify** (✓ checkmark icon, top left)
4. Look at the bottom—should say "Compilation successful" ✅

✅ Everything works! You're ready for Workshop 1.

---

## Troubleshooting

**"Board not found" error?**
- Restart Arduino Create
- Try Steps 1-3 again

**"Failed to get board info" error?**
- Check your internet connection
- Try again in a few minutes

**Still stuck?**
- Check [Troubleshooting Master](../resources/troubleshooting-master.md)
- Open an [Issue](https://github.com/zoharsf/embedded-electronics-101/issues)

---

**Next →** [Homework Checklist](./homework-checklist.md)

