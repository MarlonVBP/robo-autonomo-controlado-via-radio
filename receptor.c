#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define BAUD_RATE 9600
#define CE_PIN 9
#define CSN_PIN 10
#define MAX_MESSAGE_LENGTH 32

#define IN1_M1 2
#define IN2_M1 3
#define IN3_M1 4
#define IN4_M1 5
#define IN1_M2 6
#define IN2_M2 7
#define IN3_M2 8
#define IN4_M2 A0

const int steps[8][4] = {
  {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0},
  {0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {1, 0, 0, 1}
};

const int direcoes[2][4] = {
  {0, 1, 2, 3},
  {3, 2, 1, 0} 
};

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";

void setup() {
  Serial.begin(BAUD_RATE);
  while (!Serial);

  if (!radio.begin()) {
    Serial.println(F("Erro: Falha ao inicializar o nRF24L01!"));
    while (1);
  }

  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
  Serial.println(F("Receptor inicializado com sucesso."));

  pinMode(IN1_M1, OUTPUT);
  pinMode(IN2_M1, OUTPUT);
  pinMode(IN3_M1, OUTPUT);
  pinMode(IN4_M1, OUTPUT);
  pinMode(IN1_M2, OUTPUT);
  pinMode(IN2_M2, OUTPUT);
  pinMode(IN3_M2, OUTPUT);
  pinMode(IN4_M2, OUTPUT);
}

void loop() {
  if (radio.available()) {
    char text[MAX_MESSAGE_LENGTH] = "";
    radio.read(text, MAX_MESSAGE_LENGTH);

    Serial.print(F("Recebido: "));
    Serial.println(text);

    char direction[16] = "";
    int numSteps = 0;
    if (sscanf(text, "%s %d", direction, &numSteps) == 2) {
      if (strcmp(direction, "frente") == 0) {
        mover(numSteps, 0, 1);
      } else if (strcmp(direction, "tras") == 0) {
        mover(numSteps, 1, 0);
      } else if (strcmp(direction, "direita") == 0) {
        mover(numSteps, 1, 1);
      } else if (strcmp(direction, "esquerda") == 0) {
        mover(numSteps, 0, 0);
      } else {
        Serial.println(F("Erro: Direção inválida."));
      }
    } else {
      Serial.println(F("Erro: Formato de mensagem inválido."));
    }
  }
}

void mover(int contagemPassos, int M1, int M2) {
  for (int i = 0; i < contagemPassos; i++) {
    for (int j = 0; j < 8; j++) {
      digitalWrite(IN1_M1, steps[j][direcoes[M1][0]]);
      digitalWrite(IN2_M1, steps[j][direcoes[M1][1]]);
      digitalWrite(IN3_M1, steps[j][direcoes[M1][2]]);
      digitalWrite(IN4_M1, steps[j][direcoes[M1][3]]);

      
      digitalWrite(IN1_M2, steps[j][direcoes[M2][0]]);
      digitalWrite(IN2_M2, steps[j][direcoes[M2][1]]);
      digitalWrite(IN3_M2, steps[j][direcoes[M2][2]]);
      digitalWrite(IN4_M2, steps[j][direcoes[M2][3]]);
      delay(2);
    }
  }
}