import paho.mqtt.client as mqtt
import spidev
import time
import json
import logging
import threading
from queue import Queue


# --- Logging Setup ---
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


# --- Load Configurations ---
try:
    with open("config.json", "r") as file:
        config = json.load(file)
    logger.info("Config loaded successfully")
except FileNotFoundError:
    logger.error("Config file not found. Using defaults.")
    config = {
        "mqtt": {"broker_name": "localhost", "port_number": 1883, "keep_alive_interval": 10},
        "spi": {"bus": 0, "device": 0, "max_speed_hz": 50000, "mode": 0},
        "topics": {
            "front": "sensors/front",
            "left": "sensors/left",
            "right": "sensors/right",
            "heartbeat": "sensors/heartbeat",
            "break": "actuators/break"
        }
    }
except json.JSONDecodeError:
    logger.error("Error: Invalid JSON format in file.")
except Exception as e:
    logger.error(f"Unexpected error: {e}.")


# --- SPI Setup ---
spi = spidev.SpiDev()
spi_lock = threading.Lock()  # Creat the lock to protect concurrent SPI operations

try:
    spi.open(config["spi"]["bus"], config["spi"]["device"])
    spi.max_speed_hz = config["spi"]["max_speed_hz"]
    spi.mode = config["spi"]["mode"]
    logger.info("SPI initialized")
except Exception as e:
    logger.error(f"SPI init failed: {e}")
    raise


# --- MQTT Setup ---
client = mqtt.Client()
command_queue = Queue()  # Thread-safe queue for actuator commands

def on_connect(client, userdata, flags, rc):        # rc for return-code 0 success , otherwise failur
    if rc == 0:
        logger.info("Connected to MQTT broker")
        client.subscribe(config["topics"]["break"])
    else:
        logger.error(f"Connection failed with RC: {rc}")


def on_disconnect(client, userdata, rc):
    logger.warning(f"Disconnected (RC: {rc}). Reconnecting...")
    client.reconnect()


def on_message(client, userdata, msg):
    try:
        command = msg.topic.split('/')[1]   # Extract command (e.g., "brake")
        value = int(msg.payload.decode())   # Convert payload to integer
        command_queue.put((command, value)) # Add to thread-safe queue
        logger.info(f"Received command: {command}={value}")
    except Exception as e:
        logger.error(f"Invalid recieved command from actuators: {e}")

client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.on_message = on_message


try:
    client.connect(
        config["mqtt"]["broker_name"],
        config["mqtt"]["port_number"],
        config["mqtt"]["keep_alive_interval"]
    )
except Exception as e:
    logger.error(f"MQTT connection error: {e}")
    raise

client.loop_start()                                # Runs MQTT in the background


# --- Sensor Data Reading --- Data formate [ 0xA0 front left right 0xB0 ] ---
def receive_sensor_data():
    dummy_data = [0x00] * 5
    with spi_lock:                      # Only one thread at a time can run this code
        response = spi.xfer2(dummy_data)
    if len(response) == 5 and response[0] == 0xA0 and response[-1] == 0xB0:
        return {
            'front_altrasonic': response[1],
            'left_altrasonic': response[2],
            'right_altrasonic': response[3]
        }
    return {'front_altrasonic': None, 'left_altrasonic': None, 'right_altrasonic': None}


# --- Actuator Command Processing ---
def process_actuator_commands():
    while True:
        try:
            command, value = command_queue.get(timeout=1.0)
            with spi_lock:
                if (command=="break"):
                    spi.xfer2([0x01, value])                  # Send command to STM32 ( 0x01 for break command)
            logger.info(f"Sent to STM32: {command} = {value}")
        except queue.Empty:
            pass  # No commands in queue
        except Exception as e:
            logger.error(f"Command processing error: {e}")


# Start actuator thread
actuator_thread = threading.Thread(target=process_actuator_commands, daemon=True)
actuator_thread.start()


# --- Main Loop ---
prev_sensor_data = {'front_altrasonic': None, 'left_altrasonic': None, 'right_altrasonic': None}
last_heartbeat_time = time.time()
heartbeat_interval = 5


try:
    while True:
        current_time = time.time()
        sensor_data = receive_sensor_data()                # Listining to SPI
        data_changed = sensor_data != prev_sensor_data

        # Publish sensor data if changed
        if data_changed:
            client.publish(config["topics"]["front"], sensor_data['front_altrasonic'], qos=1)
            client.publish(config["topics"]["left"],  sensor_data['left_altrasonic'] , qos=1)
            client.publish(config["topics"]["right"], sensor_data['right_altrasonic'], qos=1)
            prev_sensor_data = sensor_data

        # Check Heartbeat interval if our system running properly
        if (current_time - last_heartbeat_time) >= heartbeat_interval:
            client.publish(config["topics"]["heartbeat"], 'Alive!', qos=1)
            last_heartbeat_time = current_time

        # set a delay for Reading each 50 ms and for CPU Efficiency as well
        time.sleep(0.05)
finally:
    spi.close()
    client.loop_stop()
    client.disconnect()
    logger.info("Shutdown complete")



