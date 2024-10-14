#include <FS.h>
#include <PubSubClient.h>
#include "MqttManager.h"
#include "Config.h"
#include "GpioControl.h"

Config configMqttManager;

MqttManagerset Mqttset;

GpioControl MqttGPIO;

void MqttManagerset::callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    messageTemp += (char)payload[i];
  }
  Serial.println();
  Serial.println("-----------------------");

  if(topic=="esp01-8266/output/lamp"){
      Serial.print("Changing Room lamp to ");
      if(messageTemp == "on"){
        MqttGPIO.write(MqttGPIO.GPIO0, HIGH);
        MqttGPIO.write(MqttGPIO.GPIO2, HIGH);
        Mqttset.publish("esp01-8266/output", "GPIO:HIGH");
        Serial.print(" on");
      }
      else if(messageTemp == "off"){
        MqttGPIO.write(MqttGPIO.GPIO0, LOW);
        MqttGPIO.write(MqttGPIO.GPIO2, LOW);
        Mqttset.publish("esp01-8266/output", "GPIO:LOW");
        Serial.print("off");
      }
  }
  Serial.println();
}


void MqttManagerset::init(Client &client) {

    mqttClient.setClient(client);

    mqttClient.setServer(configMqttManager.mqttBroker.c_str(), configMqttManager.mqttPort);

    return;
}

void MqttManagerset::connect() {

    while (!mqttClient.connected()) {
        Serial.println("Connecting to MQTT...");

        if (mqttClient.connect("House Automate", configMqttManager.mqttUser.c_str(), configMqttManager.mqttPassword.c_str())) {
            Serial.println("Connected to MQTT broker");
        } else {
            Serial.print("Failed to connect, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void MqttManagerset::publish(const char* topic, const char* payload) {
    mqttClient.publish(topic, payload);
}

void MqttManagerset::subscribe(const char* topic) {
    mqttClient.subscribe(topic);
}

void MqttManagerset::loop() {
    mqttClient.loop();
}