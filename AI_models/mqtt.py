import time
import cv2
from ultralytics import YOLO
import numpy as np
import paho.mqtt.client as mqtt
import json
import threading
import sys
import os
import contextlib

# Suppress stderr
sys.stderr = open(os.devnull, 'w')

import warnings
warnings.filterwarnings("ignore", category=UserWarning, module='ultralytics')

# For raspberry pi camera
# from picamera2 import picamera2

# Load ONNX model
with contextlib.redirect_stdout(open(os.devnull, 'w')), contextlib.redirect_stderr(open(os.devnull, 'w')):
    model = YOLO("model.onnx", task='detect')

model.predict(verbose=False)

# Class names
class_names = [
    "Green Light", "Red Light", "Speed Limit 10", "Speed Limit 100", "Speed Limit 110",
    "Speed Limit 120", "Speed Limit 20", "Speed Limit 30", "Speed Limit 40", "Speed Limit 50",
    "Speed Limit 60", "Speed Limit 70", "Speed Limit 80", "Speed Limit 90", "Stop"
]

# MQTT setup
broker_address = "localhost"
pub_topic = "info/tsr"
sub_topic = "control/tsr"
client = mqtt.Client()

# Shared control variable
running = True 


def on_message(client, userdata, msg):
    global running
    payload = msg.payload.decode().strip().lower()
    if payload == "on":
        print("✅ Received ON → starting detection.")
        running = True
    elif payload == "off":
        print("🛑 Received OFF → stopping detection.")
        running = False

client.on_message = on_message
client.connect(broker_address)
client.subscribe(sub_topic)
client.loop_start()

# Previous detection info
prev_detection = {
    'classes': [],
    'boxes': [],
    'count': 0
}

def boxes_similar(box1, box2, iou_threshold=0.7):
    x1, y1, w1, h1 = box1
    x2, y2, w2, h2 = box2
    xi1 = max(x1, x2)
    yi1 = max(y1, y2)
    xi2 = min(x1 + w1, x2 + w2)
    yi2 = min(y1 + h1, y2 + h2)
    inter_area = max(0, xi2 - xi1) * max(0, yi2 - yi1)
    union_area = (w1 * h1) + (w2 * h2) - inter_area
    return (inter_area / union_area) > iou_threshold if union_area > 0 else False

# Open camera
# For laptop testing
cap = cv2.VideoCapture(0)  

# For raspberry pi camera
# picam2 = Picamera2()
# picam2.configure(picam2.create_preview_configuration())
# picam2.start()

try:
    while True:
        # For laptop testing
        ret, frame = cap.read()  

        # For raspberry pi camera
        #frame = picam2.capture_array()
        # ret = frame is not None
        
        if not ret:
            break

        if running:
            results = model.predict(frame, conf=0.5, verbose=False)
            current_boxes = results[0].boxes

            current_detection = {'classes': [], 'boxes': [], 'count': 0}

            if current_boxes:
                current_detection['count'] = len(current_boxes)
                for box in current_boxes:
                    cls_id = int(box.cls[0])
                    current_detection['classes'].append(class_names[cls_id])
                    current_detection['boxes'].append(box.xywh[0].tolist())

            detection_changed = (
                current_detection['count'] != prev_detection['count'] or
                current_detection['classes'] != prev_detection['classes'] or
                not all(boxes_similar(c, p) for c, p in zip(current_detection['boxes'], prev_detection['boxes']))
            )

            if detection_changed:
                annotated_frame = results[0].plot()
                prev_detection = current_detection.copy()

                # Publish to MQTT
                detected_class = str(current_detection['classes'])
                if len(detected_class) > 4:
                    message = detected_class[2:-2]
                client.publish(pub_topic,message)
                print("📤 Published:", message)

finally:
    cap.release()  # for testing
    client.loop_stop()
    client.disconnect()
