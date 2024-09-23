#include "WebServerAndOTAUpdate.h"
#include "WebServerModule.h"
#include "Config.h"
#include "OTAUpdate.h"
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ElegantOTA.h>

ESP8266WebServer server(80);

void WebServer::init() {
    server.on("/", []() {
        server.send(200, "text/html", "/index.html");
    });

    server.begin();
    Serial.println("Servidor web iniciado!");
}

void WebServer::handleClient() {
    server.handleClient();
}

void OTAUpdate::init() {
    ElegantOTA.begin(&server);
    server.begin();
}