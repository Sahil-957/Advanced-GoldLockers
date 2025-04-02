// aws_mqtt.h
#ifndef AWS_MQTT_H
#define AWS_MQTT_H

#include <WiFiClientSecure.h>
#include <PubSubClient.h>

extern WiFiClientSecure espClient;
extern PubSubClient client;

bool connectToAWS() {
    Serial.print("Connecting to AWS IoT...");

    while (!client.connected()) {
        if (client.connect("ESP32CAM_Client")) {
            Serial.println("Connected to AWS IoT!");
            return true;
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" trying again in 5 seconds...");
            delay(5000);
        }
    }
    return false;
}

#endif // AWS_MQTT_H
