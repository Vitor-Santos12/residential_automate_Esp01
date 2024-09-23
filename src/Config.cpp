#include "Config.h"

bool loadConfig(Config &config) {
    if (!SPIFFS.begin()) {
        Serial.println("Falha ao montar o sistema de arquivos");
        return false;
    }

// ***Está lendo arquivo ***

    File file = SPIFFS.open("/secret.env", "r");
    if (!file) {
        Serial.println("Falha ao abrir o arquivo secret.env");
        return false;
    }else{
        Serial.println("\nArquivo secret.env aberto com sucesso");
        while(file.available()){
            Serial.write(file.read());
        }
    }

    size_t size = file.size();
    std::unique_ptr<char[]> buf(new char[size]);

    file.readBytes(buf.get(), size);
    file.close();

// Possível resoluçao //

/* 
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
*/

// *** Biblioteca JSon não está funcionando

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, buf.get());

    if (error) {
        Serial.println("Falha ao analisar o arquivo secret.env");
        return false;
    }else{
        Serial.println("Arquivo secret.env analisado com sucesso");
        strlcpy(config.wifiSSID, doc["WIFI_SSID"], sizeof(config.wifiSSID));
        strlcpy(config.wifiPassword, doc["WIFI_PASSWORD"], sizeof(config.wifiPassword));
        config.piscaLed = doc["piscaLed"];
        strlcpy(config.mqttServer, doc["MQTT_BROKER"], sizeof(config.mqttServer));
        config.mqttPort = doc["MQTT_PORT"];
        strlcpy(config.firebaseHost, doc["FIREBASE_HOST"], sizeof(config.firebaseHost));
        strlcpy(config.firebaseAuth, doc["FIREBASE_AUTH"], sizeof(config.firebaseAuth));
    }

    return true;
}