#include "Config.h"
#include "Blinkled.h"
#include <Arduino.h>

void blink() {

Config configblink;
    digitalWrite(configblink.piscaLed, HIGH); // Liga o LED
    delay(500);                          // Espera 500 ms
    digitalWrite(configblink.piscaLed, LOW);  // Desliga o LED
    delay(500);                          // Espera 500 ms
}