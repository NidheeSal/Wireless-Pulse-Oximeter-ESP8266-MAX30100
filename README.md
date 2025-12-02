# Wireless Pulse Oximeter using ESP8266, MAX30100 & OLED Display

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform](https://img.shields.io/badge/Platform-ESP8266-blue)](#)
[![Sensor](https://img.shields.io/badge/Sensor-MAX30100-red)](#)

## Abstract
This project presents a low-cost, high-performance, wireless pulse oximeter and heart-rate monitoring device built around the ESP8266 Wi-Fi module, MAX30100 sensor, and a 0.96" OLED display.  
It continuously measures:
- **SpO₂** (Blood Oxygen Saturation in %)
- **BPM** (Heart Rate in beats per minute)  

The device is completely wireless, battery-powered, and displays real-time readings on the OLED screen. Data can also be sent to a phone, web dashboard, or IoT platform (Blynk, ThingSpeak, etc.) over Wi-Fi.

## Features
- Non-invasive SpO₂ and heart-rate measurement
- Real-time display on 128×64 OLED (SSD1306)
- Wi-Fi connectivity (ESP8266 NodeMCU / Wemos D1 Mini)
- Low power consumption & long battery life
- Open source – easy to modify and extend
- Optional: Push data to Blynk / ThingSpeak / MQTT

## Components Used
| Component          | Description                                                                 |
|--------------------|-----------------------------------------------------------------------------|
| ESP8266            | Wi-Fi enabled microcontroller (NodeMCU / Wemos D1 Mini)                     |
| MAX30100           | Integrated pulse oximeter and heart-rate sensor (I²C)                       |
| 0.96" OLED Display | 128×64 SSD1306 / SH1106 (I²C)                                               |
| Li-Po / Li-ion     | 3.7 V battery + TP4056 charging module (optional)                          |
| Resistors          | 4.7kΩ pull-ups for I²C (sometimes required)                                |
| Switch, wires, etc.| For power and enclosure                                                     |

## Circuit Diagram
![Circuit Diagram](https://github.com/johndoe/Wireless-Pulse-Oximeter-ESP8266-MAX30100/raw/main/images/circuit_diagram.png)
*(See `/circuit` folder for high-resolution image and Fritzing file)*

### Pin Connections
| MAX30100 / OLED | ESP8266 (NodeMCU) |
|-----------------|-------------------|
| VCC             | 3.3 V             |
| GND             | GND               |
| SDA             | D2 (GPIO-4)       |
| SCL             | D1 (GPIO-5)       |

> Note: Both MAX30100 and OLED share the same I²C bus (SDA → D2, SCL → D1).

## Arduino Code
Full code is provided in the `/src` folder.

**Libraries Required** (install via Library Manager):
- `MAX30100_PulseOximeter` by OXullo Intersec
- `Adafruit_GFX`
- `Adafruit_SSD1306`
- `ESP8266WiFi` (built-in)

```cpp
// Main file: Wireless_Pulse_Oximeter.ino
