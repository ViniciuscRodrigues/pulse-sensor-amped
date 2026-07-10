#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <SPIFFS.h> // Para ler o HTML da memória flash

const char* ssid = "NOME_DA_SUA_REDE";
const char* password = "SUA_SENHA_WIFI";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Pinos do ESP32
const int pulsePin = 36; // VP
const int blinkPin = 2;  // LED Onboard

// Variáveis de controle
int signalValue = 0;
int bpm = 72;
int ibi = 800;
unsigned long lastSampleTime = 0;
const int sampleInterval = 2; // 2ms = 500Hz
unsigned long lastWsSend = 0;

void notifyClients() {
  String json = "{\"signal\":" + String(signalValue) + ",\"bpm\":" + String(bpm) + ",\"ibi\":" + String(ibi) + "}";
  ws.textAll(json);
}

void tratarSinalSensor() {
  signalValue = analogRead(pulsePin);

  // Aqui você pode integrar um algoritmo real de detecção de picos (Threshold)
  // Para fins de demonstração da GUI, estamos enviando o sinal bruto e BPM fixo

  if(millis() - lastWsSend > 20) { // Atualiza a GUI a cada 20ms
    notifyClients();
    lastWsSend = millis();
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(blinkPin, OUTPUT);
  analogSetAttenuation(ADC_11db); // Permite ler de 0 a 3.3V (0-4095)

  // Inicializa o sistema de arquivos (LittleFS/SPIFFS)
  if(!SPIFFS.begin(true)){
    Serial.println("Erro ao montar o SPIFFS");
    return;
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado! IP: " + WiFi.localIP().toString());

  // WebSocket
  ws.onEvent([](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len){});
  server.addHandler(&ws);

  // Rota para servir o index.html salvo na pasta /data do ESP32
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.begin();
}

void loop() {
  ws.cleanupClients();

  if (millis() - lastSampleTime >= sampleInterval) {
    lastSampleTime = millis();
    tratarSinalSensor();
  }
}
