Custom ESP32 BLE Remote Controller
A robust, low-latency wireless controller designed to bring reliable Bluetooth Low Energy (BLE) control to robotics, drones, and custom embedded systems. Built around the ESP32 WROOM 32, this project replaces bulky, off-the-shelf RC transmitters with a highly customizable, rechargeable control hub.

> Key Features:
1. Zero-Tether Control: Leverages ESP32's BLE protocol for high-speed, low-latency communication, ensuring real-time responsiveness for dynamic robotic movements.
2. Smart Power Architecture: Powered by a 2S Li-Ion battery pack with an integrated Battery Management System (BMS) and modern Type-C charging. No more swapping dead AA batteries mid-testing.
3. Precision & Tactile Input: Features dual analog joysticks for multi-axis maneuvering, paired with toggle and limit switches for instant mode-switching and auxiliary controls.
4. Active Telemetry & Feedback: Integrated battery voltage monitoring triggers the onboard buzzer and LED indicators, providing immediate physical and visual feedback before power drops out.

> Hardware Stack:
1. Microcontroller: ESP32 WROOM 32 NodeMCU
2. Power System: 2S Li-Ion Battery + BMS + Type-C Charging Module
3. Inputs: 2x Analog Joysticks, Toggle Switches, Limit Switches
4. Outputs/Feedback: Piezo Buzzer, Status LEDs
5. Connectivity: Bluetooth Low Energy (BLE)

> Use Cases:
Designed primarily as a versatile command center for custom engineering projects, including:
- Omnidirectional rovers and robotic arms
- Drone and UAV payload triggers
- Remote industrial mechanism testing
