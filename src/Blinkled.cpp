#include "Config.h"
#include "Blinkled.h"
#include <Arduino.h>
#include <PubSubClient.h>
#include <MqttManager.h>

MqttManagerset Mqttblink;

void blink() {

Config configblink;
    digitalWrite(LED_BUILTIN, HIGH); // Liga o LED
    Mqttblink.publish("esp01-8266/output", "LED: ON");
    Serial.println("LED: ON");
    delay(10000);                          // Espera 10000 ms
    digitalWrite(LED_BUILTIN, LOW);  // Desliga o LED
    Mqttblink.publish("esp01-8266/output", "LED: OFF");
    Serial.println("LED: OFF");
    delay(10000);                          // Espera 10000 ms
}
