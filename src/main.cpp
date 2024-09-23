#include "Config.h"
#include "WebServerAndOTAUpdate.h"
#include "MqttManager.h"
// #include "FirebaseManager.h"
#include "GpioControl.h"
#include "Scheduler.h"
#include "OTAUpdate.h"
#include "WebServerModule.h"
#include "RealTimeClock.h"
#include "RTOSManager.h"

#include "BlinkLed.h"

Config configurator;

void setup() {
    Serial.begin(115200);

    if (!loadConfig(configurator)) {
        Serial.println("Falha ao carregar as configurações");
        while (true);
    }
    
    // Inicializa Wi-Fi
    WifiManager::init();

    // Inicializa MQTT
    // MqttManager::init();
    // MqttManager::connect();

    // Inicializa Firebase
    // FirebaseManager::init();

    // Inicializa GPIO
    // GpioControl::init();

    // Inicializa RTC
    RealTimeClock::init();

    // Inicializa OTA Update
    OTAUpdate::init();

    // Inicializa Web Server
    WebServer::init();

    // Inicializa Scheduler
    Scheduler::init();

    // Inicializa RTOS Manager
    RTOSManager::init();
}

void loop() {
    // Atualiza o Watchdog
    // ESP.wdtFeed();

    // Atualiza os módulos
    // MqttManager::loop();
    // FirebaseManager::update();
        Scheduler::update();
        WebServer::handleClient();
        RTOSManager::runTasks();
    // ** Pisca Led Funcionou
        blink();
    // Realiza um delay de 1 segundo
        delay(1000);
}
