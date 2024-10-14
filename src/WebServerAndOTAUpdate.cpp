#include "WebServerAndOTAUpdate.h"
#include "WebServerModule.h"
#include "MqttManager.h"
#include "Config.h"
#include "OTAUpdate.h"
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ElegantOTA.h>
#include <FS.h>

ESP8266WebServer server(80);

MqttManagerset MqttWebServer;

void WebServer::init() { 
    // Handle root URL
    server.on("/", []() {
        // Send the plain text response
        server.send(200, "text/plain", "Hi! This is ElegantOTA Demo.");

        // Send the index.html file (assuming it is served from SPIFFS or LittleFS)
        if (SPIFFS.exists("index.html")) {
            File file = SPIFFS.open("index.html", "r");
            server.streamFile(file, "text/html");
            file.close();
        } else {
            server.send(404, "text/plain", "index.html not found");
        }

        // Publish MQTT message
        MqttWebServer.publish("esp01-8266/output", "Online!");
    });

    // Start the web server
    server.begin();
    Serial.println("Servidor web iniciado!");

    // Publish MQTT message indicating the server started
    MqttWebServer.publish("esp01-8266/output", "Servidor web iniciado!");
}
void WebServer::handleClient() {
    server.handleClient();
}

void OTAUpdate::init() {
    ElegantOTA.begin(&server);
    server.begin();
    Serial.println("HTTP server started");
    MqttWebServer.publish("esp01-8266/output","OTA:HTTP server started");
}