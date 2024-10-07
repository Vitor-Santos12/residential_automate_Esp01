#include "GpioControl.h"

GpioControl::GpioControl() {
    // Construtor, caso queira inicializar algo específico
}

void GpioControl::init() {
    // Inicialização dos pinos como INPUT por padrão
    setPinMode(GPIO0, OUTPUT);
    setPinMode(GPIO2, OUTPUT);

    // Set up output pin
    digitalWrite(GPIO0, HIGH);
    digitalWrite(GPIO2, HIGH);
}

void GpioControl::setPinMode(uint8_t pin, uint8_t mode) {
    pinMode(pin, mode);
}

void GpioControl::write(uint8_t pin, uint8_t state) {
    digitalWrite(pin, state);
}

int GpioControl::read(uint8_t pin) {
    return digitalRead(pin);
}
