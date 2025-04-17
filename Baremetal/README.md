# ADAS with SDV BareMetal Development

## this is the full Advanced Driving Assistance System with Software Defined vehicles 

The bare-metal portion of the ADAS with SDV (Advanced Driving Assistance Systems with Software Defined Vehicles) project is implemented on an STM32 microcontroller, focusing on real-time control and direct hardware interfacing, enhanced by the use of a Real-Time Operating System (RTOS). This system is responsible for time-critical ADAS functionalities and implements two key SDV layers: perception and actuation. The perception layer handles sensor data acquisition, while the actuation layer manages motor control and safety feature execution, including Emergency Braking. By using a bare-metal approach, the system achieves low-latency responses and deterministic behavior—both critical for ensuring reliable and safe operation in automotive environments.

### ADAS features

<img src="https://www.google.com/imgres?q=ADAS%20features&imgurl=https%3A%2F%2Fmulticorewareinc.com%2Fwp-content%2Fuploads%2F2023%2F12%2FADAS-Features-1.png&imgrefurl=https%3A%2F%2Fmulticorewareinc.com%2Fwhat-we-do%2Fautonomous-mobility%2Fl2-adas%2F&docid=QgGDbxgyByffeM&tbnid=JmN8c0EBIWE7cM&vet=12ahUKEwif0--e_t6MAxVk2AIHHePNLOwQM3oECFIQAA..i&w=1050&h=591&hcb=2&ved=2ahUKEwif0--e_t6MAxVk2AIHHePNLOwQM3oECFIQAA" alt= "ADAS features" width="80%">

### System Layers

<img src="./assets/img/architecture.drawio.png" alt="SDV Architecture" width="80%">

