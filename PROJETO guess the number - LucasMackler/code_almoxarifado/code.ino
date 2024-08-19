// selecionar a placa "ESP32 Dev Module"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define B1 14
#define B2 27
#define B3 26
#define B4 25
#define B5 33
#define B6 32

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x3F for a 20 chars and 4 line display

void setup() {

  // Configuracao e mensagem inicial do LCD
  lcd.init();  // initialize the lcd
  lcd.backlight();
  // lcd.setCursor(COLUNA, LINHA);
  lcd.setCursor(0, 0);
  lcd.print("     CEFET");
  // lcd.setCursor(0, 1);
  // lcd.print("Extensao OAs");
  //lcd.clear();

  // Configuracao de pinos dos botoes
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
  pinMode(B4, INPUT);
  pinMode(B5, INPUT);
  pinMode(B6, INPUT);

  // Console serial
  Serial.begin(9600);
  Serial.println("inicio");
}



void loop() {

  lcd.setCursor(0, 1);
  if (digitalRead(B1) == HIGH) {
    lcd.print("1");
  } else {
    lcd.print("-");
  }

  lcd.setCursor(3, 1);
  if (digitalRead(B2) == HIGH) {
    lcd.print("2");
  } else {
    lcd.print("-");
  }

  lcd.setCursor(6, 1);
  if (digitalRead(B3) == HIGH) {
    lcd.print("3");
  } else {
    lcd.print("-");
  }

  lcd.setCursor(9, 1);
  if (digitalRead(B4) == HIGH) {
    lcd.print("4");
  } else {
    lcd.print("-");
  }

  lcd.setCursor(12, 1);
  if (digitalRead(B5) == HIGH) {
    lcd.print("5");
  } else {
    lcd.print("-");
  }

  lcd.setCursor(15, 1);
  if (digitalRead(B6) == HIGH) {
    lcd.print("6");
  } else {
    lcd.print("-");
  }

  delay(100);
}
