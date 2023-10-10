#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <Fonts/FreeSerif9pt7b.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels
#define DELAY_LOOP 500
#define SAMPLE_WINDOW 50  //janela em que o som eh medido no sensor de som

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL)
// On an arduino ESP32:    21(SDA),  22(SCL)
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//-----------------------------



//display SDA - D21 (antes da RX0)
//display SCK - D22 (depois da TX0)
#define SENSOR_SOM_ANALOGICO 34
#define SENSOR_SOM_DIGITAL 32

#define LED_RED 4
#define LED_GREEN 15
#define LED_BLUE 2
int count_led = 0;




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

  pinMode(SENSOR_SOM_ANALOGICO, INPUT);
  pinMode(SENSOR_SOM_DIGITAL, INPUT);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT); //o led azul compartilha a mesma porta que o led da placa
}

void loop() {


  // faz o gamer
  // aqui coloquei pra piscar um de cada vez, mas qualquer combinacao de leds
  // pode ser feita e gerar cores combinadas
  if (count_led == 0) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
    count_led = 1;
  } else if (count_led == 1) {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, LOW);
    count_led = 2;
  } else if (count_led == 2) {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, HIGH);
    count_led = 0;
  }


  // faz a medida do SOM analogico - collect data for 50 mS
  unsigned long startMillis = millis();
  int valor_mic_analogico = 0;
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;
  unsigned int sample;
  while (millis() - startMillis < SAMPLE_WINDOW) {
    sample = analogRead(SENSOR_SOM_ANALOGICO);
    if (sample > signalMax) {
      signalMax = sample;
    } else if (sample < signalMin) {
      signalMin = sample;
    }
  }
  valor_mic_analogico = (signalMax + signalMin) / 2;

  //faz a leitura do SOM digital
  int valor_mic_digital = digitalRead(SENSOR_SOM_DIGITAL);


  // Imprime valores lidos no serial
  Serial.print("Analogico:");
  Serial.print(valor_mic_analogico);
  Serial.print("; Digital:");
  Serial.print(valor_mic_digital);
  Serial.println();

  // Imprime valores lidos no display OLED
  display.clearDisplay();
  display.setCursor(5, 7);
  display.print("Analog.: ");
  display.print(valor_mic_analogico);
  display.setCursor(5, 25);
  display.print("Digital: ");
  display.print(valor_mic_digital);
  display.display();


  delay(DELAY_LOOP);
}
