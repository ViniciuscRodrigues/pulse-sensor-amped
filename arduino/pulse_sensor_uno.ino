/* Autor: Joel Murphy e Yury Gitman  || visite o site: http://www.pulsesensor.com
----------------------  Observações ----------------------
Para mais informações sobre o projeto acesse:
https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/README.md
 ---------------------------------------------------------
*/

#define PROCESSING_VISUALIZER 1
#define SERIAL_PLOTTER  2

// Definindo as Variáveis

int pulsePin = 0;                 // Pino de Dados do Sensor conectado a porta A0
int blinkPin = 13;                // Pino onde conectamos o LED (pino 13)
int fadePin = 5;                  // Pino onde será o conectado o LED do efeito 'Fade'
int fadeRate = 0;                 // Variavel para realizar o efeito 'Fade'

// Criação das variaveis voláteis usadas nas rotinas de interrupção

volatile int BPM;                   // Variável que vai armazenar o valor do A0 e atualiza a cada 2ms
volatile int Signal;                // Recebe os dados do sensor
volatile int IBI = 950;             // Essa variável vai determinar o intervlo de batidas
volatile boolean Pulse = false;     // "true" = detectou a pulsação.
volatile boolean QS = false;        // "true" = o Arduino encontrou uma pulsação de algo

static int outputType = SERIAL_PLOTTER;

void setup(){
  pinMode(blinkPin,OUTPUT);         // Declarando os leds como saída!
  pinMode(fadePin,OUTPUT);
  Serial.begin(115200);
  interruptSetup();                 // Ativa a função para fazer a leitura a cada 2ms
}

void loop(){
  serialOutput();

  if (QS == true){                    // Uma pulsação foi encontrada
     fadeRate = 255;                  // Faz o efeito 'Fade
     serialOutputWhenBeatHappens();
     QS = false;
  }

  ledFadeToBeat();                       // Faz o efeito 'Fade' acontecer
  delay(95);                             // Dê uma pausa
}

void ledFadeToBeat(){
  fadeRate -= 30;
  fadeRate = constrain(fadeRate,0,255);
  analogWrite(fadePin,fadeRate);
}
