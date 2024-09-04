#include <Arduino.h>
#include <unity.h>
#include "../include/GpioControl.h"

void test_gpio_init() {
    GpioControl::init();
    TEST_ASSERT_EQUAL(OUTPUT, getPinMode(GPIO2_PIN));
}

void test_gpio_on_off() {
    GpioControl::setGpioState(GPIO2_PIN, true);
    TEST_ASSERT_EQUAL(HIGH, GpioControl::getGpioState(GPIO2_PIN));
    
    GpioControl::setGpioState(GPIO2_PIN, false);
    TEST_ASSERT_EQUAL(LOW, GpioControl::getGpioState(GPIO2_PIN));
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_gpio_init);
    RUN_TEST(test_gpio_on_off);
    UNITY_END();
}

void loop() {
    // Deixe vazio para evitar reinicializações automáticas
}
