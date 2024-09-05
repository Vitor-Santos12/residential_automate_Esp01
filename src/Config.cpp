#include "Config.h"

bool loadConfig(Config &config) {
    if (!SPIFFS.begin()) {
        Serial.println("Falha ao montar o sistema de arquivos");
        return false;
    }

    File file = SPIFFS.open("/secret.env", "r");
    if (!file) {
        Serial.println("Falha ao abrir o arquivo secret.env");
        return false;
    }

    size_t size = file.size();
    std::unique_ptr<char[]> buf(new char[size]);

    file.readBytes(buf.get(), size);
    file.close();

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, buf.get());

    if (error) {
        Serial.println("Falha ao analisar o arquivo secret.env");
        return false;
    }

    strlcpy(config.wifiSSID, doc["WIFI_SSID"], sizeof(config.wifiSSID));
    strlcpy(config.wifiPassword, doc["WIFI_PASSWORD"], sizeof(config.wifiPassword));
    config.piscaLed = doc["piscaLed"];
    strlcpy(config.mqttServer, doc["mqttServer"], sizeof(config.mqttServer));
    config.mqttPort = doc["mqttPort"];
    strlcpy(config.firebaseHost, doc["FIREBASE_HOST"], sizeof(config.firebaseHost));
    strlcpy(config.firebaseAuth, doc["FIREBASE_AUTH"], sizeof(config.firebaseAuth));

    return true;
}