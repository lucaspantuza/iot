#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"
#include "printf.h"

RF24 myRadio(16, 5);  // CE, CSN - ESP
// const uint64_t pipe = 0xB01DFACECEL;
const byte address[6] = "00002";
struct package
{
  int id=0;
  int code = 0;
  char text[100] = "";
};

typedef struct package Package;
Package data;

void setup() {
 Serial.begin(9600);
 printf_begin();
 delay(1000);

 myRadio.begin();
 myRadio.setChannel(115);
 myRadio.openReadingPipe(1,pipe);
 myRadio.printDetails();
 myRadio.startListening();

 Serial.println("Set-Up Done");
 delay(1000);
}

void loop() {
  if(myRadio.available())
 {
  while(myRadio.available())
   {
     myRadio.read(&data, sizeof(data));
     Serial.print("\nPackage");
     Serial.println(data.id);
     Serial.println(data.code);
     Serial.println(data.text);
   }
 }
 delay(500);
}   