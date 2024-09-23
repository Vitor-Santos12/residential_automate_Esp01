#include "../include/WebServerModule.h"

#include <ESP8266WebServer.h>

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
