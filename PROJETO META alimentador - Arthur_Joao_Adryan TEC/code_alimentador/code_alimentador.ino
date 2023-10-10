int hora = 15;
int minuto = 59;
int intervaloM = 1;  //em minutos

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

int lastS;      //ultimo segundo que foi alimentado
int lastM;      //ultimo minuto que foi alimentado
int lastH;      //ultima hora que foi alimentado
int first = 0;  // começa 0, quando a primeira alimentação ocorrer, ele recebe 1

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
  //rtc.setDate(23, 10, 10);
  //rtc.setTime(15, 22, 8);

  vw_set_rx_pin(PIN_RF);  // Define o pino do Arduino como entrada de dados do receptor
  vw_setup(2000);         // Bits por segundo
  vw_rx_start();          // Inicializa o receptor
}

void alimentar(int vezes = 1) {
  MotorP.step(682 * 2 * vezes);
  delay(1000);
  lastH = hour;
  lastM = minute;
  lastS = second;
  first = 1;
}

//-------------------

void loop() {

  //se pressionar o botao, da uma rodadinha no motor
  if (digitalRead(BOTAO) == HIGH) {
    while (digitalRead(BOTAO) == HIGH) {}
    Serial.println("press");
    alimentar();
  }


  //pega novas informacoes de relogio atualizadas
  rtc.getDate(year, month, day, weekday);
  rtc.getTime(hour, minute, second, period);

  uint8_t message[VW_MAX_MESSAGE_LEN];
  uint8_t msgLength = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(message, &msgLength)) {  // Non-blocking
    Serial.print("Recebido: ");
    for (int i = 0; i < msgLength; i++) {
      Serial.write(message[i]);
    }
    Serial.println();
  }



  if (message[0] == 'A') {
    alimentar(1);
  } else if (message[0] == 'B') {
    alimentar(2);
  } else if (message[0] == 'C') {
    alimentar(3);
  } else if (message[0] == 'D') {
    alimentar(4);
  }
  message[0] = ' ';



  //imprime no display
  if (first == 0) {
    display.clearDisplay();
    display.setCursor(10, 0);
    display.print("   ");
    if (hour <= 9) display.print("0");
    display.print(hour, DEC);
    display.print(":");
    if (minute <= 9) display.print("0");
    display.print(minute, DEC);
    display.print(":");
    if (second <= 9) display.print("0");
    display.print(second, DEC);
    display.setCursor(10, 12);
    display.print("Ultima Alimentacao: ");
    display.setCursor(10, 24);
    display.print("   ");
    display.print("Aguardando...");
    display.display();
  } else {
    display.clearDisplay();
    display.setCursor(10, 0);
    display.print("   ");
    if (hour <= 9) display.print("0");
    display.print(hour, DEC);
    display.print(":");
    if (minute <= 9) display.print("0");
    display.print(minute, DEC);
    display.print(":");
    if (second <= 9) display.print("0");
    display.print(second, DEC);
    display.setCursor(10, 12);
    display.print("Ultima Alimentacao: ");
    display.setCursor(10, 24);
    display.print("   ");
    if (lastH <= 9) display.print("0");
    display.print(lastH);
    display.print(":");
    if (lastM <= 9) display.print("0");
    display.print(lastM);
    display.print(":");
    if (lastS <= 9) display.print("0");
    display.print(lastS);
    display.display();
  }


  if ((hour == hora) && (minute == minuto) && (second == 0)) {
    display.clearDisplay();
    display.setCursor(5, 0);
    display.print("Alimentador Acionado");
    display.setCursor(5, 15);
    display.print("Automaticamente");
    display.display();
    alimentar();
    int total = intervaloM + minuto;
    int aux = floor(total / 60);
    if (total > 59) {
      minuto = (60 * aux) - total;
      hora = hora + aux;
    } else {
      minuto = intervaloM + minuto;
    }
    Serial.print("Próxima alimentação automática: ");
    Serial.print(hora);
    Serial.print(":");
    Serial.print(minuto);
    Serial.println();
  }
}