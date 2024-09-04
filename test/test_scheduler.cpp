#include <Arduino.h>
#include <unity.h>
#include "../include/Scheduler.h"

void test_scheduler_initialization() {
    Scheduler::init();
    // Adicione verificações específicas da sua implementação de Scheduler
    TEST_ASSERT_TRUE(true);  // Exemplo de teste básico
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_scheduler_initialization);
    UNITY_END();
}

void loop() {
    // Deixe vazio para evitar reinicializações automáticas
}
