#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define BAUD_RATE 9600
#define CE_PIN 9
#define CSN_PIN 10
#define MAX_MESSAGE_LENGTH 32

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";

void setup() {
  Serial.begin(BAUD_RATE);
  while (!Serial);

  if (!radio.begin()) {
    Serial.println(F("Erro: Falha ao inicializar o nRF24L01!"));
    while (1);
  }

  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
  Serial.println(F("Emissor inicializado com sucesso."));
}

void contagemRegressiva(unsigned long segundos) {
  unsigned long startTime = millis();
  unsigned long duration = segundos * 1000;
  unsigned long lastPrint = 0;

  while (millis() - startTime < duration) {
    unsigned long elapsed = (millis() - startTime) / 1000;
    unsigned long remaining = segundos - elapsed;

    if (remaining != lastPrint) {
      Serial.print(F("Próxima mensagem em: "));
      Serial.print(remaining);
      Serial.println(F(" segundos"));
      lastPrint = remaining;
    }
  }
}

void loop() {
  const int commands = 4;
  const char *texts[] = { "frente 11", "esquerda 11", "tras 11", "direita 11" };

  for (int i = 0; i < commands; i++) {
    int delaySeconds;
    sscanf(texts[i], "%*s %d", &delaySeconds);

    if (radio.write(texts[i], strlen(texts[i]) + 1)) {
      Serial.print(F("Enviado: "));
      Serial.println(texts[i]);
    } else {
      Serial.println(F("Erro: Falha ao enviar mensagem!"));
    }

    contagemRegressiva(delaySeconds);
  }
}