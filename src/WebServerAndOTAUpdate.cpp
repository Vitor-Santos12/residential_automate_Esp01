#include "WebServerAndOTAUpdate.h"
/* #include "ESPAsyncWebServer.h" */
#include <ESPAsyncTCP.h>
#include "WebServerModule.h"
#include "MqttManager.h"
#include "Config.h"
#include "OTAUpdate.h"
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ElegantOTA.h>
#include <FS.h>

ESP8266WebServer server(80);
ESP8266WebServer WS("/WS");

/* AsyncWebServer server(80);
AsyncWebSocket ws("/ws"); */

MqttManagerset MqttWebServer;

bool ledState = 0;

const char index_html[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Automate Irrigation</title>
   <style>
    body {
    font-family: Arial, sans-serif;
    background-color: #f4f4f4;
    margin: 0;
    padding: 0;
    display: flex;
    justify-content: center;
    align-items: center;
    height: 100vh;
}

.container {
    background-color: #ffffff;
    padding: 20px;
    border-radius: 8px;
    box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
    width: 300px;
}

h1, h2 {
    text-align: center;
    color: #333;
}

label {
    display: block;
    margin-bottom: 5px;
    color: #555;
}

input, select, button {
    width: 100%;
    padding: 10px;
    margin-bottom: 15px;
    border: 1px solid #ccc;
    border-radius: 4px;
}

button {
    background-color: #28a745;
    color: #fff;
    cursor: pointer;
}

button:hover {
    background-color: #218838;
}

#status {
    text-align: center;
    color: #666;
}

   </style>
</head>
<body>
    <div class="container">
        <h1>Automate Irrigation</h1>
        
        <section>
            <h2>GPIO Control</h2>
            <div class="gpio-control">
                <label for="gpio-select">Select GPIO:</label>
                <select id="gpio-select">
                    <option value="0">LEDBUILTIN</option>
                </select>
                <button id="gpio-on" onclick="controlGPIO('on')">Turn ON</button>
                <button id="gpio-off" onclick="controlGPIO('off')">Turn OFF</button>
            </div>
        </section>

        <section>
            <h2>Schedule Irrigation</h2>
            <div class="schedule">
                <label for="start-time">Start Time:</label>
                <input type="datetime-local" id="start-time">
                
                <label for="end-time">End Time:</label>
                <input type="datetime-local" id="end-time">
                
                <label for="repeat">Repeat:</label>
                <select id="repeat">
                    <option value="daily">Daily</option>
                    <option value="weekly">Weekly</option>
                    <option value="monthly">Monthly</option>
                </select>
                <button onclick="scheduleIrrigation()">Set Schedule</button>
            </div>
        </section>

        <section>
            <h2>Status</h2>
            <div id="status">
                <p>Current GPIO Status: <span id="gpio-status">OFF</span></p>
                <p>Next Scheduled Start: <span id="next-schedule">None</span></p>
            </div>
        </section>
    </div>

    <script>

function controlGPIO(action) {
    const gpio = document.getElementById("gpio-select").value;
    
    // Enviar solicitação para o servidor
    fetch(`/gpio/${gpio}/${action}`)
        .then(response => response.json())
        .then(data => {
            document.getElementById("gpio-status").innerText = data.status ? "ON" : "OFF";
        })
        .catch(error => console.error('Error:', error));
}

function scheduleIrrigation() {
    const startTime = document.getElementById("start-time").value;
    const endTime = document.getElementById("end-time").value;
    const repeat = document.getElementById("repeat").value;

    const schedule = {
        startTime,
        endTime,
        repeat
    };

    // Enviar solicitação para agendar a irrigação
    fetch('/schedule', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(schedule),
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById("next-schedule").innerText = data.nextSchedule || "None";
    })
    .catch(error => console.error('Error:', error));
}

// Obter status inicial
function getStatus() {
    fetch('/status')
        .then(response => response.json())
        .then(data => {
            document.getElementById("gpio-status").innerText = data.gpioStatus ? "ON" : "OFF";
            document.getElementById("next-schedule").innerText = data.nextSchedule || "None";
        })
        .catch(error => console.error('Error:', error));
}

// Atualizar status ao carregar a página
window.onload = getStatus;

    </script>
</body>
</html>
)rawliteral";

void notifyClients() {
  WS.textAll(String(LED_BUILTIN));
}

/* void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "toggle") == 0) {
      ledState = !ledState;
      notifyClients();
    }
  }
} */

/* void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
} */

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if (ledState){
      return "ON";
    }
    else{
      return "OFF";
    }
  }
  return String();
}


void WebServer::init() { 
/*     // Handle root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
    }); */

    server.on("/", []() {
        // Send the plain text response
        server.send(200, "text/html", index_html);
    });


    //----------------------------
    /* initWebSocket(); */
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