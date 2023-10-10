//Programa : Módulo RF Transmissor com Arduino Tiny

#include <VirtualWire.h>

#define PIN_RF 4
#define PIN_B1 14
#define PIN_B2 12
#define PIN_B3 8
#define PIN_B4 5
#define LED_BUILTIN 13


void setup() {
 pinMode(LED_BUILTIN, OUTPUT);

  pinMode(PIN_B1, INPUT_PULLUP);
  pinMode(PIN_B2, INPUT_PULLUP);
  pinMode(PIN_B3, INPUT_PULLUP);
  pinMode(PIN_B4, INPUT_PULLUP);

  vw_set_tx_pin(PIN_RF);
  vw_setup(2000);  // Bits per sec
}

void loop() {
  if (digitalRead(PIN_B1) == LOW) {
    while (digitalRead(PIN_B1) == LOW) {}
    send("A");
  }

  if (digitalRead(PIN_B2) == LOW) {
    while (digitalRead(PIN_B2) == LOW) {}
    send("B");
  }

  if (digitalRead(PIN_B3) == LOW) {
    while (digitalRead(PIN_B3) == LOW) {}
    send("C");
  }

  if (digitalRead(PIN_B4) == LOW) {
    while (digitalRead(PIN_B4) == LOW) {}
    send("D");
  }
}

// void press(int PIN) {
//   if (digitalRead(PIN) == LOW) {
//     while (digitalRead(PIN) == LOW) {}
//     char buffer[2];
//     sprintf(buffer, "%d", PIN);
//     send(buffer);
//     send()
//   }
// }

void send(char *message) {
  digitalWrite(LED_BUILTIN, HIGH);
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx();  // Aguarda o envio de dados
  digitalWrite(LED_BUILTIN, LOW);
}