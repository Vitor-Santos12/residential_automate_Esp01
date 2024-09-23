#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoJson.h>
#include <FS.h>

#define FORMAT_SPIFFS_IF_FAILED true

// Estrutura para armazenar as configurações
struct Config {
    char wifiSSID[32];
    char wifiPassword[64];
    int piscaLed = 13;
    String mqttBroker;
    uint16_t mqttPort;
    String mqttUser;
    String mqttPassword;
    char firebaseHost[64];
    char firebaseAuth[64];
};

// Declaração da função para carregar as configurações
bool loadConfig(Config &config);

#endif // CONFIG_H
