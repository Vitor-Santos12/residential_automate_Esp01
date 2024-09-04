#include "../include/WifiManager.h"
#include <ESP8266WiFi.h>

void WifiManager::init() {
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


