---
hide:
  - navigation
  - toc
---

<div class="hero" markdown>

# Embedded Electronics 101

Three hands-on workshops. One ESP32 kit. From "I've never touched a wire" to a connected IoT dashboard you control from your phone.

<div class="hero-cta">
[:material-rocket-launch: Start with the pre-workshop](0-pre-workshop/){ .md-button .md-button--primary }
[:material-github: View on GitHub](https://github.com/zoharsf/embedded-electronics-101){ .md-button }
</div>

</div>

## How the series works

Each workshop is **1.5 hours** in person. Between workshops, light reading and a project pick (about **30-45 minutes** total) so we hit the ground running on the day.

<div class="workshop-grid" markdown>

<a class="workshop-card" href="0-pre-workshop/">
  <span class="step">Step 0</span>
  <h3>Pre-Workshop</h3>
  <p>Set up Arduino IDE, learn what voltage / current / resistance actually mean, and watch four short videos. ~30 min at home.</p>
</a>

<a class="workshop-card" href="1-workshop-1/">
  <span class="step">Workshop 1</span>
  <h3>First Circuit</h3>
  <p>LED + button on a breadboard. Code it. Make it interactive. By the end you'll have toggled, debounced, and PWM'd your way around a GPIO pin.</p>
</a>

<a class="workshop-card" href="2-inter-workshop/">
  <span class="step">Between 1 &amp; 2</span>
  <h3>Sensor Basics</h3>
  <p>Read about the DHT11 and the LDR, tweak some code samples, and pick which Workshop 2 project you want to build.</p>
</a>

<a class="workshop-card" href="3-workshop-2/">
  <span class="step">Workshop 2</span>
  <h3>Pick a Project</h3>
  <p>Sensor logger, LED light show, button game, or live data dashboard. You build one in 90 minutes.</p>
</a>

<a class="workshop-card" href="4-inter-workshop/">
  <span class="step">Between 2 &amp; 3</span>
  <h3>Going Wireless</h3>
  <p>Quick reading on WiFi, Bluetooth, and web servers. Pick your final project.</p>
</a>

<a class="workshop-card" href="5-workshop-3/">
  <span class="step">Workshop 3</span>
  <h3>Connected IoT</h3>
  <p>WiFi weather station, Bluetooth controller, or a full IoT dashboard - hosted right on your ESP32, accessed from your phone.</p>
</a>

</div>

## What you'll have at the end

A working connected ESP32 project that runs from your breadboard, talks over your phone's hotspot, and serves a webpage you can open from any device on the network. The kit is yours to keep - extend the project at home, or jump into any of the [25+ project ideas](resources/inspiration.md) using the same parts.

## What's in the kit

Everything is in [`KIT_CONTENTS.md`](https://github.com/zoharsf/embedded-electronics-101/blob/main/KIT_CONTENTS.md): an ESP32 dev board, breadboard, jumpers, 5 LEDs, 3 buttons, a DHT11 sensor, a light sensor, and the resistors you need. Around $25-30 of parts, no soldering, you take it home.

## Getting unstuck

- [Workshop 1 troubleshooting](1-workshop-1/troubleshooting.md) - LED, button, upload issues.
- [Workshop 3 troubleshooting](5-workshop-3/troubleshooting.md) - WiFi, hotspot, Bluetooth, web-server issues.
- [Master troubleshooting guide](resources/troubleshooting-master.md) - everything in one searchable place.
- [Glossary](resources/glossary.md) - every weird term in plain English.

---

**License:** MIT. Use it, fork it, run your own workshops with it.
