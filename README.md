# Graduation-Project
SDV with ADAS
# 🚗 Integration of Software-Defined Vehicles (SDV) with Advanced Driver Assistance Systems (ADAS) for Next-Generation Automotive Applications

## 📌 Overview

This project presents a miniature **Software-Defined Vehicle (SDV)** prototype integrated with multiple **Advanced Driver Assistance Systems (ADAS)** features.
The goal was to bridge the gap between traditional academic ADAS prototypes and modern automotive SDV architectures by developing a **modular, scalable, and software-centric platform** capable of evolving with future automotive technologies.

The system combines **embedded systems**, **edge AI**, **real-time communication**, and **containerized software deployment** to simulate next-generation intelligent vehicle behavior.

---

# ✨ Features

## ✅ Advanced Driver Assistance Systems (ADAS)

### 🚨 Emergency Braking System (EBS)

Detects nearby obstacles and automatically triggers braking mechanisms to prevent collisions.

### 🔍 Blind Spot Detection (BSD)

Monitors blind spots using sensors and alerts the driver about nearby vehicles or objects.

### 🚦 Traffic Sign Recognition (TSR)

Uses a lightweight **YOLOv8n** deep learning model converted to **ONNX** format for efficient edge inference on the Raspberry Pi.

Supported traffic signs include:

* Stop
* Speed limits
* Traffic lights
* Warning signs

---

# 🖥️ Infotainment System

A custom **Qt-based infotainment interface** was developed to:

* Display real-time ADAS alerts
* Show traffic sign recognition results
* Enable/disable safety features dynamically
* Improve driver interaction with the SDV platform

---

# 🏗️ System Architecture

The project follows a layered SDV-inspired architecture.

## 🔹 Embedded Layer — STM32 + FreeRTOS

Responsible for:

* Sensor data acquisition
* Real-time task scheduling
* Actuator control
* Low-level hardware interaction

### Technologies:

* STM32 Microcontroller
* FreeRTOS
* SPI Communication

---

## 🔹 Edge Computing Layer — Raspberry Pi

Responsible for:

* Running ADAS software modules
* AI inference
* Data processing
* Communication management

### Technologies:

* Raspberry Pi
* Embedded Linux
* Eclipse Leda
* Docker/Containerization

---

## 🔹 Communication Layer

Provides seamless real-time communication between components.

### Protocols Used:

* MQTT → Inter-module communication
* SPI → High-speed communication between STM32 and Raspberry Pi

---

# 🤖 AI Model

## Traffic Sign Recognition (TSR)

### Model:

* YOLOv8n

### Optimization:

* Converted to ONNX format for lightweight edge deployment
* Optimized for real-time inference on Raspberry Pi

### Workflow:

1. Capture camera frames
2. Preprocess images
3. Run ONNX inference
4. Detect and classify traffic signs
5. Send results to infotainment system

---

# 🔄 OTA (Over-The-Air) Update Readiness

The architecture was designed with future OTA support in mind, enabling:

* Remote software updates
* Modular deployment
* Feature scalability
* Continuous improvement without hardware modifications

---

# 📂 Project Structure

```bash
├── STM32_FreeRTOS/
│   ├── EBS_Module/
│   ├── BSD_Module/
│   └── Drivers/
│
├── RaspberryPi_ADAS/
│   ├── TSR_YOLOv8/
│   ├── ONNX_Runtime/
│   ├── MQTT_Handler/
│   └── Containers/
│
├── Qt_Infotainment/
│   ├── UI/
│   ├── Alerts/
│   └── Feature_Control/
│
├── Communication/
│   ├── MQTT/
│   └── SPI/
│
└── Documentation/
```

---

# ⚙️ Technologies Used

## Embedded Systems

* STM32
* FreeRTOS
* SPI

## Edge Computing

* Raspberry Pi
* Embedded Linux
* Eclipse Leda

## AI & Computer Vision

* YOLOv8n
* ONNX Runtime
* OpenCV

## Communication

* MQTT

## GUI Development

* Qt Framework

## Containerization

* Docker Containers

---

# 🚀 Key Learning Outcomes

Through this project, we gained hands-on experience in:

* Software-Defined Vehicle architectures
* Embedded real-time systems
* MQTT-based communication
* Containerized automotive applications
* Edge AI deployment
* Lightweight object detection models
* Embedded Linux environments
* OTA-ready modular software design

---

# 🔮 Future Improvements

Potential future enhancements include:

* Lane Detection System
* Adaptive Cruise Control
* Vehicle-to-Vehicle (V2V) Communication
* Cloud-based telemetry dashboard
* Full OTA implementation
* Cybersecurity integration for SDV systems
* CAN Bus integration
* Sensor fusion with LiDAR/Radar

---

# 👥 Team Contribution

This project was developed collaboratively to explore the future of intelligent automotive systems through the integration of:

* Embedded systems
* Artificial intelligence
* Real-time communication
* Software-defined architectures

---

# 📜 License

This project is intended for educational and research purposes.

---

# 📧 Contact

For questions, collaboration, or contributions, feel free to reach out through GitHub or LinkedIn.
