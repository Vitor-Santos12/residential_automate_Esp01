#include <Arduino.h>
#include <unity.h>
#include "../include/MqttManager.h"

void test_mqtt_connect() {
    MqttManager::init();
    TEST_ASSERT_TRUE(client.connected());
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_mqtt_connect);
    UNITY_END();
}

void loop() {
    // Deixe vazio para evitar reinicializações automáticas
}
