# Arduino RGB Distance Radar

[![Watch the video](https://img.youtube.com/vi/YOUR_VIDEO_ID/0.jpg)](https://youtu.be/YOUR_VIDEO_LINK)

📺 **Watch the Full Build Video on YouTube**
https://youtu.be/YOUR_VIDEO_LINK

---

## Project Overview

This project demonstrates a smart and visually attractive **Arduino RGB Distance Radar** using an **Arduino UNO**, **HC-SR04 Ultrasonic Sensor**, **WS2812B Addressable RGB LED Strip**, and a **0.91" OLED Display**.

The system measures the distance of nearby objects in real-time using the ultrasonic sensor and displays the distance in millimeters on the OLED screen.

At the same time, the WS2812B RGB LED strip acts as a live visual distance indicator bar. As the measured distance changes, the LED strip dynamically changes both:

* Number of illuminated LEDs
* Distance warning color zones

The system uses three color zones:

* Green Zone → Safe Distance
* Yellow Zone → Medium Distance
* Red Zone → Close Distance Warning

This project is ideal for learning **Arduino programming, ultrasonic distance measurement, WS2812B LED control, OLED interfacing, and real-time sensor visualization systems**.

The full build process is available on the **AmithLabs YouTube channel**.

---

## Main Features

* Real-Time Distance Measurement
* OLED Live Distance Display
* WS2812B RGB LED Bar Indicator
* Green / Yellow / Red Distance Zones
* Smooth LED Distance Visualization
* Millimeter Distance Resolution
* Beginner Friendly Arduino Project
* Professional Looking Smart Sensor System

---

## Hardware Components

* Arduino UNO
* HC-SR04 Ultrasonic Sensor
* WS2812B 5V Addressable RGB LED Strip
* 0.91" OLED Display (I2C SSD1306)
* Jumper Wires
* Breadboard (Optional)
* 5V External Power Supply
* 330 Ohm Resistor (Recommended)
* 1000uF Capacitor (Recommended)

---

## Pin Configuration

| Component           | Arduino UNO Pin |
| ------------------- | ---------------- |
| OLED SDA            | A4               |
| OLED SCL            | A5               |
| HC-SR04 TRIG        | D9               |
| HC-SR04 ECHO        | D10              |
| WS2812B DIN         | D6               |
| OLED VCC            | 5V               |
| HC-SR04 VCC         | 5V               |
| WS2812B 5V          | External 5V      |
| All GND Connections | GND              |
---

## Schematic Diagram

![Schematic Diagram](Schematic%20Diagram.jpg)
---

## System Operation

1. Arduino powers ON and initializes all devices.
2. OLED display starts using I2C communication.
3. HC-SR04 ultrasonic sensor measures object distance.
4. Distance is calculated in millimeters.
5. OLED displays the live distance value.
6. WS2812B LED strip lights according to measured distance.
7. More distance = more LEDs illuminated.
8. LED color changes according to warning zones.
9. System continuously updates in real-time.

---

## Distance Zones

| Distance Range | LED Color |
| -------------- | ---------- |
| 260mm ~ 390mm  | Green      |
| 130mm ~ 260mm  | Yellow     |
| 0mm ~ 130mm    | Red        |

---

## LED Resolution

```text
24 LEDs across 390mm range
```

Distance Resolution:

```text
390mm / 24 LEDs = 16.25mm per LED
```

Example:

```text
162mm ≈ 10 LEDs ON
```

---

## Arduino Code

The complete Arduino program is included in this repository:

```text
Arduino_RGB_Distance_Radar.ino
```

This code controls:

* Ultrasonic Distance Measurement
* OLED Display Output
* WS2812B RGB LED Control
* Distance Zone Detection
* Real-Time LED Visualization

---

## Project Images

```text
Circuit Diagram.jpg
Project Build Photos.jpg
OLED Display Preview.jpg
```

---

## Required Libraries

Install the following libraries from Arduino IDE:

```text
FastLED
Adafruit SSD1306
Adafruit GFX Library
Wire
```

Library Path:

```text
Sketch → Include Library → Manage Libraries
```

Search and install:

```text
FastLED
Adafruit SSD1306
Adafruit GFX
```

---

## Distance Calculation Formula

```text
distanceMM = duration * 0.343 / 2
```

Where:

* `duration` = ultrasonic echo pulse time in microseconds
* `0.343` = speed of sound in mm/us
* `/2` = signal travels forward and back

---

## Important Notes

* Use an external 5V power supply for the WS2812B LED strip.
* Connect Arduino GND and LED power supply GND together.
* Recommended protection components:
  * 330 Ohm resistor on DATA line
  * 1000uF capacitor across 5V and GND

---

## YouTube Channel

This project was created for the **AmithLabs** YouTube channel.

Subscribe for more DIY electronics, Arduino projects, smart sensors, automation systems, and creative engineering builds.

---

## Disclaimer

This project is created for **educational and demonstration purposes only**.

Please use proper safety precautions when working with power supplies and electronic circuits.

For best performance, use stable 5V power and proper wiring connections.

---

## Author

**Amith Wijekoon**
Automation & Electrical Engineering Specialist
Creator of the **AmithLabs** YouTube Channel
