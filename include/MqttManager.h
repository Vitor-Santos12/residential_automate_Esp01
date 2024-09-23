#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include <PubSubClient.h>

class MqttManager {
public:
    MqttManager();
    void init(Client &client);
    void connect();
    void publish(const char* topic, const char* payload);
    void subscribe(const char* topic);
    void loop();

private:
    void loadEnvConfig();

    String mqttBroker;
    uint16_t mqttPort;
    String mqttUser;
    String mqttPassword;

    PubSubClient mqttClient;
};

#endif
