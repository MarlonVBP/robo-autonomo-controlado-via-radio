# 🤖 Robô Autônomo Controlado via Rádio 📡

Este projeto implementa um robô autônomo controlado remotamente por comunicação via rádio usando módulos nRF24L01 📻. O sistema é composto por um emissor que envia comandos (frente, ré, esquerda, direita) e um receptor que controla motores de passo para movimentação do robô 🚗. A comunicação é unidirecional, com o emissor enviando mensagens e o receptor interpretando-as para executar os movimentos 🕹️.

## ✨ Funcionalidades

- Comunicação sem fio via módulos nRF24L01 📶.
- Controle de movimentos do robô: frente ⬆️, ré ⬇️, esquerda ⬅️, direita ➡️.
- Envio de comandos com duração configurável (em segundos) ⏱️.
- Controle de motores de passo com driver ULN2003 para movimentos precisos 🔄.
- Feedback via Serial para monitoramento de envio e recebimento de mensagens 📢.

## 📂 Estrutura do Projeto

O projeto está organizado em dois arquivos principais:

- `emissor.ino` 📄: Código do emissor, responsável por enviar comandos via nRF24L01.
- `receptor.ino` 📜: Código do receptor, que interpreta os comandos e controla os motores do robô.

## 🛠️ Requisitos

### ⚙️ Hardware

- 2x Arduino (Uno, Nano ou compatível) 🖥️.
- 2x Módulos nRF24L01 📻.
- 2x Motores de passo unipolares (ex.: 28BYJ-48) 🔧.
- 2x Drivers ULN2003 para motores de passo 🔌.
- Fonte de alimentação de 5V (para os Arduinos e lógica dos ULN2003) 🔋.
- Cabos jumper e protoboard para conexões 🪢.

### 💾 Software

- Arduino IDE (ou outra IDE compatível com Arduino) 🖥️.
- Bibliotecas:
  - `RF24` (instale via Library Manager ou GitHub) 📚.
  - `nRF24L01` (dependência da biblioteca RF24) 📦.
  - `SPI` (incluída na Arduino IDE) 📚.

## 🔧 Diagrama Elétrico

O diagrama elétrico mostra as conexões entre os Arduinos, os módulos nRF24L01, os drivers ULN2003 e os motores de passo ⚡:

- **Arduino (Emissor)** 🖥️:
  - nRF24L01: CE → Pino 9, CSN → Pino 10, SCK → Pino 13, MOSI → Pino 11, MISO → Pino 12.
  - VCC → 3.3V, GND → Terra comum 🌍.
- **Arduino (Receptor)** 🖥️:
  - nRF24L01: CE → Pino 9, CSN → Pino 10, SCK → Pino 13, MOSI → Pino 11, MISO → Pino 12.
  - Motor 1: IN1 → Pino 2, IN2 → Pino 3, IN3 → Pino 4, IN4 → Pino 5.
  - Motor 2: IN1 → Pino 6, IN2 → Pino 7, IN3 → Pino 8, IN4 → Pino A0.
  - VCC → 3.3V (nRF24L01), 5V (ULN2003), GND → Terra comum 🌍.
- **ULN2003 (Motor 1 e Motor 2)** 🔌:
  - IN1 a IN4 conectados aos pinos do Arduino.
  - OUT1 a OUT4 conectados às bobinas A, B, C, D de cada motor.
  - VCC → 5V, COM → 5V (ou fonte externa, se necessário), GND → Terra comum 🌍.
- **Motores de Passo** 🔧:
  - Motor 1 e Motor 2 conectados às saídas OUT1 a OUT4 dos respectivos ULN2003.
- **Fontes de Alimentação** 🔋:
  - 5V para os Arduinos (VCC) e VCC dos ULN2003.
  - Opcional: fonte externa para os motores (COM dos ULN2003).

**Nota** 📝: Certifique-se de conectar todos os GNDs (Arduinos, nRF24L01, ULN2003, fontes) a um único ponto comum para evitar problemas elétricos ⚠️.

## 🚀 Instruções de Instalação

1. **Clone o Repositório** 📥:

   ```bash
   git clone https://github.com/seu-usuario/robo-autonomo-controlado-via-radio.git
   cd robo-autonomo-controlado-via-radio
   ```

2. **Abra o Projeto na Arduino IDE** 🖥️:

   - Abra os arquivos `emissor.ino` e `receptor.ino` na Arduino IDE.
   - Certifique-se de que ambos os arquivos estão no mesmo diretório 📂.

3. **Instale as Bibliotecas Necessárias** 📚:

   - No Arduino IDE, vá em "Sketch" > "Include Library" > "Manage Libraries...".
   - Procure e instale `RF24` (autor: TMRh20) 📦.
   - A biblioteca `nRF24L01` e `SPI` são incluídas automaticamente.

4. **Monte o Circuito** 🔧:

   - Conecte os componentes conforme o diagrama elétrico descrito acima ⚡.
   - Verifique todas as conexões antes de ligar as fontes de alimentação 🔍.

5. **Faça Upload do Código** ⬆️:

   - Conecte o Arduino do emissor ao computador via USB 🔌.
   - Na Arduino IDE, selecione a placa correta (ex.: "Arduino Uno") em "Tools" > "Board" 🛠️.
   - Selecione a porta correta em "Tools" > "Port" 🔗.
   - Clique em "Upload" para carregar o código `emissor.ino` 🚀.
   - Repita o processo para o Arduino do receptor com o código `receptor.ino`.

## 🎮 Como Usar

1. **Inicie os Arduinos** 🌟:

   - Após o upload, abra o Monitor Serial (em "Tools" > "Serial Monitor", 9600 baud) para ambos os Arduinos 📡.
   - O emissor exibirá mensagens de inicialização e status de envio, enquanto o receptor mostrará mensagens recebidas 📍.

2. **Controle o Robô** 🚗:

   - O emissor envia comandos automaticamente em sequência (frente, esquerda, ré, direita) a cada 11 segundos ⏲️.
   - O receptor interpreta os comandos e move o robô conforme instruído:
     - "Frente" ⬆️: Ambos os motores em sentidos opostos para movimento linear.
     - "Ré" ⬇️: Ambos os motores em sentidos opostos (inverso ao frente).
     - "Esquerda" ⬅️: Ambos os motores no mesmo sentido para giro.
     - "Direita" ➡️: Ambos os motores no mesmo sentido (inverso ao esquerda).
   - Verifique o Monitor Serial para confirmar o envio e recebimento de comandos 📢.

**Demonstração**: [Ver projeto funcionando](https://drive.google.com/drive/folders/1i8JzHkTcUEUGwg8nRB1wRnrthykEvdyF?usp=sharing)

## 🌟 Possíveis Melhorias

- Adicionar sensores (ex.: ultrassom para detecção de obstáculos) 📡.
- Implementar controle proporcional para ajustar a velocidade dos motores ⚙️.
- Adicionar uma interface manual no emissor (ex.: botões ou joystick) 🕹️.
- Implementar comunicação bidirecional para feedback do receptor 📻.

## 📜 Licença

Este projeto está licenciado sob a MIT License. Sinta-se à vontade para usar, modificar e compartilhar! 🎉

---

Feito por: Marlon Victor Bezerra dos Passos. 🚀
