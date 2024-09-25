#include "Config.h"

bool loadConfig(Config &config) {

    if (!SPIFFS.begin()) {
        Serial.println("Failed to mount file system");
    }

    File file = SPIFFS.open("/secret.env", "r");
    if (!file) {
        Serial.println("Failed to open secret.env file");
    }else{
        Serial.println("\nArquivo secret.env aberto com sucesso");

    size_t size = file.size();
    if (size > 1024) {
        Serial.println("secret.env file size is too large");
    }

    std::unique_ptr<char[]> buf(new char[size]);
    file.readBytes(buf.get(), size);
    file.close();

    // Parsear o arquivo env
    String content = String(buf.get());
    int startIndex = 0;
    while (startIndex >= 0) {
        int endIndex = content.indexOf('\n', startIndex);
        Serial.println("startIndex: " + startIndex);
        Serial.println("endIndex" +endIndex);
        String line = content.substring(startIndex, endIndex);
        int separatorIndex = line.indexOf('=');
        if (separatorIndex >= 0) {
            String key = line.substring(0, separatorIndex);
            String value = line.substring(separatorIndex + 1);

            if (key == "MQTT_BROKER") config.mqttBroker = value;
            else if (key == "MQTT_PORT") config.mqttPort = value.toInt();
            else if (key == "MQTT_USER") config.mqttUser = value;
            else if (key == "MQTT_PASSWORD") config.mqttPassword = value;

            else if (key == "FIREBASE_HOST") config.firebaseHost = value;
            else if (key == "FIREBASE_AUTH") config.firebaseAuth = value;

            else if (key == "PISCALED") config.piscaLed = value.toInt();

            else if (key == "WIFI_SSID") config.wifiSSID = value;
            else if (key == "WIFI_PASSWORD") config.wifiPassword = value;
        }
        startIndex = endIndex + 1;
    }

    }

    return true;
}

// *** Biblioteca JSon não está funcionando

    // DynamicJsonDocument doc(1024);
    // DeserializationError error = deserializeJson(doc, buf.get());

    // if (error) {
    //     Serial.println("Falha ao analisar o arquivo secret.env");
    //     return false;
    // }else{
    //     Serial.println("Arquivo secret.env analisado com sucesso");
    //     strlcpy(config.wifiSSID, doc["WIFI_SSID"], sizeof(config.wifiSSID));
    //     strlcpy(config.wifiPassword, doc["WIFI_PASSWORD"], sizeof(config.wifiPassword));
    //     config.piscaLed = doc["piscaLed"];
    //     strlcpy(config.mqttServer, doc["MQTT_BROKER"], sizeof(config.mqttServer));
    //     config.mqttPort = doc["MQTT_PORT"];
    //     strlcpy(config.firebaseHost, doc["FIREBASE_HOST"], sizeof(config.firebaseHost));
    //     strlcpy(config.firebaseAuth, doc["FIREBASE_AUTH"], sizeof(config.firebaseAuth));
    // }