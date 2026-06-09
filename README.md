# 🫀 Pulse Sensor Amped - Guia de Hardware, Processamento de Sinal & Interfaces (Arduino & ESP32)

[![Platform: Arduino](https://img.shields.io/badge/Platform-Arduino-pro.svg?style=flat-square&logo=arduino)](https://www.arduino.cc/)
[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32-blue.svg?style=flat-square&logo=espressif)](https://www.espressif.com/)
[![Status: Produção Acadêmica](https://img.shields.io/badge/Status-Documentado-success.svg?style=flat-square)]()

Este repositório contém a documentação técnica, análise de engenharia de firmware e guias de migração de arquitetura para o uso do **Pulse Sensor Amped**. O objetivo deste documento é servir como um manual completo para estudantes e entusiastas que desejam implementar processamento de sinal biométrico em tempo real e construir interfaces gráficas (GUIs).

---

## 🗺️ Índice
1. [Documentações e Fontes Originais](#-documentações-e-fontes-originais)
2. [Análise de Arquitetura do Código Base (Arduino)](#-análise-de-arquitetura-do-código-base-arduino)
3. [Migração de Arquitetura: Implementação no ESP32](#-migração-de-arquitetura-implementação-no-esp32)
4. [Construção de Interfaces Gráficas (GUI) no ESP32](#-construção-de-interfaces-gráficas-gui-no-esp32)
5. [Como Contribuir](#-como-contribuir)

---

## 🌐 Documentações e Fontes Originais

Para aprofundamento na física do sensor, calibração óptica e download das ferramentas oficiais de visualização, consulte as fontes que serviram de base para este projeto:

* **Portal Central do Projeto:** [PulseSensor Official Site](https://pulsesensor.com/)
* **Documentação de Hardware e Firmware:** [Repositório PulseSensor Amped Arduino](https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino)
* **Software de Interface para Desktop:** [PulseSensor Processing Visualizer GUI](https://github.com/WorldFamousElectronics/PulseSensor_Amped_Processing_Visualizer)
* **Guia de Referência de Engenharia:** [AutoCore Robótica - Blog de Aplicação](https://autocorerobotica.blog.br/utilizando-sensor-de-pulsos-com-arduino/)

---

## 🏗️ Análise de Arquitetura do Código Base (Arduino)

O firmware original (`pulsesensor.txt`) opera utilizando uma abordagem orientada a **Interrupções de Temporizador (Timer Interrupts)**. Isso remove o peso do processamento analógico do laço de execução principal (`loop()`), blindando a amostragem contra atrasos causados por funções bloqueantes.

### Diagrama de Pinagem Padrão
