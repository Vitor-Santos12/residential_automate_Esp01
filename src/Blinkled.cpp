#include "Config.h"
#include "Blinkled.h"
#include <Arduino.h>
#include <PubSubClient.h>
#include <MqttManager.h>

MqttManagerset Mqttblink;
Config configblink;

void blink(int time_delay) {
    digitalWrite(LED_BUILTIN, HIGH); // Liga o LED
    Mqttblink.publish("esp01-8266/output", "LED: ON");
    Serial.println("LED: ON");
    delay(time_delay);                          // Espera 1000 ms
    digitalWrite(LED_BUILTIN, LOW);  // Desliga o LED
    Mqttblink.publish("esp01-8266/output", "LED: OFF");
    Serial.println("LED: OFF");
    delay(time_delay);                          // Espera 1000 ms
}
