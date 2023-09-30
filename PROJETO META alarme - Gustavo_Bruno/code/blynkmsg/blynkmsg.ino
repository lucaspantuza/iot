/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL29DcbQ7Ho"
#define BLYNK_TEMPLATE_NAME "sensor"
#define BLYNK_AUTH_TOKEN "Q7QMvpDIQ2uPNApWIlO_nHP77MS7xwPN"


/* Comment this out to disable prints and save space */
// #define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "BLYNK";
char pass[] = "28350507";

BlynkTimer timer;

#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bits/stdc++.h>

#include <iostream>
//A tela possui 16 caracteres
//1234567890123456
//=? tecle =

//D8     NAO DA como entrada, mas DA como saida
//Tx==1  NAO DA como entrada, mas DA como saida
//Rx==3
//sk==10
//S3==9

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte n_rows = 4;
const byte n_cols = 4;
char keys[n_rows][n_cols] = {{'1','2','3','+'},{'4','5','6','-'},{'7','8','9','*'},{'c','0','=','/'}};
byte colPins[n_rows] = {D6, D5, D4, D3};
byte rowPins[n_cols] = {10, 9, 3, D7};
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, n_rows, n_cols); 

int BUZZ_PIN = D8;

// recebe quantidade de milisegundos do bip que o buzz irá fazer
void buzzBip() {
  digitalWrite(BUZZ_PIN, HIGH);
  delay(50);
  digitalWrite(BUZZ_PIN, LOW);
}

//Declaramos os pinos que vamos a usar
int analogPin = A0;  //Analogico A5 para o sensor

//Declaramos uma variável para armazenar o valor que nos devolve o sensor
int val = 0;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, val);
}

char p[] = {{'P'},{'a'},{'r'},{'a'},{'d'},{'o'},{' '},{'a'},{'g'},{'o'},{'r'},{'a'},'\0'};

void escrevePrimeiraLinha(char vet[]){
  lcd.setCursor(0, 0);
  lcd.print("                "); //limpa
  lcd.setCursor(0, 0); //volta o cursor
  int i = 0;
  for(;vet[i] != '\0'; i++){
    lcd.print(vet[i]);
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(10,0,1,1));

  // Setup a function to be called every second
  timer.setInterval(100L, myTimerEvent);

  pinMode(analogPin, INPUT);  //Configuramos o pino analogico A5 como entrada
  // Serial.begin(9600);
  pinMode(BUZZ_PIN,OUTPUT);
  
  lcd.init();   // INICIALIZA O DISPLAY LCD
  lcd.clear();
  lcd.backlight(); // HABILITA O BACKLIGHT (LUZ DE FUNDO) 
  //lcd.noBacklight();
  
  //escrevePrimeiraLinha(p);
}



void limpa(){
  lcd.setCursor(0, 1); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print("                "); //limpa
  lcd.setCursor(0, 0);
  lcd.print("                "); //limpa
}

char m[] = {{'O'},{'P'},{'A'},{' '},{'m'},{'o'},{'v'},{'i'},{'m'},{'e'},{'n'},{'t'},{'o'},{'u'},{'!'},'\0'};

int op;

unsigned long ini = millis();
unsigned long now;

int mov = 0;

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer

  minhaLogica();
}

void minhaLogica() {
  val = analogRead(analogPin);  //Lemos o valor analogico que nos devolve o sensor
  Serial.println(val);  //Obtemos o valor do sensor por serial
  if (val > 100)                //Si o valor é maior que 100
  {
    Blynk.logEvent("alerta", "Possivel Pessoa desconhecida");
    if(op != 0){
      mov = 1;
      //limpa();
      escrevePrimeiraLinha(m);
      op = 0;
      //buzzBip();
      //lcd.backlight(); // HABILITA O BACKLIGHT (LUZ DE FUNDO) 
      ini = millis();
    }
  } else if(op != 1)                          //Se o valor é menor que 100
  {
    op = 1;
    now = millis();
    if(mov == 1 and now - ini >= 5000){
      mov = 0;
    }else{
      //lcd.noBacklight();
      //limpa();
      escrevePrimeiraLinha(p);
    }
  }
}