#ifndef CONFIG_H
#define CONFIG_H

#include <string.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
/* #include <FS.h> */

#define FORMAT_SPIFFS_IF_FAILED true

// Estrutura para armazenar as configurações
struct Config {

public:
    String wifiSSID = "Ubuntu";
    String wifiPassword = "v1234567";
    String mqttBroker = "test.mosquitto.org";
    int mqttPort = 1883;
    String mqttUser = "";
    String mqttPassword = "";
    String firebaseHost = "";
    String firebaseAuth = "";

    WiFiClient espClient;

};

// Declaração da função para carregar as configurações
/* bool loadConfig(Config &config); */

#endif // CONFIG_H
