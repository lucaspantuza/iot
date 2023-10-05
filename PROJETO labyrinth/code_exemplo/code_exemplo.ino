#include <Servo.h>

// Cria objeto para controlar o servo
Servo servomotorA;
Servo servomotorB;

// Especifica o pino usado para controlar o servo
int servoA = D6;
int servoB = D7;

int botaoCIMA = D4;       //laranja
int botaoBAIXO = D1;      //amarelo
int botaoDIREITA = D2;    //verde
int botaoESQUERDA = D3;   //marrom

void setup() {

  Serial.begin(115200);

  pinMode(botaoCIMA, INPUT_PULLUP);
  pinMode(botaoBAIXO, INPUT_PULLUP);
  pinMode(botaoDIREITA, INPUT_PULLUP);
  pinMode(botaoESQUERDA, INPUT_PULLUP);

  // Associa o pino ao objeto servomotor
  servomotorA.attach(servoA);
  servomotorB.attach(servoB);
}

void loop() {




  // // Teste dos botoes

  // if (digitalRead(botaoCIMA) == LOW)
  //   Serial.println("CIMA *");
  // else
  //   Serial.println("CIMA o");

  // if (digitalRead(botaoBAIXO) == LOW)
  //   Serial.println("BAIXO *");
  // else
  //   Serial.println("BAIXO o");

  // if (digitalRead(botaoDIREITA) == LOW)
  //   Serial.println("DIREITA *");
  // else
  //   Serial.println("DIREITA o");

  // if (digitalRead(botaoESQUERDA) == LOW)
  //   Serial.println("ESQUERDA *");
  // else
  //   Serial.println("ESQUERDA o");
  

  // Serial.println();
  // delay(100);



  //****************************************************



  // Teste dos motores

  servomotorA.write(0);
  delay(1000);
  servomotorA.write(45);
  delay(1000);
  servomotorA.write(90);
  delay(1000);
  servomotorA.write(135);
  delay(1000);
  servomotorA.write(180);
  delay(1000);

  servomotorB.write(0);
  delay(1000);
  servomotorB.write(45);
  delay(1000);
  servomotorB.write(90);
  delay(1000);
  servomotorB.write(135);
  delay(1000);
  servomotorB.write(180);
  delay(1000);


}
