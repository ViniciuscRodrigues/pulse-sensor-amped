#ifndef WEBSERVER_HANDLER_H
#define WEBSERVER_HANDLER_H

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

// Classe responsável por toda a comunicação em rede e interface gráfica
class WebServerHandler {
private:
    const char* ssid;
    const char* password;
    AsyncWebServer server;
    AsyncWebSocket ws;

public:
    WebServerHandler(const char* wifiSSID, const char* wifiPASS);
    
    void begin();
    void loop(); // Limpeza de clientes desligados
    
    // Empacota e envia os dados via WebSocket para a GUI
    void broadcastData(int signal, int bpm, int ibi);
};

#endif // WEBSERVER_HANDLER_H
