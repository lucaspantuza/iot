#include <HCSR04.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Servo.h>

#define TRIGGER 9
#define ECHO 8
#define SERVOPIN 11

UltraSonicDistanceSensor distanceSensor(TRIGGER, ECHO);
Adafruit_SSD1306 display = Adafruit_SSD1306();
Servo myservo;

int distancia = 0;
int distancia_novo = 0;
bool aberto = false;
bool abrir = false;

#define POS_ABERTO 180   //ANGULO DO SERVO
#define POS_FECHADO 110  //ANGULO DO SERVO
#define DELAY_TAMPA 5000
#define DELAY_LOOP 500
#define DEBUG true
#define CM_FECHAR 12

void setup() {

  //display
  Wire.begin();                               //INICIALIZA A BIBLIOTECA WIRE
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C
  display.setTextColor(WHITE);                //DEFINE A COR DO TEXTO
  display.setTextSize(1);                     //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.clearDisplay();                     //LIMPA AS INFORMAÇÕES DO DISPLAY


  if (DEBUG) Serial.begin(9600);

  myservo.attach(SERVOPIN);
  myservo.write(POS_FECHADO);
  abrir = false;
  aberto = false;

  pinMode(ECHO, INPUT);      //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(TRIGGER, OUTPUT);  //DEFINE O PINO COMO SAÍDA (ENVIA)
}

void loop() {

  distancia_novo = distanceSensor.measureDistanceCm();
  if (distancia_novo > 0)  //PULA ERRO
    distancia = distancia_novo;

  //imprime a distancia no display
  display.clearDisplay();     //LIMPA AS INFORMAÇÕES DO DISPLAY
  display.setCursor(10, 10);  //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
  display.print("Distancia: ");
  display.print(distancia);  //ESCREVE O TEXTO NO DISPLAY
  display.print(" cm");
  display.display();  //EFETIVA A ESCRITA NO DISPLAY
  display.setCursor(10, 25);


  if (DEBUG) Serial.println(distancia);

  if (distancia <= CM_FECHAR) {
    abrir = true;
  } else {
    abrir = false;
  }

  if (abrir && !aberto) {
    if (DEBUG) Serial.println(F("\tabrindo..."));
    display.print("Status: abrindo...");
    display.display();
    myservo.write(POS_ABERTO);
    delay(DELAY_TAMPA);
    aberto = true;
  } else if (!abrir && aberto) {
    if (DEBUG) Serial.println("\tfechando...");
    display.print("Status: fechando...");
    display.display();
    myservo.write(POS_FECHADO);
    delay(DELAY_TAMPA);
    aberto = false;
  } else {
    if (DEBUG) Serial.println("\tmantido");
    display.print("Status: mantido");
    display.display();
  }


  delay(DELAY_LOOP);
}
