# 🚨 IoT Fall Detector Device

An embedded IoT system designed to detect human falls in real-time using an IMU (Inertial Measurement Unit) sensor and an optimized detection algorithm. The system minimizes false positives by processing multi-axis accelerometer data, triggering an immediate alert response upon fall verification.

This project demonstrates proficiency in **real-time data acquisition, digital signal filtering, and low-power embedded design.**

---

## ⚡ System Architecture & Detection Logic

The device utilizes a **three-stage threshold algorithm** to differentiate an actual fall from normal daily activities (like sitting down quickly or jumping).

1. **Free Fall Detection:** Monitors the Accelerometer Vector Magnitude. A sudden drop near 0G indicates a free-fall state.
2. **Impact Detection:** A massive spike in G-force (typically > 3G) registers the impact with the ground.
3. **Inactivity Monitoring:** If the user remains motionless for a calibrated window (e.g., 5 seconds) after the impact, a fall is confirmed.

---

## 🚀 Key Engineering Features Demonstrated

* **Sensor Fusion:** Implements basic filtering to smooth out raw sensor noise and prevent false alarms.
* **Protocol Implementation:** Handles hardware communication over the I2C bus.
* **Low-Power Optimization:** Uses hardware interrupts to wake the microcontroller from sleep mode *only* when a high-G event occurs.
* **Non-Blocking Architecture:** Avoids the use of `delay()`, ensuring the microcontroller remains responsive to immediate button overrides.

---

## 💻 Tech Stack & Hardware Concepts

* **Languages:** C / C++ (Embedded)
* **Hardware Interfacing:** I2C communication, GPIO, External Interrupts.
* **Target Hardware Components:** MPU6050 (Accelerometer), Arduino/ESP32, Buzzer/LED indicators.
