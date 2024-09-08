//Para Larissa 


#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "pinagem.h" //primeiro de tudo

// set the LCD address to 0x3F for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include "util.h"
#include "icones.h"
#include "menuMusicas.h"
#include "menuDJ.h"
#include "menuJogo.h"

void setup()
{
  // Inicializa a EEPROM
  EEPROM.begin(512);

  // Recupere o recorde da EEPROM
  // recorde = EEPROM.read(enderecoRecorde);

  // CONFIGURACAO INICIAL DO LCD
  telaBoasVindas();
  delay(1000);

  // Configuracao de pinos dos botoes
  pinMode(BOTAO_AZUL, INPUT);
  pinMode(BOTAO_AMARELO, INPUT);
  pinMode(BOTAO_VERDE, INPUT);
  pinMode(BOTAO_VERMELHO, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BOTAO_SELECAO_DIR, INPUT_PULLUP);
  pinMode(BOTAO_SELECAO_ESQ, INPUT_PULLUP);

  // criar caracter especial (LIMITE DE 8)
  lcd.createChar(0, icon_esquerda);
  lcd.createChar(1, icon_meio);
  lcd.createChar(2, icon_direita);
  lcd.createChar(3, icon_esquerda_E);
  lcd.createChar(4, icon_meio_E);
  lcd.createChar(5, icon_direita_E);
  lcd.createChar(6, notaMusical1);
  lcd.createChar(7, o_fechado);

  // Console serial
  Serial.begin(9600);

  //randomSeed(analogRead(0));
}

// the loop function runs over and over again forever
void loop()
{

  // Volta a situacao de tela inicial
  apagaLeds();
  digitalWrite(BUZZER_PIN, LOW);//desliga resquicio de buzzer

  if (digitalRead(BOTAO_SELECAO_DIR) == LOW)
  {
    // ------------------------
    // MODO DIREITA - JOGO
    // ------------------------
    menuJogo();
  }

  else if (digitalRead(BOTAO_SELECAO_ESQ) == LOW)
  {
    // ------------------------
    // MODO ESQUERDA - SONGS
    // ------------------------
    menuMusicas();
  }

  else
  {
    // ------------------------
    // MODO CENTRAL - DJ
    // ------------------------
    menuDJ();
    
  }
}
