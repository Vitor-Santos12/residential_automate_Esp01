/* #ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include <PubSubClient.h>

class MqttManagerset {
public:
    void init(Client &client);
    void connect();
    void publish(const char* topic, const char* payload);
    void subscribe(const char* topic);
    void loop();

    PubSubClient mqttClient;
};

#endif */
