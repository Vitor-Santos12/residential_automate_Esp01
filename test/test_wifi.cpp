#include <Arduino.h>
#include <unity.h>
#include "../include/WifiManager.h"

void test_wifi_connect() {
    WifiManager::init();
    TEST_ASSERT_EQUAL(WL_CONNECTED, WiFi.status());
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_wifi_connect);
    UNITY_END();
}

void loop() {
    // Deixe vazio para evitar reinicializações automáticas
}
