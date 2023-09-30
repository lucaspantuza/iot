#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DELAY_LOOP 2000

RF24 radio(4, 5);  // CE, CSN
const byte address[6] = "00001";



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



#define SENSOR_TEMPERATURA 32
DHT_Unified dht(SENSOR_TEMPERATURA, DHT11);  // configurando o Sensor DHT - pino e tipo
float umidade = 0;
float temperatura = 0;





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


  dht.begin();  // inicializa a função
  Serial.println("Usando o Sensor DHT");
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);  // imprime os detalhes do Sensor de Temperatura
  Serial.println("------------------------------------");
  Serial.println("Temperatura");
  Serial.print("Sensor:       ");
  Serial.println(sensor.name);
  Serial.print("Valor max:    ");
  Serial.print(sensor.max_value);
  Serial.println(" *C");
  Serial.print("Valor min:    ");
  Serial.print(sensor.min_value);
  Serial.println(" *C");
  Serial.print("Resolucao:   ");
  Serial.print(sensor.resolution);
  Serial.println(" *C");
  dht.humidity().getSensor(&sensor);  // imprime os detalhes do Sensor de Umidade
  Serial.println("------------------------------------");
  Serial.println("Umidade");
  Serial.print("Sensor:       ");
  Serial.println(sensor.name);
  Serial.print("Valor max:    ");
  Serial.print(sensor.max_value);
  Serial.println("%");
  Serial.print("Valor min:    ");
  Serial.print(sensor.min_value);
  Serial.println(" %");
  Serial.print("Resolucao:   ");
  Serial.print(sensor.resolution);
  Serial.println(" %");
  Serial.println("------------------------------------");


  if ((sensor.min_delay / 1000) > DELAY_LOOP) {
    Serial.println(F("ERRO: O tempo de leitura minimo do sensor eh maior que o tempo do LOOP"));
    for (;;)
      ;  // Don't proceed, loop forever
  }


  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

int cont = 0;  //esse contador eh apenas para testar, na vida real ele iria estourar rapido
void loop() {

  //-------------

  // Faz a leitura da temperatura e umidade
  sensors_event_t event;

  dht.temperature().getEvent(&event);  // faz a leitura da Temperatura
  if (isnan(event.temperature)) {      // se algum erro na leitura
    Serial.println("Erro na leitura da Temperatura!");
  } else {
    Serial.print("Temperatura: ");  // imprime a Temperatura
    temperatura = event.temperature;
    Serial.print(temperatura);
    Serial.println(" *C");
  }

  dht.humidity().getEvent(&event);       // faz a leitura de umidade
  if (isnan(event.relative_humidity)) {  // se algum erro na leitura
    Serial.println("Erro na leitura da Umidade!");
  } else {
    Serial.print("Umidade: ");  // imprime a Umidade
    umidade = event.relative_humidity;
    Serial.print(umidade);
    Serial.println(" %");
  }

  //-------------

  // Imprime valores lidos no display OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("---------------------");
  display.print("Temperatura. ");
  display.print(temperatura);
  display.println(" C");
  display.setCursor(0, 20);
  display.print("Umidade..... ");
  display.print(umidade);
  display.println(" %");
  display.println("---------------------");
  display.display();

  //-------------

  char buffer[25];
  sprintf(buffer, "%d: %.1fC %.0fU", cont, temperatura, umidade);
  cont++;

  display.setCursor(0, 48);
  display.print("Msg. ");
  display.print(buffer);
  display.display();

  Serial.print("Msg. ");
  Serial.println(buffer);
  Serial.println();


  radio.write(&buffer, sizeof(buffer));

  //-------------

  delay(DELAY_LOOP);
}