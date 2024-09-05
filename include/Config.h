#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoJson.h>
#include <FS.h>

// Estrutura para armazenar as configurações
struct Config {
    char wifiSSID[32];
    char wifiPassword[64];
    int piscaLed;
    char mqttServer[64];
    int mqttPort;
    char firebaseHost[64];
    char firebaseAuth[64];
};

// Declaração da função para carregar as configurações
bool loadConfig(Config &config);

#endif // CONFIG_H
