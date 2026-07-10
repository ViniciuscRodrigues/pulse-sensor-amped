#include "SensorProcessing.h"

// Construtor: Inicializa as variáveis com valores padrão
SensorProcessing::SensorProcessing(uint8_t analogPin) {
    pin = analogPin;
    threshold = 2000; // Limiar ajustado para o ADC de 12 bits do ESP32 (0-4095)
    currentSignal = 0;
    currentBPM = 0;
    currentIBI = 0;
    lastBeatTime = 0;
    pulseDetected = false;
}

// Configuração inicial do pino analógico
void SensorProcessing::begin() {
    // Configura a atenuação para leitura de até 3.3V no ESP32
    analogSetAttenuation(ADC_11db);
    pinMode(pin, INPUT);
}

// Lógica de leitura e deteção de pico (Crista da onda do pulso)
void SensorProcessing::update() {
    currentSignal = analogRead(pin);
    unsigned long currentTime = millis();

    // Algoritmo simplificado de deteção de pico (Thresholding)
    if (currentSignal > threshold && !pulseDetected && (currentTime - lastBeatTime > 250)) {
        // Encontrou um batimento
        pulseDetected = true;
        currentIBI = currentTime - lastBeatTime;
        lastBeatTime = currentTime;
        
        // Cálculo do BPM baseado no intervalo do último batimento
        if (currentIBI > 0) {
            currentBPM = 60000 / currentIBI;
        }
    } 
    
    // Repõe a deteção quando o sinal cai abaixo do limiar
    if (currentSignal < threshold) {
        pulseDetected = false;
    }
}

// Métodos de acesso (Getters)
int SensorProcessing::getSignal() const { return currentSignal; }
int SensorProcessing::getBPM() const { return currentBPM; }
int SensorProcessing::getIBI() const { return currentIBI; }
bool SensorProcessing::isPulseDetected() const { return pulseDetected; }
void SensorProcessing::resetPulseFlag() { pulseDetected = false; }
