#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

RF24 radio(4, 5); // CE, CSN

const byte address[6] = "00001";

#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 64     // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {  
  Serial.begin(9600);

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000);  // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  //display.setFont(&FreeSerif9pt7b);
  display.setTextColor(WHITE);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }

      //Imprime a mensagem recebida no display OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("---------------------");
    display.println("- MENSAGEM RECEBIDA -");
    display.println("---------------------");
    display.println();
    display.println(str);
    display.display();

    //Imprime a mensagem recebida no terminal
    Serial.print("Msg. ");
    Serial.println(text);
}