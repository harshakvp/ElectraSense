# ElectraSense - Embedded Single-Phase Electrical Parameter Monitoring System

[![Stars](https://img.shields.io/github/stars/harshakvp/ElectraSense?style=flat-square\&label=stars)](https://github.com/harshakvp/ElectraSense/stargazers)
[![Forks](https://img.shields.io/github/forks/harshakvp/ElectraSense?style=flat-square\&label=forks)](https://github.com/harshakvp/ElectraSense/forks)
[![Watchers](https://img.shields.io/github/watchers/harshakvp/ElectraSense?style=flat-square\&label=watchers)](https://github.com/harshakvp/ElectraSense/watchers)
[![Contributors](https://img.shields.io/github/contributors/harshakvp/ElectraSense?style=flat-square\&label=contributors)](https://github.com/harshakvp/ElectraSense/graphs/contributors)
![Last Commit](https://img.shields.io/github/last-commit/harshakvp/ElectraSense?style=flat-square\&label=last%20commit)
![Repo Size](https://img.shields.io/github/repo-size/harshakvp/ElectraSense?style=flat-square\&label=repo%20size)
![License](https://img.shields.io/badge/license-MIT-green?style=flat-square)
![Visitors](https://visitor-badge.laobi.icu/badge?page_id=harshakvp.ElectraSense)

A low-cost **ESP32-based embedded electrical parameter monitoring system** for real-time monitoring of **single-phase AC loads**. The system measures voltage and current, digitally computes electrical parameters such as active power, apparent power, reactive power, power factor, and energy, while providing **local display, SD card logging, and wireless mobile dashboard monitoring**.

This project was developed as part of my undergraduate research work in embedded systems and electrical instrumentation.

---

# Features

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

# System Overview

<p align="center">
  <img src="Documents/Figures/SystemArchitecture.png" alt="System Architecture" width="100%">
</p>

The system consists of three major functional blocks:

* **Sensing Unit**

  * ZMPT101B Voltage Sensor
  * ACS712 Current Sensor

* **Processing Unit**

  * ESP32 Microcontroller
  * Signal acquisition
  * Electrical parameter computation

* **Human Machine Interface**

  * 16×2 LCD Display
  * Push Buttons
  * Micro SD Card Logging
  * Wi-Fi Dashboard
  * Status LEDs

---

# Hardware

## Components Used

| Component              | Purpose                             |
| ---------------------- | ----------------------------------- |
| ESP32 DevKit           | Main processing unit                |
| ZMPT101B               | AC Voltage sensing                  |
| ACS712                 | AC Current sensing                  |
| 16×2 LCD (I2C)         | Local parameter display             |
| Micro SD Card Module   | CSV data logging                    |
| Push Buttons           | User navigation and logging control |
| LEDs                   | Power and logging indication        |
| Plug & Socket Assembly | Compact deployment                  |

---

# Working Principle

The system continuously samples the analog outputs of the voltage and current sensors using the ESP32's ADC.

From the acquired samples, the firmware computes:

* RMS Voltage
* RMS Current
* Active Power
* Apparent Power
* Reactive Power
* Power Factor
* Energy

The computed parameters are simultaneously:

* Displayed on the LCD
* Logged to a Micro SD card (CSV format)
* Transmitted to a mobile dashboard over Wi-Fi

---

# Repository Structure

```text
ElectraSense/
│
├── Firmware/
│   ├── ElectraSense.ino
│   └── Libraries/
│
├── Hardware/
│   ├── Circuit_Schematic/
│   ├── Wiring_Diagram/
│   └── Images/
│
├── Documents/
│   ├── Conference_Paper.pdf
│   ├── Figures/
│   └── Validation/
│
├── MobileDashboard/
│
├── Images/
│
└── README.md
```

---

# Validation

The prototype was experimentally validated using a **step-adjustable 5 A resistive load bank**.

Reference instruments used:

* Digital Multimeter (Voltage)
* Digital Clamp Meter (Current)

Experimental results showed:

* Voltage Error: **1.7104%**
* Current Error: **2.0952%**

indicating acceptable accuracy for low-cost educational and laboratory monitoring applications.

---

# Future Improvements

* Relay-based appliance ON/OFF control
* Threshold-based load management
* Cloud database integration
* Historical data visualization
* Remote firmware updates (OTA)
* Three-phase system support
* Improved sensor calibration
* Enhanced power quality analysis

---

# Tools Used

* Arduino IDE
* ESP32 Arduino Framework
* Embedded C++
* EasyEDA / KiCad (if applicable)
* Microsoft Excel
* Git
* GitHub

---

# Documentation

The repository includes:

* Firmware source code
* Circuit schematic
* Wiring diagram
* Hardware images
* Experimental validation setup
* CSV sample logs
* Conference paper
* System architecture figures

---

# Author

## Harshak V P

Electrical and Electronics Engineering Undergraduate
Vellore Institute of Technology (VIT), Vellore

### Connect

* GitHub: https://github.com/harshakvp
* LinkedIn: https://www.linkedin.com/in/harshakvp/
* Portfolio: https://harshakvp.dev
* Email: [harshakvp.contact@gmail.com](mailto:harshakvp.contact@gmail.com)

---

# Citation

If you use this project in your work, please consider citing the accompanying conference paper or linking to this repository.

---

## License

This project is intended for educational, research, and open-source hardware development purposes. Feel free to explore, modify, and build upon this work with appropriate attribution.
