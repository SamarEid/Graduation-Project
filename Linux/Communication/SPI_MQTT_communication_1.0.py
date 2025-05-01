import paho.mqtt.client as mqtt
import spidev
import time
import json
import struct
import logging
import threading
from queue import Queue, Empty


# --- Logging Setup ---
logging.basicConfig(level=logging.INFO, format="%(asctime)s [%(levelname)s] %(message)s", datefmt="%Y-%m-%d %H:%M:%S")
logger = logging.getLogger(__name__)


# --- Load Configurations ---
try:
    with open("config.json", "r") as file:
        config = json.load(file)
    logger.info("Configurations loaded successfully")
except FileNotFoundError:
    logger.error("Config file not found. Using defaults.")
    config = {
        "mqtt": {"broker_name": "localhost", "port_number": 1883, "keep_alive_interval": 10},
        "spi": {"bus": 0, "device": 0, "max_speed_hz": 500000, "mode": 0},
        "topics": {
            "front":     "sensors/front",
            "left":      "sensors/left",
            "right":     "sensors/right",
            "heartbeat": "sensors/heartbeat",
            "start":     "actuators/start",
            "forward":   "actuators/forward",
            "reverse":   "actuators/reverse",
            "turnRight": "actuators/turnRight",
            "turnLeft":  "actuators/turnLeft",
            "stop":      "actuators/stop"
        }
    }
except json.JSONDecodeError:
    logger.error("Error: Invalid JSON format in file.")
except Exception as e:
    logger.error(f"Unexpected error: {e}.")


# --- SPI Setup ---
spi = spidev.SpiDev()
spi_lock = threading.Lock()                         # Creat the lock to protect concurrent SPI operations

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
command_queue = Queue()                             # Thread-safe queue for actuator commands

def on_connect(client, userdata, flags, rc):        # rc for return-code 0 success , otherwise failur
    if rc == 0:
        logger.info("Connected to MQTT broker")
        client.subscribe(config["topics"]["start"])
        client.subscribe(config["topics"]["forward"])
        client.subscribe(config["topics"]["reverse"])
        client.subscribe(config["topics"]["turnRight"])
        client.subscribe(config["topics"]["turnLeft"])
        client.subscribe(config["topics"]["stop"])
    else:
        logger.error(f"Connection failed with RC: {rc}")


def on_disconnect(client, userdata, rc):
    logger.warning(f"Disconnected (RC: {rc}). Reconnecting...")
    client.reconnect()


def on_message(client, userdata, msg):
    try:
        command = msg.topic.split('/')[1]           # Extract command (e.g., "actuators/brake")
        value = int(msg.payload.decode())           # Convert payload to integer
        command_queue.put((command, value))         # Add to thread-safe queue
        logger.info(f"-"*40)
        logger.info(f"Received Command '{command}' from MQTT broker")
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


# --- Sensors Data Reading ---
def receive_sensor_data():
    dummy_data = [0x00] * 10
    with spi_lock:
        response = bytes(spi.xfer2(dummy_data))
        if response[0] == 0xA0 and response[-1] == 0xB0 :
            sensor_id = struct.unpack('<I', response[1:5])[0]
            sensor_data = struct.unpack('<f', response[5:9])[0]
            if sensor_id==1:
                logger.info(f'Received Front Ultrasonic sensor data with value: {sensor_data}')
                return { 'front': sensor_data }
            elif sensor_id==2:
                logger.info(f'Received Left Ultrasonic sensor data with value: {sensor_data}')
                return { 'left': sensor_data  }
            elif sensor_id==3:
                logger.info(f'Received Right Ultrasonic sensor data with value: {sensor_data}')
                return { 'right': sensor_data }
    logger.info('None Data received form STM32 right now !!!')
    return {'front': None, 'left': None, 'right': None}


# --- Actuator Command Processing ---
def process_actuator_commands():

    # Verify Command is Sent to STM32 Successfully
    def verify_command_format(byte, timeout=1.0):
        start_time = time.time()
        while True:
            res = spi.xfer2(byte + [0x00] * 9)                  
            if res[0] == 0xA0 and res[-1] == 0xB0:
                logger.info(f'Command sent to STM32 Successfully')
                break
            if time.time() - start_time > timeout:
                logger.error('SPI Command Verification timeout!')
                break

    while True:
        try:
            command, value = command_queue.get(timeout=1.0)
            with spi_lock:
                if (command=="start"):
                    verify_command_format([0x0A])
                elif (command=="forward"):
                    verify_command_format([0x0B])
                elif (command=="reverse"):
                    verify_command_format([0x0C])
                elif (command=="turnRight"):
                    verify_command_format([0x0D])
                elif (command=="turnLeft"):
                    verify_command_format([0x0E])
                elif (command=="stop"):
                    verify_command_format([0x0F])
                logger.info('-'*40)
        except Empty:                              # No commands in queue
            pass                                            
        except Exception as e:
            logger.error(f"Command processing error: {e}")


# Start actuator thread
actuator_thread = threading.Thread(target=process_actuator_commands, daemon=True)
actuator_thread.start()


# --- Main Loop ---

prev_sensor_data = {'front': None, 'left': None, 'right': None}
last_heartbeat_time = time.time()
heartbeat_interval = 10

try:
    while True:
        current_time = time.time()
        sensor_data = prev_sensor_data.copy()
        sensor_data.update( receive_sensor_data() )
        data_changed = sensor_data != prev_sensor_data

        # Publish sensor data if changed
        if data_changed:
            client.publish(config["topics"]["front"], sensor_data['front'], qos=1)
            client.publish(config["topics"]["left" ], sensor_data[ 'left'], qos=1)
            client.publish(config["topics"]["right"], sensor_data['right'], qos=1)
            prev_sensor_data = sensor_data

        # Check Heartbeat interval if our system running properly
        if (current_time - last_heartbeat_time) >= heartbeat_interval:
            client.publish(config["topics"]["heartbeat"], 'Alive', qos=1)
            last_heartbeat_time = current_time

        # set a delay for CPU Efficiency
        time.sleep(0.05)

finally:
    spi.close()
    client.loop_stop()
    client.disconnect()
    logger.info("Shutdown completed successfully!")




