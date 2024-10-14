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

#include <ElegantOTA.h>

Config ConfigMain;

GpioControl GPIO;

MqttManagerset Mqtt;

// Timers auxiliar variables
long now = millis();
long lastMeasure = 0;

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

    if (now - lastMeasure > 3000) {
    lastMeasure = now;
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float humidity = 1001+(rand())%4000;
    // Read temperature as Celsius (the default)
    float temperatureC = 1001+(rand())%4000;
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float temperatureF = 1001+(rand())%4000;

    // Publishes Temperature and Humidity values
    Mqtt.publish("esp01-8266/output/temperature", String(temperatureC).c_str());
    Mqtt.publish("esp01-8266/output/humidity", String(humidity).c_str());
    Mqtt.publish("esp01-8266/output", "Atualização pelo ElegantOTA");
    
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println(" ºC");
    Serial.print(temperatureF);
    Serial.println(" ºF");
  }

    
    // Atualiza os módulos
    Mqtt.loop();
    WebServer::handleClient();
    ElegantOTA.loop();
/*     FirebaseManager::update();
    Scheduler::update();
    WebServer::handleClient();
    RTOSManager::runTasks(); */
    blink(1000);
}
