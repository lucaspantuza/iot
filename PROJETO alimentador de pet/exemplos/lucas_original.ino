#include <HCSR04.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>
#include <Servo.h>

#define TRIGGER 9
#define ECHO 8
#define SERVOPIN 6

UltraSonicDistanceSensor distanceSensor(TRIGGER, ECHO);
Adafruit_SSD1306 display = Adafruit_SSD1306();
Servo myservo;
RTC_DS3231 rtc;  //OBJETO DO TIPO RTC_DS3231

int distancia = 0;
int distancia_nova = 0;
DateTime now;

//DECLARAÇÃO DOS DIAS DA SEMANA
//char daysOfTheWeek[7][12] = { "Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado" };

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
  display.setCursor(10, 10);

  if (DEBUG) Serial.begin(9600);

  myservo.attach(SERVOPIN);
  myservo.write(POS_FECHADO);

  pinMode(ECHO, INPUT);      //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(TRIGGER, OUTPUT);  //DEFINE O PINO COMO SAÍDA (ENVIA)

  if (!rtc.begin()) {                                    // SE O RTC NÃO FOR INICIALIZADO, FAZ
    if (DEBUG) Serial.println("DS3231 não encontrado");  //IMPRIME O TEXTO NO MONITOR SERIAL
    display.print("DS3231 não encontrado");              //mostra tb no display
    display.display();                                   //EFETIVA A ESCRITA NO DISPLAY
    while (1) {}                                         //SEMPRE ENTRE NO LOOP
  }
  if (rtc.lostPower()) {                     //SE RTC FOI LIGADO PELA PRIMEIRA VEZ / FICOU SEM ENERGIA / ESGOTOU A BATERIA, FAZ
    if (DEBUG) Serial.println("DS3231 OK");  //IMPRIME O TEXTO NO MONITOR SERIAL
    display.print("DS3231 OK");              //mostra tb no display
    display.display();                       //EFETIVA A ESCRITA NO DISPLAY
    delay(3000);

    // REMOVA O COMENTÁRIO DE UMA DAS LINHAS ABAIXO PARA INSERIR AS INFORMAÇÕES ATUALIZADAS EM SEU RTC
    // so precisa caso vc queira ajustar o horario do RTC
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //CAPTURA A DATA E HORA EM QUE O SKETCH É COMPILADO
    //rtc.adjust(DateTime(2018, 9, 29, 15, 00, 45)); //(ANO), (MÊS), (DIA), (HORA), (MINUTOS), (SEGUNDOS)
  }
}

void loop() {

  distancia_nova = distanceSensor.measureDistanceCm();
  if(distancia_nova > 0) distancia = distancia_nova; //serve para descartar leituras de distancia negativa

  if (DEBUG) Serial.println(distancia);


  //imprime a distancia no display
  display.clearDisplay();     //LIMPA AS INFORMAÇÕES DO DISPLAY
  display.setCursor(10, 10);  //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
  display.print(distancia);   //ESCREVE O TEXTO NO DISPLAY
  display.print(" cm");

  //imprime a hora no display
  display.setCursor(10, 25);
  now = rtc.now();
  display.print(now.day(), DEC);
  display.print('/');
  display.print(now.month(), DEC);
  display.print('/');
  display.print(now.year(), DEC);
  display.print(" - ");
  //display.print(daysOfTheWeek[now.dayOfTheWeek()]);
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  display.print(':');
  display.print(now.second(), DEC);

  display.setCursor(70, 10);
  if (distancia <= 12) {
    if (DEBUG) Serial.println(F("ABERTO"));
    display.print("ABERTO");
    myservo.write(POS_ABERTO);
  } else {
    if (DEBUG) Serial.println("FECHADO");
    display.print("FECHADO");
    myservo.write(POS_FECHADO);
  }

  display.display();  //EFETIVA A ESCRITA NO DISPLAYF
  delay(DELAY_LOOP);
}
