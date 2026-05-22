# AI models


# 🚦 Traffic Sign Detection and Recognition using YOLOv8

This project implements a real-time **traffic sign detection and recognition system** using the **YOLOv8** object detection algorithm. The trained model is exported to **ONNX format** for efficient inference on edge devices like the **Raspberry Pi**. The system processes camera input and communicates detections via **MQTT**, making it suitable for smart transportation and embedded AI applications.

---

## 📌 Features

* 🚘 Detects 15 classes of traffic signs, including speed limits, stop sign, and traffic lights
* ⚡ Fast and lightweight YOLOv8 model exported to ONNX
* 📷 Real-time inference from camera input on Raspberry Pi
* 📡 MQTT communication to send detection results on "on/off" command
* 🧠 Optimized using `onnxruntime` for efficient edge deployment

---

## 🧠 Classes Detected

The model recognizes the following traffic signs:

1. Green Light
2. Red Light
3. Speed Limit 10
4. Speed Limit 100
5. Speed Limit 110
6. Speed Limit 120
7. Speed Limit 20
8. Speed Limit 30
9. Speed Limit 40
10. Speed Limit 50
11. Speed Limit 60
12. Speed Limit 70
13. Speed Limit 80
14. Speed Limit 90
15. Stop

---

## 📂 Project Structure

```
traffic_sign_detector/
├── models/
│   └── traffic_signs.onnx            # YOLOv8 model in ONNX format
├── main.py                           # Inference script for Raspberry Pi
├── mqtt_client.py                    # Handles MQTT communication
├── camera_stream.py                  # Captures and processes frames from the camera
├── utils.py                          # Helper functions (e.g., drawing boxes, decoding classes)
├── requirements.txt                  # Dependencies
└── README.md                         # Project documentation
```

---

## 🛠️ Setup Instructions

### 1. Install dependencies

```bash
pip install onnxruntime opencv-python paho-mqtt numpy
```

### 2. Run the system

```bash
python main.py
```

The system will:

* Start the camera stream.
* Process frames using the ONNX YOLOv8 model.
* Send detection results via MQTT based on "on/off" command.

---

## 📡 MQTT Integration

* Broker: `localhost`
* Subscribed topic: `/command`
* Publishes results on: `/detections`

Send the command `"on"` to start detection, and `"off"` to stop it.

---

## 🐍 Inference Pipeline

1. Capture frame from camera
2. Preprocess frame to match YOLOv8 input
3. Run ONNX model using `onnxruntime`
4. Decode bounding boxes, confidences, and classes
5. Draw results and publish detection to MQTT broker

---

## 💻 Deployment

* Device: Raspberry Pi 4
* Optimized for low-power, real-time performance
* Uses `onnxruntime` for CPU-efficient inference

---

## 📷 Sample Output

(You can add sample image or video frames here to demonstrate detection.)

---

## 🧑‍💻 Author

**Shereen Alaa**
Machine Learning Engineer
[LinkedIn](https://www.linkedin.com/in/shreen-alaa/) | [GitHub](https://github.com/shreenalaa)

---

## 📄 License


