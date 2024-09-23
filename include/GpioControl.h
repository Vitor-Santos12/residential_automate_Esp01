#ifndef GPIOCONTROL_H
#define GPIOCONTROL_H

#include <Arduino.h>

class GpioControl {

public:
    GpioControl();
    void init();
    void setPinMode(uint8_t pin, uint8_t mode);
    void write(uint8_t pin, uint8_t state);
    int read(uint8_t pin);

    // Definição dos pinos do ESP01-8266
    static const uint8_t GPIO0 = 0; // Pin 3
    static const uint8_t GPIO2 = 2; // Pin 4

};

#endif