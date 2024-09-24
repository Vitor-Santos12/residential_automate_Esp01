#include "Config.h"
#include "WebServerAndOTAUpdate.h"
/* #include "MqttManager.h" */
/* #include "FirebaseManager.h"*/
#include "GpioControl.h"
#include "Scheduler.h"
#include "OTAUpdate.h"
#include "WebServerModule.h"
#include "RealTimeClock.h"
#include "RTOSManager.h"
#include "Blinkled.h"


// MQTT de maneira simples
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

Config configurator;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "esp01-8266/output") {
    Serial.print("Changing output to ");
    if (messageTemp == "on") {
      Serial.println("on");
      digitalWrite(configurator.piscaLed, HIGH);
    } else if (messageTemp == "off") {
      Serial.println("off");
      digitalWrite(configurator.piscaLed, LOW);
    }
  }
}

void setup() {
    Serial.begin(115200);

    if (!loadConfig(configurator)) {
        Serial.println("Falha ao carregar as configurações");
        while (true);
    }
    
    // Inicializa Wi-Fi
    WifiManager::init();

      // Configura o WiFi e o cliente MQTT
    client.setServer(configurator.mqttBroker.c_str(), configurator.mqttPort);
    client.setCallback(callback);

    // Inicializa MQTT
 /*    MqttManagerset Mqtt;
    Mqtt.init();
    Mqtt.connect();
 */
    // Inicializa Firebase
    /* FirebaseManager::init(); */

    // Inicializa GPIO
    GpioControl GPIO;
    GPIO.init();

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
    // Mqtt.loop();
    // FirebaseManager::update();
    Scheduler::update();
    WebServer::handleClient();
    RTOSManager::runTasks();
    // ** Pisca Led Funcionou
        blink();
    // Realiza um delay de 1 segundo
        delay(1000);
}
