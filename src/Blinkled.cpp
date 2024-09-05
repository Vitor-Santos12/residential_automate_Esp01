#include "BlinkLed.h"
#include <Arduino.h>

const int ledPin = 13; // Defina o pino do LED

void blink() {
    digitalWrite(ledPin, HIGH); // Liga o LED
    delay(500);                 // Espera 500 ms
    digitalWrite(ledPin, LOW);  // Desliga o LED
    delay(500);                 // Espera 500 ms
}