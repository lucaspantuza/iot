#include <Wire.h>  
#include <LiquidCrystal_I2C.h> 

int switch1 = 10;
int switch2 = 11;
int switch3 = 12;
int switch4 = 13;

int buzzer = 9;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  Serial.begin(9600);

  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);
  pinMode(switch3, INPUT_PULLUP);
  pinMode(switch4, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  lcd.init();   // INICIALIZA O DISPLAY LCD
  lcd.clear();
  lcd.backlight(); // HABILITA O BACKLIGHT (LUZ DE FUNDO) 

}

void loop() {

  lcd.clear();
  
  lcd.setCursor(0, 0); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print("#    CEFET     #"); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
  lcd.setCursor(0, 1); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  //lcd.print(" oioioioioi "); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD



  // Teste dos botoes
  if (digitalRead(switch1) == LOW)
    lcd.print(" * ");
  else
    lcd.print(" o ");

  if (digitalRead(switch2) == LOW)
    lcd.print(" * ");
  else
    lcd.print(" o ");

  if (digitalRead(switch3) == LOW)
    lcd.print(" * ");
  else
    lcd.print(" o ");

  if (digitalRead(switch4) == LOW)
    lcd.print(" * ");
  else
    lcd.print(" o ");


  if (digitalRead(switch1) == LOW){
    /*
    Frequência das notas:
    Dó - 262 Hz
    Ré - 294 Hz
    Mi - 330 Hz
    Fá - 349 Hz
    Sol - 392 Hz
    Lá - 440 Hz
    Si - 494 Hz
    #Dó - 528 Hz
    */
    delay(1000);
    int tempo = 400;
    
    tone(buzzer,440,tempo); //LA
    delay(tempo);
    tone(buzzer,294,tempo); //RE
    delay(tempo);
    tone(buzzer,349,tempo/2); //FA - O tempo/2 faz com que demore metade do valor estipulado anteriormente, pois essa parte é mais rápida
    delay(tempo/2);
    tone(buzzer,392,tempo/2); //SOL
    delay(tempo/2);
    tone(buzzer,440,tempo); //LA
    delay(tempo);
    tone(buzzer,294,tempo); //RE
    delay(tempo);
    tone(buzzer,349,tempo/2); //FA
    delay(tempo/2);
    tone(buzzer,392,tempo/2); //SOL
    delay(tempo/2);
    tone(buzzer,330,tempo); //MI
    delay(tempo);

    delay(2000);
  }else{
    //digitalWrite(buzzer, LOW);
  }

  Serial.println();
  delay(500);

}
