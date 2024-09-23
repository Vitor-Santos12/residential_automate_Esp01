#include <FS.h>
#include "MqttManager.h"
#include "Config.h"

Config configMqttManager;

MqttManager::MqttManager() {
    // Construtor vazio
}

void MqttManager::init(Client &client) {

    mqttClient.setClient(client);

    mqttClient.setServer(configMqttManager.mqttBroker.c_str(), configMqttManager.mqttPort);
}

void MqttManager::connect() {

    while (!mqttClient.connected()) {
        Serial.println("Connecting to MQTT...");

        if (mqttClient.connect("ESP8266Client", configMqttManager.mqttUser.c_str(), configMqttManager.mqttPassword.c_str())) {
            Serial.println("Connected to MQTT broker");
        } else {
            Serial.print("Failed to connect, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void MqttManager::publish(const char* topic, const char* payload) {
    mqttClient.publish(topic, payload);
}

void MqttManager::subscribe(const char* topic) {
    mqttClient.subscribe(topic);
}

void MqttManager::loop() {
    mqttClient.loop();
}
