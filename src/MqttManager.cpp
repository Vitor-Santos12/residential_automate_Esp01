#include <FS.h>
#include <PubSubClient.h>
#include "MqttManager.h"
#include "Config.h"

Config configMqttManager;

void MqttManagerset::init(Client &client) {

    mqttClient.setClient(client);

    mqttClient.setServer(configMqttManager.mqttBroker.c_str(), configMqttManager.mqttPort);

    return;
}

void MqttManagerset::connect() {

    while (!mqttClient.connected()) {
        Serial.println("Connecting to MQTT...");

        if (mqttClient.connect("House Automate", configMqttManager.mqttUser.c_str(), configMqttManager.mqttPassword.c_str())) {
            Serial.println("Connected to MQTT broker");
        } else {
            Serial.print("Failed to connect, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void MqttManagerset::publish(const char* topic, const char* payload) {
    mqttClient.publish(topic, payload);
}

void MqttManagerset::subscribe(const char* topic) {
    mqttClient.subscribe(topic);
}

/* void MqttManagerset::loop() {
    mqttClient.loop();
} */
