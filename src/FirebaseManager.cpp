/* #include <FS.h>                // SPIFFS library
#include <FirebaseESP8266.h>   // Firebase library for ESP8266
#include <ArduinoJson.h>       // JSON library
#include "FirebaseManager.h"

// Config configFirebase;

void FirebaseManager::init() {

// Conectar ao Wi-Fi
    WiFi.begin(configFirebase.wifiSSID.c_str(), configFirebase.wifiPassword.c_str());
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi.");

    // Configurar o Firebase
    config.host = configFirebase.firebaseHost.c_str();
    config.signer.tokens.legacy_token = configFirebase.firebaseAuth.c_str();

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    if (Firebase.ready()) {
        Serial.println("Firebase connected.");
    } else {
        Serial.println("Failed to connect to Firebase.");
    }
}

bool FirebaseManager::sendData(const String &path, const String &json) {
   if (Firebase.pushJSON(firebaseData, path, json)) {
        Serial.println("Data sent successfully");
        return true;
    } else {
        Serial.println("Failed to send data: " + firebaseData.errorReason());
        return false;
    }
}

String FirebaseManager::getData(const String &path) {
       String data;
   if (Firebase.getString(firebaseData, path)) {
        data = firebaseData.stringData();
        Serial.println("Data retrieved: " + data);
    } else {
        Serial.println("Failed to retrieve data: " + firebaseData.errorReason());
    }
    return data;
}
 */