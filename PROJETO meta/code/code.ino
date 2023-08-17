//motor
#include <Stepper.h>

//tela
#include <Wire.h>             
#include <Adafruit_GFX.h>     
#include <Adafruit_SSD1306.h>  

//relogio
#include "RTCDS1307.h"

//-------------------

const int PassoPorVolta = 500;
const int BOTAO = 12;

Stepper MotorP(PassoPorVolta, 8, 10, 9, 11);
Adafruit_SSD1306 display = Adafruit_SSD1306();
RTCDS1307 rtc(0x68);

uint8_t year, month, weekday, day, hour, minute, second;
bool period = 0;
String m[12] = { "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro" };
String w[7] = { "Domingo", "Segunda-feira", "Terça-feira", "Quarta-feira", "Quinta-feira", "Sexta-feira", "Sábado" };

//-------------------

void setup() {
  Serial.begin(9600);

  pinMode(BOTAO, INPUT);

  MotorP.setSpeed(60);

  Wire.begin();                               //INICIALIZA A BIBLIOTECA WIRE
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C
  display.setTextColor(WHITE);                //DEFINE A COR DO TEXTO
  display.setTextSize(1);                     //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.clearDisplay();                     //LIMPA AS INFORMAÇÕES DO DISPLAY

  rtc.begin();
  // para acertar o relogio, descomente as linhas abaixo e atualize seus valores com os atuais
  // rtc.setDate(23, 8, 17);
  // rtc.setTime(4, 8, 50);
}

//-------------------

void loop() {

  //se pressionar o botao, da uma rodadinha no motor
  if (digitalRead(BOTAO) == HIGH) {
    while (digitalRead(BOTAO) == HIGH) {}
    Serial.println("press");
    MotorP.step(682 * 2);
    delay(1000);
  }


  //pega novas informacoes de relogio atualizadas
  rtc.getDate(year, month, day, weekday);
  rtc.getTime(hour, minute, second, period);


  //imprime no display
  display.clearDisplay();
  display.setCursor(10, 0);
  display.print(w[weekday - 1]);
  display.setCursor(10, 12);
  display.print(day, DEC);
  display.print(" / ");
  display.print(m[month - 1]);
  display.print(" / ");
  display.print(year + 2000, DEC);
  display.setCursor(10, 24);
  display.print("   ");
  if (hour <= 9) display.print("0");
  display.print(hour, DEC);
  display.print(":");
  if (minute <= 9) display.print("0");
  display.print(minute, DEC);
  display.print(":");
  if (second <= 9) display.print("0");
  display.print(second, DEC);
  display.print(period ? " PM" : " AM");
  display.display();
}