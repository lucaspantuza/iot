#include <RH_ASK.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>





// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL)
// On an arduino ESP32:    21(SDA),  22(SCL)
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 64     // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);






//Which will initialise the driver at 2000 bps, recieve on GPIO2, transmit on GPIO4, PTT on GPIO5
#define RF_TRANSMISSOR 18
#define RF_RECEPTOR 5
// RH_ASK driver(2000, RF_TRANSMISSOR, 11, 5);  //CRIA O DRIVER PARA COMUNICAÇÃO
RH_ASK driver(2000, RF_RECEPTOR, RF_TRANSMISSOR);  // 200bps, TX on D3 (pin 2), RX on D4 (pin 3)
String str = "";                                   //VARIÁVEL DO TIPO STRING


void setup() {

  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000);  // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  //display.setFont(&FreeSerif9pt7b);
  display.setTextColor(WHITE);



  //INICIALIZA A COMUNICAÇÃO RF DO DRIVER
  if (!driver.init())
    Serial.println("init RF failed");
}

void loop() {

  //-------------



  // Recebe mensagem via radio
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];  //LÊ A MENSAGEM RECEBIDA (PALAVRA: led)
  uint8_t buflen = sizeof(buf);         //CRIA O COMPRIMENTO DO BUFFER PARA O TAMANHO DE buf

  if (driver.recv(buf, &buflen)) {      //SE O DRIVER RECEBEU buf(INTEIRO) E buflen (COMPRIMENTO DE DADOS), FAZ
    str = "";                           //VARIÁVEL RECEBE VAZIO
    for (int i = 0; i < buflen; i++) {  //PARA i IGUAL A 0, ENQUANTO i MENOR QUE buflen, INCREMENTA i
      str += (char)buf[i];              //VARIÁVEL RECEBE OS CARACTERES E FORMA A PALAVRA
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
    Serial.println(str);
  }

  //-------------

  //nao pode ter delay, pq senao corre um grande risco de perder mensagens enquanto dormia
}
