#include "../include/Config.h"
// #include "../include/Secrets.h"
// #include "../include/WifiManager.h"
// #include "../include/MqttManager.h"
// #include "../include/FirebaseManager.h"
#include "../include/GpioControl.h"
// #include "../include/Scheduler.h"
// #include "../include/OTAUpdate.h"
// #include "../include/WebServerModule.h"
// #include "../include/RealTimeClock.h"
// #include "../include/RTOSManager.h"

#include "BlinkLed.h"

Config configurator;

void setup() {
    Serial.begin(115200);

    if (!loadConfig(configurator)) {
        Serial.println("Falha ao carregar as configurações");
        while (true);
    }

    Serial.print("SSID: ");
    Serial.println(configurator.wifiSSID);
    Serial.print("Password: ");
    Serial.println(configurator.wifiPassword);
    Serial.print("Pisca LED: ");
    Serial.println(configurator.piscaLed);
    Serial.print("MQTT Server: ");
    Serial.println(configurator.mqttServer);
    Serial.print("MQTT Port: ");
    Serial.println(configurator.mqttPort);
    Serial.print("Firebase Host: ");
    Serial.println(configurator.firebaseHost);
    Serial.print("Firebase Auth: ");
    Serial.println(configurator.firebaseAuth);
    
    // Inicializa Wi-Fi
    // WifiManager::init();

    // Inicializa MQTT
    // MqttManager::init();
    // MqttManager::connect();

    // Inicializa Firebase
    // FirebaseManager::init();

    // Inicializa GPIO
    // GpioControl::init();

    // Inicializa RTC
    // RealTimeClock::init();

    // Inicializa OTA Update
    // OTAUpdate::init();

    // Inicializa Web Server
    // WebServer::init();

    // Inicializa Scheduler
    // Scheduler::init();

    // Inicializa RTOS Manager
    // RTOSManager::init();
}

void loop() {
    // Atualiza o Watchdog
    ESP.wdtFeed();

    // Atualiza os módulos
    // MqttManager::update();
    // MqttManager::loop();
    // FirebaseManager::update();
    // Scheduler::update();
    // WebServer::handleClient();
    // OTAUpdate::handleUpdate();
    // RTOSManager::runTasks();

    blink();
    // Realiza um delay de 1 segundo
    delay(1000);
}
