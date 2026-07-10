#ifndef SENSOR_PROCESSING_H
#define SENSOR_PROCESSING_H

#include <Arduino.h>

// Classe responsável exclusivamente por ler e processar o sinal biométrico
class SensorProcessing {
private:
    uint8_t pin;
    int threshold;
    int currentSignal;
    int currentBPM;
    int currentIBI;
    
    unsigned long lastBeatTime;
    bool pulseDetected;

public:
    SensorProcessing(uint8_t analogPin);
    
    void begin();
    void update(); // Chamada periodicamente para ler o sensor
    
    // Getters para encapsulamento de dados
    int getSignal() const;
    int getBPM() const;
    int getIBI() const;
    bool isPulseDetected() const;
    void resetPulseFlag();
};

#endif // SENSOR_PROCESSING_H
