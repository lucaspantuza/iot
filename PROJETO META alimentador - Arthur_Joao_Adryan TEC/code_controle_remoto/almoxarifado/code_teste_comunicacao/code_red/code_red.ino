#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(8, 10);  // CE, CSN
const byte address[6] = "00002";


void setup() {

  Serial.begin(9600);

  // radio.begin();
  // radio.openWritingPipe(address);
  // radio.setPALevel(RF24_PA_MIN);
  // radio.stopListening();
}

int cont = 0;  //esse contador eh apenas para testar, na vida real ele iria estourar rapido
void loop() {

  // char buffer[25] = "AAA";
  // // sprintf(buffer, "testeA... cont %d", cont);
  // // cont++;

  // radio.write(&buffer, sizeof(buffer));

  Serial.print("Msg enviada: ");
  // Serial.println(buffer);
  // Serial.println();

  delay(1000);
}