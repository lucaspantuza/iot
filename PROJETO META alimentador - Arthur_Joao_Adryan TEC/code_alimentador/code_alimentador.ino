int hora = 17;
int minuto = 19;
int segundo = 0;
int intervaloM = 1;

//motor
#include <Stepper.h>

//tela
#include <Wire.h>             
#include <Adafruit_GFX.h>     
#include <Adafruit_SSD1306.h>  

//RF
#include <VirtualWire.h>

//relogio
#include "RTCDS1307.h"

//-------------------
#define PIN_RF 11

byte message[VW_MAX_MESSAGE_LEN];     // Armazena as mensagens recebidas
byte msgLength = VW_MAX_MESSAGE_LEN;  // Armazena o tamanho das mensagens

const int PassoPorVolta = 500;
const int BOTAO = 3;

Stepper MotorP(PassoPorVolta, 4, 6, 5, 7);
Adafruit_SSD1306 display = Adafruit_SSD1306();
RTCDS1307 rtc(0x68);

uint8_t year, month, weekday, day, hour, minute, second;
bool period = 0;
String m[12] = { "Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul", "Ago", "Set", "Out", "Nov", "Dez" };
String w[7] = { "Domingo", "Segunda-feira", "Terca-feira", "Quarta-feira", "Quinta-feira", "Sexta-feira", "Sabado" };

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

  vw_set_rx_pin(PIN_RF);  // Define o pino do Arduino como entrada de dados do receptor
  vw_setup(2000);         // Bits por segundo
  vw_rx_start();          // Inicializa o receptor
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
  minute = minute - 3;

   uint8_t message[VW_MAX_MESSAGE_LEN];
  uint8_t msgLength = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(message, &msgLength)) {  // Non-blocking
    Serial.print("Recebido: ");
    for (int i = 0; i < msgLength; i++) {
      Serial.write(message[i]);
    }
    Serial.println();
  }

  //imprime no display
  display.clearDisplay();
  display.setCursor(10, 0);
  display.print(w[weekday - 1]);
  display.setCursor(10, 12);
  display.print(day, DEC);
  display.print(" de ");
  display.print(m[month - 1]);
  display.print(" de ");
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
  display.display();

    if ((hour == hora) && (minute == minuto) && (second == segundo)) {  
      display.clearDisplay();
      display.setCursor(10, 0);
      display.print("IT'S FEEDING TIME!");
      display.display();
      MotorP.step(682 * 2);
      delay(5000);
      if (intervaloM + minuto > 59){
        minuto = (intervaloM + minuto) - 60;
        hora++
      }else{
        minuto = intervaloM + minuto;
      }

    }
}