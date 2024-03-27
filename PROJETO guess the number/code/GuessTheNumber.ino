/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/


// selecionar a placa "ESP32 Dev Module"


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define B1 14   //aumenta
#define B2 27   //diminui
#define B3 26   //start
#define B4 25   //exit
#define B5 33   //indefinido
#define B6 32   //indefinido

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x3F for a 20 chars and 4 line display

byte setaCima[] = {   //cria um caractere com uma seta para cima
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

byte setaBaixo[] = {  //cria um caractere com uma seta para baixo
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100
};

byte coracao[] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};


int statusB1 = 0;
int statusB2 = 0;
int statusB3 = 0;
int statusB4 = 0;
int statusB5 = 0;
int statusB6 = 0;

int numSecreto = 0;
int numUsuario = 0;
int resultado = 0;
int vidas = 5;
int statusJogo = 0;

String strVidas = "";


void converte () { //converte as vidas do usuário em string para printar no lcd
  strVidas = String(vidas);
}

void numAleatorio () {  //gera um número aleatório
  numSecreto = random(10);
}

void verificaResposta () {  //verifica a resposta do usuário
  vidas -= 1;

  if (numSecreto == numUsuario) {
    resultado = 1;
  }
  if (numSecreto < numUsuario) {
    resultado = 2;
  }
  if (numSecreto > numUsuario) {
    resultado = 3;
  }
  if (vidas <= 0) {
    resultado = 4;
  }
}

void reiniciaJogo () {  //função para reinciar o jogo
  numSecreto = 0;
  numUsuario = 0;
  vidas = 5;
  resultado = 0;
}

void fechaJogo () {   //função que chama função exit(0);
  exit(0);
}

void ganhaJogo () { //função para quando ganhar o jogo
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Acertou!");
  delay(3000);
  lcd.setCursor(0, 0);
  lcd.print("PRESSIONE ");
  lcd.write(0);
  lcd.print(" ou ");
  lcd.write(1);
  lcd.setCursor(1, 1);
  lcd.print("PARA REINICIAR");

  reiniciaJogo();
}

void numMaior () {  //quando a tentativa do usuario for mais alta que o valor certo
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Mais baixo!");
  lcd.setCursor(7, 1);
  lcd.print(numUsuario);
}

void numMenor () {  //quando a tentativa do usuario for mais baixa que o valor certo
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Mais alto!");
  lcd.setCursor(7, 1);
  lcd.print(numUsuario);
}

void perdeJogo () { //função para quando ganhar o jogo
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Perdeu!");
  delay(3000);
  lcd.setCursor(0, 0);
  lcd.print("PRESSIONE ");
  lcd.write(0);
  lcd.print(" ou ");
  lcd.write(1);
  lcd.setCursor(1, 1);
  lcd.print("PARA REINICIAR");

  reiniciaJogo();
}

void verificaBotao () { //verifica se algum botão foi pressionado
  if (digitalRead(B1) == HIGH) {
    numUsuario += 1;
    if (numUsuario > 10) {
      numUsuario = 0;
    }
    converte();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Vidas: " + strVidas);
    /*for (i=1, i<=vidas, i++) {
      lcd.write(♡)
    }*/ //testar
    lcd.setCursor(7, 1);
    lcd.print(numUsuario);
    delay(100);
  }

  if (digitalRead(B2) == HIGH) {
    numUsuario -= 1;
    if (numUsuario < 0) {
      numUsuario = 10;
    }
    converte();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Vidas: " + strVidas);
    lcd.setCursor(7, 1);
    lcd.print(numUsuario);
    delay(100);
  }

  if (digitalRead(B3) == HIGH) {
    verificaResposta();
    if (resultado == 1) {
      ganhaJogo();
    }
    if (resultado == 2) {
      numMaior();
    }
    if (resultado == 3) {
      numMenor();
    }
    if (resultado == 4) {
      perdeJogo();
    }
    delay(500);
  }

  if (digitalRead(B4) == HIGH) {
    fechaJogo();
  }
}

void jogo () {
  numAleatorio();
  while (true) {
    verificaBotao();
  }
}


// the setup function runs once when you press reset or power the board
void setup() {
  // CONFIGURACAO INICIAL DO LCD ***********************
  lcd.init();  // initialize the lcd
  lcd.backlight();
  lcd.createChar(0, setaCima);
  lcd.createChar(1, setaBaixo);
  lcd.createChar(2, coracao);

  // lcd.setCursor(COLUNA, LINHA);
  lcd.setCursor(5, 0);
  lcd.print("CEFET");
  lcd.setCursor(2, 1);
  lcd.print("Extensao OAs");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Guess the number");
  delay(2000);
  lcd.clear();
  converte();
  lcd.setCursor(0, 0);
  lcd.print("Vidas: " + strVidas);
  lcd.setCursor(7, 1);
  lcd.print(numUsuario);


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


// the loop function runs over and over again forever
void loop() {
  jogo();
}
