#include "Config.h"
#include "BlinkLed.h"
#include <Arduino.h>

Config config;

void blink() {
    digitalWrite(config.piscaLed, HIGH); // Liga o LED
    delay(500);                          // Espera 500 ms
    digitalWrite(config.piscaLed, LOW);  // Desliga o LED
    delay(500);                          // Espera 500 ms
}