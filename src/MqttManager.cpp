#include <FS.h>
#include "MqttManager.h"

MqttManager::MqttManager() {
    // Construtor vazio
}

void MqttManager::init(Client &client) {
    mqttClient.setClient(client);

    // Carregar variáveis de ambiente do arquivo secret.env
    loadEnvConfig();

    mqttClient.setServer(mqttBroker.c_str(), mqttPort);
}

void MqttManager::loadEnvConfig() {
    if (!SPIFFS.begin()) {
        Serial.println("Failed to mount file system");
        return;
    }

    File file = SPIFFS.open("/secret.env", "r");
    if (!file) {
        Serial.println("Failed to open secret.env file");
        return;
    }

    size_t size = file.size();
    if (size > 1024) {
        Serial.println("secret.env file size is too large");
        return;
    }

    std::unique_ptr<char[]> buf(new char[size]);
    file.readBytes(buf.get(), size);
    file.close();

    // Parsear o arquivo env
    String content = String(buf.get());
    int startIndex = 0;
    while (startIndex >= 0) {
        int endIndex = content.indexOf('\n', startIndex);
        String line = content.substring(startIndex, endIndex);
        int separatorIndex = line.indexOf('=');
        if (separatorIndex >= 0) {
            String key = line.substring(0, separatorIndex);
            String value = line.substring(separatorIndex + 1);

            if (key == "MQTT_BROKER") mqttBroker = value;
            else if (key == "MQTT_PORT") mqttPort = value.toInt();
            else if (key == "MQTT_USER") mqttUser = value;
            else if (key == "MQTT_PASSWORD") mqttPassword = value;
        }
        startIndex = endIndex + 1;
    }

    Serial.println("MQTT configuration loaded:");
    Serial.println("Broker: " + mqttBroker);
    Serial.println("Port: " + String(mqttPort));
}

void MqttManager::connect() {
    while (!mqttClient.connected()) {
        Serial.println("Connecting to MQTT...");

        if (mqttClient.connect("ESP8266Client", mqttUser.c_str(), mqttPassword.c_str())) {
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
