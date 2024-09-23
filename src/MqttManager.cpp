#include <FS.h>
#include "MqttManager.h"
#include "Config.h"

Config config;

MqttManager::MqttManager() {
    // Construtor vazio
}

void MqttManager::init(Client &client) {
    
    mqttClient.setClient(client);

    mqttClient.setServer(config.mqttBroker.c_str(), config.mqttPort);
}

void MqttManager::connect() {
    while (!mqttClient.connected()) {
        Serial.println("Connecting to MQTT...");

        if (mqttClient.connect("ESP8266Client", config.mqttUser.c_str(), config.mqttPassword.c_str())) {
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
