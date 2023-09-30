#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // Largura do display OLED em pixels
#define SCREEN_HEIGHT 64  // Altura do display OLED em pixels
#define OLED_RESET    -1  // Pino de reset do OLED (não utilizado)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int buttonPin = 7;  // Pino do botão
int lastButtonState = LOW;  // Estado anterior do botão
int randomValue;  // Variável para armazenar o número aleatório

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
  pinMode(buttonPin, INPUT_PULLUP);  // Configura o pino do botão como entrada com resistor pull-up interno

  // Inicializa o display OLED
  if(!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
    Serial.println(F("Erro ao iniciar o display OLED"));
    while(true);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Bom Dia!");
  display.display();
  randomSeed(analogRead(0));  // Inicializa a semente para gerar números aleatórios
}

void loop() {
  int buttonState = digitalRead(buttonPin);  // Lê o estado atual do botão

  // Verifica se o botão foi pressionado e o estado anterior era não pressionado
  if (buttonState == LOW && lastButtonState == HIGH) {
    randomValue = random(0, 100);  // Gera um número aleatório entre 0 e 99
    Serial.print("Número Aleatório: ");
    Serial.println(randomValue);  // Envia o número aleatório para a porta serial

    // Limpa o display e exibe a mensagem e o número aleatório
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Bom Dia!");
    display.setCursor(0, 20);  // Define a posição para exibir o número aleatório
    display.print("Aleatório: ");
    display.println(randomValue);
    display.display();
  }

  lastButtonState = buttonState;  // Atualiza o estado anterior do botão
}