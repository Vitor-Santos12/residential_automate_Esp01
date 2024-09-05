// #include "../include/RealTimeClock.h"
// #include <NTPClient.h>
// #include <WiFiUdp.h>

// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, "pool.ntp.org");

// void RealTimeClock::init() {
//     timeClient.begin();
//     timeClient.setTimeOffset(-10800);  // Ajuste de fuso horário
// }

// void RealTimeClock::update() {
//     timeClient.update();
// }

// String RealTimeClock::getFormattedTime() {
//     return timeClient.getFormattedTime();
// }
