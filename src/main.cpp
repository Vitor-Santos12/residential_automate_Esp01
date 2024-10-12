#include "Config.h"
#include "WebServerAndOTAUpdate.h"
#include "MqttManager.h"
/* #include "FirebaseManager.h"*/
#include "GpioControl.h"
#include "Scheduler.h"
#include "OTAUpdate.h"
#include "WebServerModule.h"
#include "RealTimeClock.h"
#include "RTOSManager.h"
#include "Blinkled.h"

Config ConfigMain;

MqttManagerset Mqtt;

void setup() {
    Serial.begin(115200);
  
/*     if (!loadConfig(configurator)) {
        Serial.println("Falha ao carregar as configurações");
        while (true);
    } */
    
    // Inicializa Wi-Fi
    WifiManager::init();

    // Inicializa MQTT
    Mqtt.init(ConfigMain.espClient);
    Mqtt.connect();

    // Inicializa Firebase
    /* FirebaseManager::init(); */
 
    // Inicializa GPIO
    GpioControl GPIO;
    GPIO.init();

    // Inicializa OTA Update
    OTAUpdate::init();

    // Inicializa Web Server
    WebServer::init();

/*     // Inicializa RTC
    RealTimeClock::init();

    // Inicializa Scheduler
    Scheduler::init();

    // Inicializa RTOS Manager
    RTOSManager::init(); */
}

/* bool teste = true; */

void loop() {
    // Atualiza o Watchdog
    ESP.wdtFeed();

    Serial.println("\nMQTT values:");
    Serial.println("Broker: " + ConfigMain.mqttBroker);
    Serial.println("Port: " + String(ConfigMain.mqttPort));
/*     Serial.println("User: " + configurator.mqttUser);
    Serial.println("Port: " + configurator.mqttPassword); */

    Serial.println("\nFirebase values");
    Serial.println("Host: " + ConfigMain.firebaseHost);
    Serial.println("Auth: " + ConfigMain.firebaseAuth);
    
    Serial.println("\nWifi Values");
    Serial.println("wifiSSID: " + ConfigMain.wifiSSID);
    Serial.println("wifiPassword: ********");

    // Atualiza os módulos
/*     Mqtt.loop(); */
    Mqtt.publish("esp01-8266/output","teste1");

    Mqtt.subscribe("esp01-8266/output");

/*     FirebaseManager::update();
    Scheduler::update();
    WebServer::handleClient();
    RTOSManager::runTasks(); */

    blink();
}
