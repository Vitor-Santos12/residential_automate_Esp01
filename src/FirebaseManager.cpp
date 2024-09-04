#include <FS.h>                // SPIFFS library
#include <FirebaseESP8266.h>   // Firebase library for ESP8266
#include <ArduinoJson.h>       // JSON library
#include "FirebaseManager.h"

// Firebase objects
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// Variáveis para armazenar as credenciais carregadas do arquivo
String firebaseHost;
String firebaseAuth;
String wifiSSID;
String wifiPassword;

void FirebaseManager::init() {
    // Carregar variáveis de ambiente do arquivo secret.env
    loadEnvConfig();

    // Conectar ao Wi-Fi
    WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi.");

    // Configurar o Firebase
    config.host = firebaseHost.c_str();
    config.signer.tokens.legacy_token = firebaseAuth.c_str();

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    if (Firebase.ready()) {
        Serial.println("Firebase connected.");
    } else {
        Serial.println("Failed to connect to Firebase.");
    }
}

void FirebaseManager::loadEnvConfig() {
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

            if (key == "FIREBASE_HOST") firebaseHost = value;
            else if (key == "FIREBASE_AUTH") firebaseAuth = value;
            else if (key == "WIFI_SSID") wifiSSID = value;
            else if (key == "WIFI_PASSWORD") wifiPassword = value;
        }
        startIndex = endIndex + 1;
    }

    Serial.println("Environment variables loaded:");
    Serial.println("Firebase Host: " + firebaseHost);
    Serial.println("Firebase Auth: " + firebaseAuth);
    Serial.println("Wi-Fi SSID: " + wifiSSID);
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
