#include "../include/OTAUpdate.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ElegantOTA.h>

ESP8266WebServer server(80);

void OTAUpdate::init() {
    ElegantOTA.begin(&server);
    server.begin();
}

void OTAUpdate::handleUpdate() {
    server.handleClient();
}
