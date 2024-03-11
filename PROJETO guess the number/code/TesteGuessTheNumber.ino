//TESTE GUESS THE NUMBER

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define B1 14   //esquerda
#define B2 27   //aumenta
#define B3 26   //diminui
#define B4 25   //direita
#define B5 33   //enter
#define B6 32   //reinicia

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x3F for a 20 chars and 4 line display

byte checkSymbol[8] = {
  B00000,
  B00000,
  B00001,
  B00010,
  B10100,
  B01000,
  B00000,
  B00000
};

int statusB1 = 0;
int statusB2 = 0;
int statusB3 = 0;
int statusB4 = 0;
int statusB5 = 0;
int statusB6 = 0;

int posicao = 4;

int n1Secreto = 0;
int n2Secreto = 0;
int n3Secreto = 0;
int n4Secreto = 0;
int n5Secreto = 0;
int n6Secreto = 0;
int n7Secreto = 0;
int n8Secreto = 0;
int n1Usuario = 0;
int n2Usuario = 0;
int n3Usuario = 0;
int n4Usuario = 0;
int n5Usuario = 0;
int n6Usuario = 0;
int n7Usuario = 0;
int n8Usuario = 0;

bool resultado1 = false;
bool resultado2 = false;
bool resultado3 = false;
bool resultado4 = false;
bool resultado5 = false;
bool resultado6 = false;
bool resultado7 = false;
bool resultado8 = false;
bool resultadoFinal = false;

int tentativas = 0;
int statusJogo = 0;

String strTentativas = "";
String strN1 = "";
String strN2 = "";
String strN3 = "";
String strN4 = "";
String strN5 = "";
String strN6 = "";
String strN7 = "";
String strN8 = "";


void converte () { //converte variáveis em string para printar no lcd
  strTentativas = String(tentativas);
  strN1 = String(n1Usuario);
  strN2 = String(n2Usuario);
  strN3 = String(n3Usuario);
  strN4 = String(n4Usuario);
  strN5 = String(n5Usuario);
  strN6 = String(n6Usuario);
  strN7 = String(n7Usuario);
  strN8 = String(n8Usuario);
}

void numAleatorio () {  //gera os números aleatórios
  n1Secreto = random(10);
  n2Secreto = random(10);
  n3Secreto = random(10);
  n4Secreto = random(10);
  n5Secreto = random(10);
  n6Secreto = random(10);
  n7Secreto = random(10);
  n8Secreto = random(10);
}

void confereValores () {  //confere os valores do usuario
  lcd.clear();

  tentativas += 1;

  if (n1Secreto == n1Usuario) {
    resultado1 = true;

    lcd.setCursor(4, 0);
    lcd.print(byte(0));
  } else {
    lcd.setCursor(4, 0);
    lcd.print("X");
  }
  if (n2Secreto == n2Usuario) {
    resultado2 = true;

    lcd.setCursor(5, 0);
    lcd.print(byte(0));
  } else {
    lcd.setCursor(5, 0);
    lcd.print("X");
  }
  if (n3Secreto == n3Usuario) {
    resultado3 = true;

    lcd.setCursor(6, 0);
    lcd.print(byte(0));
  } else {
    lcd.setCursor(6, 0);
    lcd.print("X");
  }
  if (n4Secreto == n4Usuario) {
    resultado4 = true;

    lcd.setCursor(7, 0);
    lcd.print(byte(0));
  } else {
    lcd.setCursor(7, 0);
    lcd.print("X");
  }
  if (n5Secreto == n5Usuario) {
    resultado5 = true;

    lcd.setCursor(8, 0);
    lcd.print(byte(0));
  } else {
    lcd.setCursor(8, 0);
    lcd.print("X");
  }
  if (n6Secreto == n6Usuario) {
    resultado6 = true;

    lcd.setCursor(9, 0);
    lcd.print(byte(0));
  } else {
    lcd.setCursor(9, 0);
    lcd.print("X");
  }
  if (n7Secreto == n7Usuario) {
    resultado7 = true;

    lcd.setCursor(10, 0);
    lcd.print(byte(0));
  } else {
    lcd.setCursor(10, 0);
    lcd.print("X");
  }
  if (n8Secreto == n8Usuario) {
    resultado8 = true;

    lcd.setCursor(11, 0);
    lcd.print(byte(0));
  } else {
    lcd.setCursor(11, 0);
    lcd.print("X");
  }

  if (resultado1 && resultado2 && resultado3 && resultado4 && resultado5 && resultado6 && resultado7 && resultado8) {
    resultadoFinal = true;
  }
}

void reiniciaJogo () {  //reseta as variáveis e reinicia o jogo
  statusJogo += 1;

  statusB1 = 0;
  statusB2 = 0;
  statusB3 = 0;
  statusB4 = 0;
  statusB5 = 0;
  statusB6 = 0;
  posicao = 4;
  n1Secreto = 0;
  n2Secreto = 0;
  n3Secreto = 0;
  n4Secreto = 0;
  n5Secreto = 0;
  n6Secreto = 0;
  n7Secreto = 0;
  n8Secreto = 0;
  n1Usuario = 0;
  n2Usuario = 0;
  n3Usuario = 0;
  n4Usuario = 0;
  n5Usuario = 0;
  n6Usuario = 0;
  n7Usuario = 0;
  n8Usuario = 0;
  resultado1 = false;
  resultado2 = false;
  resultado3 = false;
  resultado4 = false;
  resultado5 = false;
  resultado6 = false;
  resultado7 = false;
  resultado8 = false;
  resultadoFinal = false;
  tentativas = 0;
  strTentativas = "";
}

void ganhaJogo () { //quando acertar os 8 dígitos
  delay(500);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Você ganhou!");
  lcd.setCursor(1, 1);
  lcd.print("Tentativas: ");
  converte();
  lcd.print(strTentativas);
  reiniciaJogo();
}

void cursor () {  //faz a posicão do cursor piscar
  statusJogo = 0;
  verificaBotao();

  if (posicao == 4) {
    lcd.setCursor(posicao, 1);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(posicao, 1);
    lcd.print(n1Usuario);
  }
  if (posicao == 5) {
    lcd.setCursor(posicao, 1);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(posicao, 1);
    lcd.print(n2Usuario);
  }
  if (posicao == 6) {
    lcd.setCursor(posicao, 1);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(posicao, 1);
    lcd.print(n3Usuario);
  }
  if (posicao == 7) {
    lcd.setCursor(posicao, 1);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(posicao, 1);
    lcd.print(n4Usuario);
  }
  if (posicao == 8) {
    lcd.setCursor(posicao, 1);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(posicao, 1);
    lcd.print(n5Usuario);
  }
  if (posicao == 9) {
    lcd.setCursor(posicao, 1);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(posicao, 1);
    lcd.print(n6Usuario);
  }
  if (posicao == 10) {
    lcd.setCursor(posicao, 1);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(posicao, 1);
    lcd.print(n7Usuario);
  }
  if (posicao == 11) {
    lcd.setCursor(posicao, 1);
    lcd.print(" ");
    delay(100);
    lcd.setCursor(posicao, 1);
    lcd.print(n8Usuario);
  }
}

void verificaBotao () { //verifica se algum botão foi pressionado  
  if (digitalRead(B1) == HIGH) {  //move o cursor para a esquerda
    posicao -= 1;
    if (posicao < 4) {
      posicao = 12;
    }
    delay(100);
  }

  if (digitalRead(B2) == HIGH) {  //verifica posição do cursor, dps soma o valor dessa posição;
    if (posicao == 4) {
      n1Usuario += 1;
    }
    if (posicao == 5) {
      n2Usuario += 1;
    }
    if (posicao == 6) {
      n3Usuario += 1;
    }
    if (posicao == 7) {
      n4Usuario += 1;
    }
    if (posicao == 8) {
      n5Usuario += 1;
    }
    if (posicao == 9) {
      n6Usuario += 1;
    }
    if (posicao == 10) {
      n7Usuario += 1;
    }
    if (posicao == 11) {
      n8Usuario += 1;
    }

    if (n1Usuario > 9) {
      n1Usuario = 0;
    }
    if (n2Usuario > 9) {
      n2Usuario = 0;
    }
    if (n3Usuario > 9) {
      n3Usuario = 0;
    }
    if (n4Usuario > 9) {
      n4Usuario = 0;
    }
    if (n5Usuario > 9) {
      n5Usuario = 0;
    }
    if (n6Usuario > 9) {
      n6Usuario = 0;
    }
    if (n7Usuario > 9) {
      n7Usuario = 0;
    }
    if (n8Usuario > 9) {
      n8Usuario = 0;
    }
    delay(100);
  }

  if (digitalRead(B3) == HIGH) {  //verifica posição do cursor, dps subtrai o valor dessa posição;
    if (posicao == 4) {
      n1Usuario -= 1;
    }
    if (posicao == 5) {
      n2Usuario -= 1;
    }
    if (posicao == 6) {
      n3Usuario = 1;
    }
    if (posicao == 7) {
      n4Usuario -= 1;
    }
    if (posicao == 8) {
      n5Usuario -= 1;
    }
    if (posicao == 9) {
      n6Usuario -= 1;
    }
    if (posicao == 10) {
      n7Usuario -= 1;
    }
    if (posicao == 11) {
      n8Usuario -= 1;
    }


    if (n1Usuario < 0) {
      n1Usuario = 9;
    }
    if (n2Usuario < 0) {
      n2Usuario = 9;
    }
    if (n3Usuario < 0) {
      n3Usuario = 9;
    }
    if (n4Usuario < 0) {
      n4Usuario = 9;
    }
    if (n5Usuario < 0) {
      n5Usuario = 9;
    }
    if (n6Usuario < 0) {
      n6Usuario = 9;
    }
    if (n7Usuario < 0) {
      n7Usuario = 9;
    }
    if (n8Usuario < 0) {
      n8Usuario = 9;
    }
    delay(100);
  }

  if (digitalRead(B4) == HIGH) {  //move o cursor para a direita
    posicao += 1;
    if (posicao > 12) {
      posicao = 4;
    }
    delay(100);
  }

  if (digitalRead(B5) == HIGH) {  //confere os valores do usuario
    tentativas += 1;
    confereValores();

    if (resultadoFinal) {
      ganhaJogo();
    }
    delay(500);
  }

  if (digitalRead(B6) == HIGH) {  //reinicia o jogo
    reiniciaJogo();
    delay(500);
  }

  lcd.setCursor(4, 1);
  lcd.print(n1Usuario);
  lcd.print(n2Usuario);
  lcd.print(n3Usuario);
  lcd.print(n4Usuario);
  lcd.print(n5Usuario);
  lcd.print(n6Usuario);
  lcd.print(n7Usuario);
  lcd.print(n8Usuario);
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
  lcd.print("Acerte a senha!");
  converte();
  lcd.setCursor(4, 1);
  lcd.print(n1Usuario);
  lcd.print(n2Usuario);
  lcd.print(n3Usuario);
  lcd.print(n4Usuario);
  lcd.print(n5Usuario);
  lcd.print(n6Usuario);
  lcd.print(n7Usuario);
  lcd.print(n8Usuario);


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
  numAleatorio();

  while (statusJogo = 0) {
    cursor();
  }
}
