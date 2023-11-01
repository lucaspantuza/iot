#include <Keypad.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h> 


LiquidCrystal_I2C lcd(0x27, 16, 2);



void setup(){
  Serial.begin(9600);
  pinMode(BUZZ_PIN,OUTPUT);
  lcd.init();   // INICIALIZA O DISPLAY LCD
  lcd.clear();
  lcd.backlight(); // HABILITA O BACKLIGHT (LUZ DE FUNDO) 
  lcd.setCursor(0, 0); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print("#    CEFET     #"); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
  lcd.setCursor(0, 1); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print(" oioioioioi "); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
}



void loop(){

}
