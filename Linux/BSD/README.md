## SDV with ADAS - Blind Spot Detection Module

## Overview

This module is part of the Smart Driving Vehicle (SDV) with Advanced Driver Assistance Systems (ADAS) graduation project. 
The Blind Spot Detection (BSD) system monitors the vehicle's blind spots using sensors and provides alerts when obstacles are detected.

## System Architecture

The system is divided into the following modules:
1. **Configuration Module**: Reads the config.json file and manages the configuration parameters
2. **Communication Module**: Handles MQTT communication [Connecting to broker, subscribing to topics, publishing to topics, disconnecting]
3. **Blind Spot Detection Module**: Processes sensor data and triggers alerts
4. **Left & Right blind spot threads**: two separate threads to handle the blind spots
