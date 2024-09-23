#ifndef CONFIG_H
#define CONFIG_H

#include <string.h>
#include <ESP8266WebServer.h>
#include <FS.h>

#define FORMAT_SPIFFS_IF_FAILED true

// Estrutura para armazenar as configurações
struct Config {

public:
    String wifiSSID = "";
    String wifiPassword = "";
    int piscaLed = 0;
    String mqttBroker = "" ;
    uint16_t mqttPort = 0;
    String mqttUser = "";
    String mqttPassword = "";
    String firebaseHost = "";
    String firebaseAuth = "";

};

// Declaração da função para carregar as configurações
bool loadConfig(Config &config);

#endif // CONFIG_H
