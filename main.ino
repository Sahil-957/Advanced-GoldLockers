// main.ino
#include "config.h"
#include "camera_pins.h"
#include "aws_mmqtt.h"
#include "face_detection.h"

// camera_setup.h
#ifndef CAMERA_SETUP_H
#define CAMERA_SETUP_H

#include "esp_camera.h"
#include "camera_pins.h"

void initCamera() {
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    // Frame size and quality
    if (psramFound()) {
        config.frame_size = FRAMESIZE_UXGA;
        config.jpeg_quality = 10;
        config.fb_count = 2;
    } else {
        config.frame_size = FRAMESIZE_SVGA;
        config.jpeg_quality = 12;
        config.fb_count = 1;
    }

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }
    Serial.println("Camera Initialized Successfully!");
}

#endif // CAMERA_SETUP_H


#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "esp_camera.h"

WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);
    
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected!");

    espClient.setCACert(AWS_ROOT_CA);
    espClient.setCertificate(AWS_DEVICE_CERT);
    espClient.setPrivateKey(AWS_PRIVATE_KEY);
    client.setServer(AWS_IOT_ENDPOINT, 8883);

    if (connectToAWS()) {
        Serial.println("Connected to AWS IoT!");
    } else {
        Serial.println("AWS IoT Connection Failed!");
    }
    
    initCamera();
}

void loop() {
    if (!client.connected()) {
        connectToAWS();
    }
    client.loop();
    
    if (detectFace()) {
        Serial.println("Face detected!");
        client.publish("esp32/face", "Face detected");
    }
    delay(1000);
}
