// selecionar a placa "ESP32 Dev Module"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define B1 14
#define B2 12
#define B3 32
#define B4 35

#define B5 15
#define B6 2

#define BUZZER 23

#define DIPS1 16
#define DIPS2 17
#define DIPS3 5
#define DIPS4 18

#define LED_AZUL 26
#define LED_AMARELO 27
#define LED_VERDE 25
#define LED_VERMELHO 33

// LCD ***********************
// LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x3F for a 20 chars and 4 line display

void setup() {

  // CONFIGURACAO INICIAL DO LCD ***********************
  // lcd.init();  // initialize the lcd
  // lcd.backlight();
  // // lcd.setCursor(COLUNA, LINHA);
  // lcd.setCursor(0, 0);
  // lcd.print("     CEFET");
  // // lcd.setCursor(0, 1);
  // // lcd.print("Extensao OAs");
  // //lcd.clear();

  // Configuracao de pinos dos botoes
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
  pinMode(B4, INPUT);
  pinMode(B5, INPUT);
  pinMode(B6, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  pinMode(DIPS1, INPUT_PULLUP);
  pinMode(DIPS2, INPUT_PULLUP);
  pinMode(DIPS3, INPUT_PULLUP);
  pinMode(DIPS4, INPUT_PULLUP);

  // Console serial
  Serial.begin(9600);
  Serial.println("inicio");
}



void loop() {

  // ACENDE/APAGA OS LEDS - LOW:apaga, HIGH:acende
  digitalWrite(LED_AZUL, HIGH);
  digitalWrite(LED_AMARELO, HIGH);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  // PRESSIONAMENTO BOTOES
  // if (digitalRead(B1) == HIGH) {
  //   Serial.println("B1 HIGH");
  // } else {
  //   Serial.println("B1 LOW");
  // }
  // if (digitalRead(B2) == HIGH) {
  //   Serial.println("B2 HIGH");
  // } else {
  //   Serial.println("B2 LOW");
  // }
  // if (digitalRead(B3) == HIGH) {
  //   Serial.println("B3 HIGH");
  // } else {
  //   Serial.println("B3 LOW");
  // }
  // if (digitalRead(B4) == HIGH) {
  //   Serial.println("B4 HIGH");
  // } else {
  //   Serial.println("B4 LOW");
  // }
  // if (digitalRead(B5) == HIGH) {
  //   Serial.println("B5 HIGH");
  // } else {
  //   Serial.println("B5 LOW");
  // }
  // if (digitalRead(B6) == HIGH) {
  //   Serial.println("B6 HIGH");
  // } else {
  //   Serial.println("B6 LOW");
  // }

  // DIP SWITCH
  // if (digitalRead(DIPS1) == HIGH) {
  //   Serial.println("DIPS1 off");
  // } else {
  //   Serial.println("DIPS1 on");
  // }
  // if (digitalRead(DIPS2) == HIGH) {
  //   Serial.println("DIPS2 off");
  // } else {
  //   Serial.println("DIPS2 on");
  // }
  // if (digitalRead(DIPS3) == HIGH) {
  //   Serial.println("DIPS3 off");
  // } else {
  //   Serial.println("DIPS3 on");
  // }
  // if (digitalRead(DIPS4) == HIGH) {
  //   Serial.println("DIPS4 off");
  // } else {
  //   Serial.println("DIPS4 on");
  // }

  // BUZZER
  // digitalWrite(BUZZER, HIGH);
  // delay(1000);
  // digitalWrite(BUZZER, LOW);
  // delay(1000);

  // AGUARDA 1 SEGUNDO
  delay(1000);
}
