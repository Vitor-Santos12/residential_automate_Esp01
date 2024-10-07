#include "Config.h"
#include "WebServerAndOTAUpdate.h"
/* #include "MqttManager.h" */
/* #include "FirebaseManager.h"*/
#include "GpioControl.h"
#include "Scheduler.h"
// #include "OTAUpdate.h"
#include "WebServerModule.h"
#include "RealTimeClock.h"
#include "RTOSManager.h"
#include "Blinkled.h"


// MQTT de maneira simples
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

void reconnect();

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
    delay(10);

    Serial.print("MQTT_BROKER :");
    Serial.println(configurator.mqttBroker);
    Serial.print("LED_PISCALED :");
    Serial.println(configurator.piscaLed);
    Serial.print("WIFI_SSID :");
    Serial.println(configurator.wifiSSID);


    WiFi.begin("HELOISA_2G", "jujuba2910");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando ao Wi-Fi...");
        Serial.print("WIFI_SSID :");
        Serial.println(configurator.wifiSSID);
    }
    Serial.println("Conectado ao Wi-Fi!");
    Serial.print("WIFI_SSID :");
    Serial.println(configurator.wifiSSID);
    
    // // Inicializa Wi-Fi
    // WifiManager::init();

    // // Inicializa Web Server
    // WebServer::init();

    // Configura o WiFi e o cliente MQTT
    client.setServer("test.mosquitto.org", 1883);
    client.setCallback(callback);

    // Inicializa MQTT
    // MqttManagerset Mqtt;
    // Mqtt.init();
    // Mqtt.connect();

    // Inicializa Firebase
    /* FirebaseManager::init(); */

    // Inicializa GPIO
    GpioControl GPIO;
    GPIO.init();

    // Inicializa RTC
    // RealTimeClock::init();

    // Inicializa OTA Update
    // OTAUpdate::init();

    // Inicializa Scheduler
    // Scheduler::init();

    // Inicializa RTOS Manager
    // RTOSManager::init();

    // Atualiza o Watchdog
    // ESP.wdtDisable();
}

void loop() {
    // Atualiza o Watchdog
    ESP.wdtFeed();

    // Atualiza os módulos
    // Mqtt.loop();

    // Mantém o cliente MQTT ativo
    if (!client.connected()) {
        reconnect();  // Função para reconectar ao MQTT se desconectado
    }
    client.loop();  // Mantém a conexão MQTT

    // FirebaseManager::update();
    // Scheduler::update();
    // WebServer::handleClient();
    // RTOSManager::runTasks();
    // ** Pisca Led Funcionou
    blink();
    // Realiza um delay de 1 segundo
    // delay(1000);
}

// Função para reconectar ao MQTT
void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Tente se conectar ao servidor MQTT
        if (client.connect("ESP8266Client")) {
            Serial.println("connected");
            // Subscreva no tópico desejado
            client.subscribe("esp01-8266/output");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Aguarde 5 segundos antes de tentar novamente
            delay(5000);
        }
    }
}
