#include <HCSR04.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Servo.h>

#define TRIGGER 9
#define ECHO 8
#define SERVOPIN 6

UltraSonicDistanceSensor distanceSensor(TRIGGER, ECHO);
Adafruit_SSD1306 display = Adafruit_SSD1306();
Servo myservo;

int distancia = 0;


#define POS_ABERTO 175   //ANGULO DO SERVO
#define POS_FECHADO 110  //ANGULO DO SERVO
#define DELAY_LOOP 500
#define DEBUG true


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

  pinMode(ECHO, INPUT);      //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(TRIGGER, OUTPUT);  //DEFINE O PINO COMO SAÍDA (ENVIA)
}

void loop() {

  distancia = distanceSensor.measureDistanceCm();
  if (DEBUG) Serial.println(distancia);


  //imprime a distancia no display
  display.clearDisplay();     //LIMPA AS INFORMAÇÕES DO DISPLAY
  display.setCursor(10, 10);  //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
  display.print("Distancia: ");
  display.print(distancia);  //ESCREVE O TEXTO NO DISPLAY
  display.print(" cm");
  display.display();  //EFETIVA A ESCRITA NO DISPLAY
  display.setCursor(10, 25);


  if (distancia <= 12) {
    if (DEBUG) Serial.println(F("aberto"));
    display.print("aberto");
    display.display();
    myservo.write(POS_ABERTO);
  } else {
    if (DEBUG) Serial.println("fechado");
    display.print("fechado");
    display.display();
    myservo.write(POS_FECHADO);
  }


  delay(DELAY_LOOP);
}
