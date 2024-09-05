#include "../include/WifiManager.h"
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <FS.h>

char wifiSSID[32];
char wifiPassword[64];

void readSecrets() {
    if (!SPIFFS.begin()) {
        Serial.println("Falha ao montar o sistema de arquivos");
        return;
    }

    File file = SPIFFS.open("/secret.env", "r");
    if (!file) {
        Serial.println("Falha ao abrir o arquivo secret.env");
        return;
    }

    size_t size = file.size();
    std::unique_ptr<char[]> buf(new char[size]);

    file.readBytes(buf.get(), size);
    file.close();

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, buf.get());

    if (error) {
        Serial.println("Falha ao analisar o arquivo secret.env");
        return;
    }

    strlcpy(wifiSSID, doc["WIFI_SSID"], sizeof(wifiSSID));
    strlcpy(wifiPassword, doc["WIFI_PASSWORD"], sizeof(wifiPassword));
}

void WifiManager::init() {
    readSecrets();
    WiFi.begin(wifiSSID, wifiPassword);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando ao Wi-Fi...");
    }
    Serial.println("Conectado ao Wi-Fi!");
}

void WifiManager::update() {
    // Código para manter a conexão Wi-Fi
    if (WiFi.status() != WL_CONNECTED) {
        init();
    }
}


