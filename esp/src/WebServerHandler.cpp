#include "WebServerHandler.h"

WebServerHandler::WebServerHandler(const char* wifiSSID, const char* wifiPASS) 
    : server(80), ws("/ws") {
    ssid = wifiSSID;
    password = wifiPASS;
}

void WebServerHandler::begin() {
    // 1. Inicializa o sistema de ficheiros para ler o HTML
    if (!LittleFS.begin(true)) {
        Serial.println("Erro ao montar LittleFS");
        return;
    }

    // 2. Liga ao Wi-Fi
    WiFi.begin(ssid, password);
    Serial.print("A ligar ao WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nLigado! IP da Interface: " + WiFi.localIP().toString());

    // 3. Configura rotas do Servidor Web
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/index.html", "text/html");
    });

    // 4. Configura WebSockets
    ws.onEvent([](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len){
        if(type == WS_EVT_CONNECT){
            Serial.printf("Cliente %u ligado\n", client->id());
        }
    });
    server.addHandler(&ws);

    // Inicia o servidor
    server.begin();
}

void WebServerHandler::broadcastData(int signal, int bpm, int ibi) {
    // Cria um payload JSON otimizado
    StaticJsonDocument<128> doc;
    doc["signal"] = signal;
    doc["bpm"] = bpm;
    doc["ibi"] = ibi;

    char buffer[128];
    serializeJson(doc, buffer);
    
    // Envia para todos os navegadores ligados
    ws.textAll(buffer);
}

void WebServerHandler::loop() {
    ws.cleanupClients();
}
