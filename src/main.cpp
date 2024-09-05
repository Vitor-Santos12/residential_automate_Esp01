#include "../include/Config.h"
#include "../include/Secrets.h"
#include "../include/WifiManager.h"
#include "../include/MqttManager.h"
#include "../include/FirebaseManager.h"
#include "../include/GpioControl.h"
#include "../include/Scheduler.h"
#include "../include/OTAUpdate.h"
#include "../include/WebServerModule.h"
#include "../include/RealTimeClock.h"
#include "../include/RTOSManager.h"
#include "BlinkLed.h"

void setup() {
    Serial.begin(115200);
    
    // Inicializa Wi-Fi
    WifiManager::init();

    // Inicializa MQTT
    MqttManager::init();
    MqttManager::connect();

    // Inicializa Firebase
    // FirebaseManager::init();

    // Inicializa GPIO
    GpioControl::init();

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
    MqttManager::update();
    MqttManager::loop();
    // FirebaseManager::update();
    // Scheduler::update();
    // WebServer::handleClient();
    // OTAUpdate::handleUpdate();
    // RTOSManager::runTasks();

    blink();
    // Realiza um delay de 1 segundo
    delay(1000);
}
