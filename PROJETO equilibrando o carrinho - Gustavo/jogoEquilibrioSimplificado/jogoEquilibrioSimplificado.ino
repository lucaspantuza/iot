#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

#define POTENTIOMETER_PIN 15
#define BUZZER_PIN 25
#define LED_PIN 33
#define SERVO_PIN 26
#define LDR_PIN 34
#define CHAVE1_PIN 12
#define CHAVE2_PIN 14




Servo microservo;                               //Objeto para controlar o servo motor
Adafruit_SSD1306 display = Adafruit_SSD1306();  //OBJETO DO TIPO Adafruit_SSD1306


void takeOnMe() {  //toca Take On Me (A-HA)  //TIRAR OQ N USA
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_FS5 740
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define REST 0

  int tempo = 140;

  int melody[] = {
    NOTE_FS5,
    8,
    NOTE_FS5,
    8,
    NOTE_D5,
    8,
    NOTE_B4,
    8,
    REST,
    8,
    NOTE_B4,
    8,
    REST,
    8,
    NOTE_E5,
    8,
    REST,
    8,
    NOTE_E5,
    8,
    REST,
    8,
    NOTE_E5,
    8,
    NOTE_GS5,
    8,
    NOTE_GS5,
    8,
    NOTE_A5,
    8,
    NOTE_B5,
    8,
    NOTE_A5,
    8,
    NOTE_A5,
    8,
    NOTE_A5,
    8,
    NOTE_E5,
    8,
    REST,
    8,
    NOTE_D5,
    8,
    REST,
    8,
    NOTE_FS5,
    8,
    REST,
    8,
    NOTE_FS5,
    8,
    REST,
    8,
    NOTE_FS5,
    8,
    NOTE_E5,
    8,
    NOTE_E5,
    8,
    NOTE_FS5,
    8,
    NOTE_E5,
    8,
  };

  int notes = sizeof(melody) / sizeof(melody[0]) / 2;

  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;

  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }

    tone(BUZZER_PIN, melody[thisNote], noteDuration * 0.9);

    digitalWrite(LED_PIN, HIGH);

    //adicionar função para piscar leds

    delay(noteDuration);

    digitalWrite(LED_PIN, LOW);

    noTone(BUZZER_PIN);
  }
}

void writeIntIntoEEPROM(int address, int number) {
  byte byte1 = number >> 8;
  byte byte2 = number & 0xFF;
  EEPROM.write(address, byte1);
  EEPROM.write(address + 1, byte2);
}

int readIntFromEEPROM(int address){
  byte byte1 = EEPROM.read(address);
  byte byte2 = EEPROM.read(address + 1);
  return (byte1 << 8) + byte2;
}

void ganhaJogo(int tempoDecorrido) {

  int recorde = EEPROM.read(0);

  digitalWrite(BUZZER_PIN, LOW);

  display.clearDisplay();
  display.setCursor(25, 0);
  display.print("Voce ganhou!!!");

  display.setCursor(8, 12);
  display.print(converteTempo(tempoDecorrido) + " / SCORE " + converteTempo(recorde));

  display.setCursor(30, 24);
  display.print("Reinicie...");

  display.display();


  // Grava um novo record
  if (tempoDecorrido < recorde) {
    writeIntIntoEEPROM(0, tempoDecorrido);
  // TODO
    // TODO musica de novo record
  } else {
    // TODO musica de vitoria simples
    // TODO takeOnMe(); TIRAR A RAMPA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  }

  // Prende na telinha de vitoria ate que o usuario altere a posicao da chave seletora
  while (digitalRead(CHAVE1_PIN) == LOW) {
    delay(500);
  }
}



void jogo() {  //roda o modo de jogo baseado em durar mais tempo

  // Variaveis da funcao de piscar led
  unsigned long intervaloPiscar = 500;      // Intervalo desejado para piscar o LED em milissegundos
  unsigned long ultimaTrocaEstado = 0;      // Armazena o tempo da última troca de estado do LED
  unsigned long millisTempoled = millis();  // Armazena o tempo atual em milissegundos
  int potenciometroValor = NULL;
  int sensorluz = NULL;
  int tempoDecorrido = NULL;

  //Limpa o cronometro para entrar no jogo
  cronometro(true);

  for (;;) {

    // Faz leitura de sensor e potenciometro
    potenciometroValor = map(analogRead(POTENTIOMETER_PIN), 2500, 0, 0, 68);
    sensorluz = analogRead(LDR_PIN);  //lê o valor do sensor de luz

    //move o servo motor com base na leitura do pino A0
    microservo.write(potenciometroValor);

    //chama o cronômetro para marcar o tempo;
    tempoDecorrido = cronometro(false);

    //Pisca o LED enquanto o sensor de luz estiver abaixo de 1500 e o tempo for menor que 4 segundos
    if (sensorluz < 1500 && ((millis() - millisTempoled) < 4000)) {
      if (millis() - ultimaTrocaEstado >= intervaloPiscar) {  // Verifica se o tempo decorrido desde a última troca de estado do LED é maior ou igual ao intervalo definido para piscar o LED.
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));         // Inverte o estado do LED
        digitalWrite(BUZZER_PIN, !digitalRead(BUZZER_PIN));   //Inverte o estado do BUZZER
        ultimaTrocaEstado = millis();                         // Atualiza o tempo da última troca de estado
      }
    }

    // Se o sensor de luz estiver abaixo de 300 e o tempo for maior que 4 segundos, o carro está equilibrado
    if (sensorluz < 1500 && ((millis() - millisTempoled) > 4000)) {
      ganhaJogo(tempoDecorrido);

    } else {
      // Se o sensor de luz estiver acima de 300, desliga o LED e atualiza o tempo
      if (sensorluz > 1500) {        //se o sensor de luz tiver com intesidade acima de 300
        digitalWrite(LED_PIN, LOW);  // led permanece desligado;
        digitalWrite(BUZZER_PIN, LOW);
        millisTempoled = millis();  //millistempoled recebe o atual;
      }
    }

    // Situacao de quebra do laco infinito do jogo
    if (digitalRead(CHAVE1_PIN) != LOW) {
      return;
    }

    delay(50);
  }  //for
}


int tempoInicio;
int ultimaGravacaoCronometro = 0;  // Ultima gravacao do cronometro
int cronometro(bool zerar) {       //faz a contagem do tempo e printa no lcd

  if (zerar) {
    tempoInicio = millis();
  }

  int tempoDecorrido = (millis() - tempoInicio) / 1000;

  // Antes de mostrar na tela, verifica se a ultima vez que mandou gravar na tela passou pelo menos 1 segundo
  if (millis() - ultimaGravacaoCronometro >= 1000) {
    display.clearDisplay();
    display.setCursor(10, 5);
    display.print("Tempo: ");
    display.setCursor(10, 20);
    display.print(converteTempo(tempoDecorrido));
    display.display();
    ultimaGravacaoCronometro = millis();
  }

  return tempoDecorrido;
}





void setup() {

  // Inicializa a EEPROM
  // EEPROM.begin(512);
  // EEPROM.write(0, 6039);  // 6039 equivale a 99:99  //grava zero para quando nao tem nada gravado ainda no arduino
  writeIntIntoEEPROM(0, 6039);
  // EEPROM.commit();        // Isso é importante para gravar os dados na EEPROM
  Serial.println(readIntFromEEPROM(0));
//TODO sera que mantem a primeira gravacao aqui?
  microservo.attach(SERVO_PIN, 500, 2400);

  Serial.begin(9600);

  // Chave seletora
  pinMode(CHAVE1_PIN, INPUT_PULLUP);
  pinMode(CHAVE2_PIN, INPUT_PULLUP);

  //Buzzer:
  pinMode(BUZZER_PIN, OUTPUT);

  //Tela Display:
  Wire.begin();                               //INICIALIZA A BIBLIOTECA WIRE
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C
  display.setTextColor(WHITE);                //DEFINE A COR DO TEXTO
  display.setTextSize(1);                     //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.clearDisplay();                     //LIMPA AS INFORMAÇÕES DO DISPLAY

  //Mensagem inicial no LCD:
  display.clearDisplay();
  display.setCursor(40, 5);
  display.print("# CEFET #");
  display.setCursor(10, 20);
  display.print("Jogo do Equilibrio");
  display.display();
  delay(5000);

  //Definição dos pinso de componentes
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(CHAVE1_PIN, INPUT_PULLUP);
  pinMode(CHAVE2_PIN, INPUT_PULLUP);
}

String converteTempo(int tempo) {

  String resposta = "";

  int minutos = tempo / 60;
  int segundos = tempo % 60;

  if (minutos < 10) {  //formata para exibir zeros a esquerda caso o numero seja menor que 10
    resposta += "0";
  }
  resposta += String(minutos) + ":";
  if (segundos < 10) {  //formata para exibir zeros a esquerda
    resposta += "0";
  }
  resposta += String(segundos);
  return resposta;
}

void loop() {

  if (digitalRead(CHAVE1_PIN) == LOW) {
    // MODO 1 - chave selecao esquerda
    // jogo de fato
    jogo();



  } else if (digitalRead(CHAVE2_PIN) == LOW) {
    // MODO 2 - chave selecao direita
    // apenas mostra o record do jogo salvo na eprom

    display.clearDisplay();
    display.setCursor(5, 15);
    display.print("Recorde atual: ");
    display.print(converteTempo(EEPROM.read(0)));
    display.display();
//TODO zerar eprom


  } else {
    // MODO 3 - chave selecao central
    // apenas mostra opcoes para selecao (direita e esquerda)

    display.clearDisplay();             //Limpa o display
    display.setCursor(7, 0);            //Posiciona em x = 7 e y = 2
    display.print("Jogar");             //Imprime a String Jogo
    display.setCursor(5, 14);           ///Posiciona em 5, 10
    display.print("< < <");             //Imprime seta esquerda
    display.setCursor(92, 0);           //Posiciona em 85, 2
    display.print("Score");             //Imprime a String Score
    display.setCursor(95, 14);          //Posiciona em 95, 10
    display.print("> > >");             //Imprime seta direita
    display.setCursor(15, 25);          //Posiciona em 15, 20
    display.print("Selecione o modo");  // Imprime a String "Selecione o modo"
    display.display();                  //inicializa as impressões de fato na tela
  }



  delay(500);
}
