#include "../include/WifiManager.h"
#include "../include/Config.h"
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <FS.h>

void WifiManager::init() {
// Recieve configuration values
Config config;

    WiFi.begin(config.wifiSSID, config.wifiPassword);
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


