Gold Locker Project

📖 Project Overview

The Gold Locker Project is a smart locker system designed for securely storing valuables, specifically gold. It features:

Face Detection for primary user authentication.

Actuator-Based Locking System using a 12V solenoid lock.

AWS IoT Integration for remote monitoring and control.

ESP32 Microcontroller for edge processing.


Future scope includes RFID-based authentication and weight sensing.


---

🎯 Project Objectives

1. Implement face detection for secure user authentication.


2. Control locker locking and unlocking using an actuator.


3. Integrate AWS IoT Core for remote access and monitoring.


4. Ensure fail-safe locking when power is cut.




---

🛠️ Hardware Requirements

1. ESP32 Microcontroller – For controlling the system.


2. 12V Solenoid Lock – For locking and unlocking.


3. Camera Module – For face detection.


4. Relay Module – To control the solenoid lock.


5. Power Supply (12V) – To power the solenoid and ESP32.


6. Breadboard & Jumper Wires – For prototyping.




---

🖥️ Software Requirements

1. Arduino IDE – For ESP32 programming.


2. AWS IoT Core – For MQTT-based communication.


3. ESP32 Board Package – For Arduino IDE.


4. ArduinoJson Library – For handling JSON payloads.




---

📡 System Architecture

1. User Authentication: Face detection verifies user identity.


2. AWS Communication: ESP32 communicates with AWS IoT via MQTT.


3. Actuator Control: Actuator unlocks the locker upon successful authentication.


4. Fail-Safe: Locker remains locked during power failure.




---

⚙️ Setup Instructions

1. ESP32 Configuration

Install the ESP32 Board Package in Arduino IDE.

Install required libraries: WiFi, PubSubClient, ArduinoJson.


2. AWS IoT Configuration

Create an AWS IoT Thing.

Generate certificates and attach them to the Thing.

Attach an IoT Policy with Connect, Publish, Subscribe, and Receive permissions.

Note down the AWS Endpoint, Thing Name, and Topic Names.


3. Code Configuration

1. Create a secret.h file with:



#define WIFI_SSID "Your_WiFi_Name"
#define WIFI_PASSWORD "Your_WiFi_Password"
#define AWS_IOT_ENDPOINT "Your_AWS_Endpoint"
#define THINGNAME "Your_Thing_Name"
#define AWS_CERT_CA "Your_CA_Certificate"
#define AWS_CERT_CRT "Your_Device_Certificate"
#define AWS_CERT_PRIVATE "Your_Private_Key"

2. Upload the main Arduino code to ESP32.




---

🔄 MQTT Topics

Publish Topic: esp32/pub

Subscribe Topic: esp32/sub


Example Payload to control the actuator:

{
  "message": "Hello from AWS IoT console",
  "led_Control": "1"
}

"led_Control": "1" → Unlock the locker.

"led_Control": "0" → Lock the locker.



---

🚀 Testing & Deployment

1. Power the ESP32 and solenoid lock.


2. Ensure stable Wi-Fi connectivity.


3. Test face detection and actuator responses.


4. Monitor AWS IoT Core for MQTT messages.




---

📅 Project Timeline


---

📷 Future Scope

1. RFID Authentication: For alternate user access.


2. Weight Sensor: To detect the presence of valuables.


3. Mobile App: For remote locker control.




---

🤝 Contributors

1. [Your Name] – Project Lead & Developer.


2. [Collaborator Name] – AWS & Cloud Integration.




---

📝 License

This project is licensed under the MIT License. Feel free to modify and use it for personal or educational purposes.

For any queries, contact: [Your Email Address]
