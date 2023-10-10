#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"
#include "printf.h"

RF24 myRadio(7, 8);
const uint64_t pipex = 0xB01DFACECEL;
// const byte pipe[6] = "00002";

struct package {
  int id = 1;
  int code = 2;
  char text[100] = "text";
};

typedef struct package Package;
Package data;

void setup() {
  Serial.begin(9600);
  printf_begin();
  delay(1000);

  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.openWritingPipe(pipex);
  myRadio.setRetries(15, 15);
  myRadio.printDetails();
  myRadio.stopListening();

  Serial.println("Set-Up Done");
  delay(1000);
}

void loop() {
  if (!myRadio.write(&data, sizeof(data))) {
    Serial.println("******************* ERRO ********************");
    // myRadio.printDetails();
  } else {
    // myRadio.printDetails();

    Serial.print("\n\nEnvio OK - ");
    Serial.print(data.id);
    Serial.print(" - ");
    Serial.print(data.code);
    Serial.print(" - ");
    Serial.print(data.text);
    Serial.println("\n");
  }


  data.id += 1;
  data.code += 1;
  delay(3000);
}