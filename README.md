# ElectraSense

[![Stars](https://img.shields.io/github/stars/harshakvp/ElectraSense?style=flat-square&label=Stars)](https://github.com/harshakvp/ElectraSense/stargazers)
[![Forks](https://img.shields.io/github/forks/harshakvp/ElectraSense?style=flat-square&label=Forks)](https://github.com/harshakvp/ElectraSense/network/members)
[![Watchers](https://img.shields.io/github/watchers/harshakvp/ElectraSense?style=flat-square&label=Watchers)](https://github.com/harshakvp/ElectraSense/watchers)
[![Contributors](https://img.shields.io/github/contributors/harshakvp/ElectraSense?style=flat-square&label=Contributors)](https://github.com/harshakvp/ElectraSense/graphs/contributors)
![Last Commit](https://img.shields.io/github/last-commit/harshakvp/ElectraSense?style=flat-square&label=Last%20Commit)
![Repo Size](https://img.shields.io/github/repo-size/harshakvp/ElectraSense?style=flat-square&label=Repo%20Size)
![Visitors](https://visitor-badge.laobi.icu/badge?page_id=harshakvp.ElectraSense)

### ESP32-Based Single-Phase Electrical Parameter Monitoring System

A low-cost embedded electrical parameter monitoring system designed for real-time monitoring of single-phase AC loads. The system measures voltage and current, digitally computes electrical parameters such as active power, apparent power, reactive power, power factor, and energy, while providing **local display**, **CSV data logging**, and **wireless monitoring through a mobile dashboard**.

---

## Final Hardware Prototype

<p align="center">
  <img src="https://github.com/harshakvp/ElectraSense/blob/4ba940f4cd0535999c348c3f413413b537562d21/Figures/ElectraSense.png">
</p>

---

## Features

* Real-time voltage and current measurement
* Digital computation of:

  * RMS Voltage
  * RMS Current
  * Active Power
  * Apparent Power
  * Reactive Power
  * Power Factor
  * Energy Consumption
* 16×2 LCD real-time display
* User-controlled CSV logging to Micro SD card
* Wi-Fi based mobile dashboard monitoring
* Push-button user interface
* Status LED indications
* Compact plug-and-socket form factor
* Future-ready architecture for relay-based appliance control

---

## System Architecture

<p align="center">
  <img src="https://github.com/harshakvp/ElectraSense/blob/207b9e60bdb26d97e3e4c87cfee03c23c833002d/Figures/System%20Architecture.png">
</p>

The system consists of three primary functional blocks:

* **Sensing Unit**

  * ZMPT101B Voltage Sensor
  * ACS712 Current Sensor

* **Processing Unit**

  * ESP32 Microcontroller
  * Signal acquisition
  * Electrical parameter computation

* **Output & User Interface**

  * 16×2 LCD Display
  * Micro SD Card Logging
  * Wi-Fi Dashboard
  * Push Buttons
  * Status LEDs

---

## Circuit Diagram

<p align="center">
  <img src="https://github.com/harshakvp/ElectraSense/blob/207b9e60bdb26d97e3e4c87cfee03c23c833002d/Figures/Schematic%20Diagram.png">
</p>

The hardware consists of an ESP32 microcontroller interfaced with a ZMPT101B voltage sensor, ACS712 current sensor, 16×2 I²C LCD display, Micro SD card module, push buttons, and status LEDs. The analog outputs of the sensing modules are sampled using the ESP32 ADC, while SPI and I²C interfaces are used for peripheral communication.

---

## Hardware Components

| Component | Purpose |
|-----------|---------|
| ESP32 DevKit | Main processing unit |
| ZMPT101B | AC voltage sensing |
| ACS712 | AC current sensing |
| 16×2 LCD (I²C) | Local parameter display |
| Micro SD Card Module | CSV data logging |
| Push Buttons | Navigation and logging control |
| LEDs | Power and logging indication |

---

## Working Principle

1. The voltage and current sensors continuously acquire the AC voltage and current waveforms.
2. The ESP32 samples the analog signals using its ADC.
3. The firmware computes:

   * RMS Voltage
   * RMS Current
   * Active Power
   * Apparent Power
   * Reactive Power
   * Power Factor
   * Energy Consumption

4. The computed parameters are:

   * Displayed on the LCD
   * Logged to a Micro SD card in CSV format
   * Transmitted wirelessly to a mobile dashboard

5. The process repeats continuously to provide real-time monitoring.

---

## Experimental Validation

The developed prototype was experimentally validated using a **5 A step-adjustable resistive load bank**.

Reference instruments used:

* Digital Multimeter (Voltage)
* Digital Clamp Meter (Current)

Measured performance:

| Parameter | Percentage Error |
|-----------|-----------------:|
| Voltage | **1.7104 %** |
| Current | **2.0952 %** |

The obtained results demonstrate acceptable accuracy for educational, laboratory, and low-cost electrical monitoring applications.

---

## Future Improvements

* Relay-based appliance ON/OFF control
* Threshold-based load management
* Cloud data storage
* Historical data visualization
* Over-the-Air (OTA) firmware updates
* Three-phase electrical monitoring
* Enhanced sensor calibration
* Power quality analysis

---

## Repository Structure

```text
ElectraSense/
│
├── Figures/
│   ├── Prototype.png
│   ├── Circuit Diagram.png
│   └── ElectraSense.png
│
├── Firmware/
│   └── ESP32 Firmware.ino
│
└── README.md
```

---

## Tools Used

* Arduino IDE
* ESP32 Arduino Framework
* Embedded C++
* Git
* GitHub

---

## Author

### Harshak V P

Electrical and Electronics Engineering Undergraduate  
Vellore Institute of Technology (VIT), Vellore

#### Areas of Interest

* Embedded Systems
* Power Electronics
* Electric Drives
* PCB Design
* Internet of Things (IoT)
* Machine Learning Applications in Engineering

#### Connect

* **GitHub:** [harshakvp](https://github.com/harshakvp)
* **LinkedIn:** [Harshak V P](https://www.linkedin.com/in/harshakvp/)
* **Portfolio:** [harshakvp.dev](https://chain-science-5eb.notion.site/HARSHAK-V-P-4f4889ae8ebf4c05a5790637c39213ba)
* **Email:** [harshakvp.contact@gmail.com](mailto:harshakvp.contact@gmail.com)

Feel free to open an issue, suggest improvements, or reach out if you have any questions or feedback regarding this project.

---

This repository is maintained as part of my learning journey in embedded systems, electrical instrumentation, IoT, and hardware development. Feel free to explore the project, review the implementation, and use it as a reference for similar embedded monitoring applications.
