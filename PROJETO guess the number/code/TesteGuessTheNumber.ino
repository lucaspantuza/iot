//TESTE GUESS THE NUMBER

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define B1 14   //aumenta
#define B2 27   //diminui
#define B3 26   //start
#define B4 25   //reinicia
#define B5 33   //indefinido
#define B6 32   //indefinido

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x3F for a 20 chars and 4 line display

int statusB1 = 0;
int statusB2 = 0;
int statusB3 = 0;
int statusB4 = 0;
int statusB5 = 0;
int statusB6 = 0;

int numSecreto = 0;
int numUsuario = 0;
int resultado = 0;
int tentativas = 0;
int statusJogo = 0;

String strTentativas = "";


void converte () { //converte tentativas em string para printar no lcd
  strTentativas = String(tentativas);
}

void numAleatorio () {  //gera um número aleatório
  numSecreto = random(100);
}

void verificaResposta () {  //verifica a resposta do usuário
  tentativas += 1;

  if (numSecreto == numUsuario) {
    resultado = 1;
  }
  if (numSecreto < numUsuario) {
    resultado = 2;
  }
  if (numSecreto > numUsuario) {
    resultado = 3;
  }
  if (tentativas >= 5) {
    resultado = 4;
  }
}

void reiniciaJogo () {  //função para reinciar o jogo
  exit(0);
}

void ganhaJogo () { //função para quando ganhar o jogo
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Acertou!");
  delay(3000);

  reiniciaJogo();

  numSecreto = 0;
  numUsuario = 0;
  tentativas = 0;
  resultado = 0;
  statusJogo = 1;
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

  reiniciaJogo();

  numSecreto = 0;
  numUsuario = 0;
  tentativas = 0;
  resultado = 0;
  statusJogo = 1;
}

void verificaBotao () { //verifica se algum botão foi pressionado
  if (digitalRead(B1) == HIGH) {
    numUsuario += 1;
    if (numUsuario > 99) {
      numUsuario = 0;
    }
    converte();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tentativas: " + strTentativas);
    lcd.setCursor(7, 1);
    lcd.print(numUsuario);
    delay(100);
  }

  if (digitalRead(B2) == HIGH) {
    numUsuario -= 1;
    if (numUsuario < 0) {
      numUsuario = 99;
    }
    converte();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tentativas: " + strTentativas);
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
    reiniciaJogo();
  }
}

void jogo () {
  numAleatorio();
  while (statusJogo == 0) {
    verificaBotao();
  }
}


// the setup function runs once when you press reset or power the board
void setup() {
  // CONFIGURACAO INICIAL DO LCD ***********************
  lcd.init();  // initialize the lcd
  lcd.backlight();
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
  lcd.print("Tentativas: " + strTentativas);
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