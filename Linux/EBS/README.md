## SDV with ADAS - Emergency Braking System Module

## Overview

This module is part of the Smart Driving Vehicle (SDV) with Advanced Driver Assistance Systems (ADAS) graduation project. 
The Emergency Braking System (EBS) continuously monitors obstacles in front of the vehicle and takes action to prevent collisions.

## System Architecture

The system is divided into the following modules:
1. **Configuration Module**: Reads the config.json file and manages the configuration parameters
2. **Communication Module**: Handles MQTT communication [Connecting to broker, subscribing to topics, publishing to topics, disconnecting]
3. **Emergency Braking System Module**: Processes sensor data and triggers alerts
