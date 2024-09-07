#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

// Pinagem
#define POTENTIOMETER_PIN 15
#define BUZZER_PIN 25
#define LED_PIN 33
#define SERVO_PIN 26
#define LDR_PIN 34
#define CHAVE1_PIN 12
#define CHAVE2_PIN 14

// Constrantes de setup inicial
// Estes valores foram adquiridos na tentativa e erro
#define SERVO_POSICAO_MEIO 32
#define LDR_MIN 3200
#define LDR_MAX 4000


Servo microservo;                               //Objeto para controlar o servo motor
Adafruit_SSD1306 display = Adafruit_SSD1306();  //OBJETO DO TIPO Adafruit_SSD1306



void ganhaJogo(long tempoDecorrido) {

  // Le recorde anterior
  long recorde = eeprom();

  // Se ganhar vai tocar estes beeps (se for novo recorde, toca ainda mais)
  int qtdBeeps = 3;

  // Grava um novo record
  if (tempoDecorrido < recorde) {
    eeprom(tempoDecorrido);  //grava o recorde
    recorde = tempoDecorrido;
    qtdBeeps = 10;
  }

  // Telinha da vitoria
  display.clearDisplay();
  display.setCursor(25, 0);
  display.print("Voce ganhou!!!");
  display.setCursor(8, 12);
  display.print(converteTempo(tempoDecorrido) + " / SCORE " + converteTempo(recorde));
  display.setCursor(30, 24);
  display.print("Reinicie...");
  display.display();

  beep(qtdBeeps);
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

    //Pisca o LED enquanto o sensor de luz estiver abaixo de xxx e o tempo for menor que 4 segundos
    if (sensorluz < LDR_MIN && ((millis() - millisTempoled) < LDR_MAX)) {
      if (millis() - ultimaTrocaEstado >= intervaloPiscar) {  // Verifica se o tempo decorrido desde a última troca de estado do LED é maior ou igual ao intervalo definido para piscar o LED.
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));         // Inverte o estado do LED
        digitalWrite(BUZZER_PIN, !digitalRead(BUZZER_PIN));   //Inverte o estado do BUZZER
        ultimaTrocaEstado = millis();                         // Atualiza o tempo da última troca de estado
      }
    }

    // Se o sensor de luz estiver abaixo de 300 e o tempo for maior que 4 segundos, o carro está equilibrado
    if (sensorluz < LDR_MIN && ((millis() - millisTempoled) > LDR_MAX)) {
      ganhaJogo(tempoDecorrido);
      digitalWrite(LED_PIN, LOW);

      // Prende na telinha de vitoria ate que o usuario altere a posicao da chave seletora
      while (digitalRead(CHAVE1_PIN) == LOW) {
        delay(50);
      }

    } else {
      // Se o sensor de luz estiver acima de 300, desliga o LED e atualiza o tempo
      if (sensorluz > LDR_MIN) {     //se o sensor de luz tiver com intesidade acima de 300
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

  long tempoDecorrido = (millis() - tempoInicio) / 1000;

  // Antes de mostrar na tela, verifica se a ultima vez que mandou gravar na tela passou pelo menos 1 segundo
  if (millis() - ultimaGravacaoCronometro >= 1000) {
    display.clearDisplay();
    display.setCursor(50, 2);
    display.print("Tempo:");
    display.setCursor(40, 15);
    display.setTextSize(2);
    display.print(converteTempo(tempoDecorrido));
    display.setTextSize(1);
    display.display();
    ultimaGravacaoCronometro = millis();
  }

  return tempoDecorrido;
}

void setup() {
  Serial.begin(9600);

  EEPROM.begin(sizeof(int) + sizeof(int));  //alocacao da EEPROM
  eeprom(59, 59);                           //grava 59:59 para quando nao tem nada gravado ainda no arduino

  microservo.attach(SERVO_PIN, 500, 2400);

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
  int tempoLogoSegundos = 5;
  for (int i = 0; i < tempoLogoSegundos; i++) {
    display.clearDisplay();

    display.setCursor(0, 0);
    display.setTextSize(1);
    display.print(" ");
    display.print(tempoLogoSegundos - i);

    display.setCursor(40, 2);

    display.setTextSize(2);
    display.print("CEFET");
    display.setTextSize(1);

    display.setCursor(13, 22);
    display.print("Jogo do Equilibrio");
    display.display();
    delay(1000);
  }

  //Definição dos pinso de componentes
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(CHAVE1_PIN, INPUT_PULLUP);
  pinMode(CHAVE2_PIN, INPUT_PULLUP);
}

String converteTempo(long tempo) {
  String resposta = "";
  int minutos = int(tempo / 60);
  int segundos = tempo - (minutos * 60);

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

void eeprom(int minutos, int segundos) {
  EEPROM.write(0, minutos);
  EEPROM.write(sizeof(int), segundos);
}
void eeprom(long valor) {
  int minutos = int(valor / 60);
  int segundos = valor - (minutos * 60);
  eeprom(minutos, segundos);
}
long eeprom() {
  int minutos = 0;
  int segundos = 0;
  //EEPROM.get(0,minutos);
  //EEPROM.get(sizeof(int),segundos);
  minutos = EEPROM.read(0);
  segundos = EEPROM.read(sizeof(int));
  return (long)((minutos * 60) + segundos);
}

void beep() {
  beep(1);
}

void beep(int qtd) {
  for (int i = 0; i < qtd; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
}

void exibeRecordeNoDisplay() {
  display.clearDisplay();
  display.setCursor(30, 2);
  display.print("Recorde atual: ");
  display.setCursor(36, 15);
  display.setTextSize(2);
  display.print(converteTempo(eeprom()));
  display.setTextSize(1);
  display.display();
}

void loop() {

  // Caso tenha voltado ao loop principal (da chave), entao retorna os atuadores aos valores iniciais
  display.clearDisplay();
  microservo.write(SERVO_POSICAO_MEIO);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);




  if (digitalRead(CHAVE1_PIN) == LOW) {
    // MODO 1 - chave selecao esquerda
    // jogo de fato
    jogo();



  } else if (digitalRead(CHAVE2_PIN) == LOW) {
    // MODO 2 - chave selecao direita
    // apenas mostra o record do jogo salvo na eprom
    exibeRecordeNoDisplay();

    // Gambiarra para zerar o record do jogo gravado na EEPROM
    // Para zerar, tem que estar no modo que exibe recorde, e entao leva o
    // potenciometro para o extremo MIN, extremo MAX, extremo MIN e extremo MAX
    int potenciometroValor;
    int fase = 0;
    while (fase < 4 && (digitalRead(CHAVE2_PIN) == LOW)) {
      potenciometroValor = map(analogRead(POTENTIOMETER_PIN), 2500, 0, 0, 10);
      if ((potenciometroValor == 0 && (fase == 0 || fase == 2)) || (potenciometroValor == 10 && (fase == 1 || fase == 3))) {
        beep();
        fase++;
      }
      if (fase == 4) {
        eeprom(59, 59);
        exibeRecordeNoDisplay();
        fase = 0;  //permite novo resset
        beep(3);
      }
      delay(100);
    }

    //mesmo sem o procedimento de resset do record, fica em espera ate a saida pela chave
    // while (digitalRead(CHAVE2_PIN) == LOW) {
    //   delay(100);
    // }

  } else {
    // MODO 3 - chave selecao central
    // apenas mostra opcoes para selecao (direita e esquerda)
    display.clearDisplay();
    display.setCursor(15, 0);
    display.print("Selecione o modo:");
    display.setCursor(10, 14);
    display.print("Jogar");
    display.setCursor(10, 25);
    display.print((char)17);
    display.print(" ");
    display.print((char)17);
    display.print(" ");
    display.print((char)17);
    display.setCursor(92, 14);
    display.print("Score");
    display.setCursor(92, 25);
    display.print((char)16);
    display.print(" ");
    display.print((char)16);
    display.print(" ");
    display.print((char)16);
    display.display();

    // Fica em espera ate a troca da chave
    while ((digitalRead(CHAVE1_PIN) != LOW) && (digitalRead(CHAVE2_PIN) != LOW)) {
      delay(100);
    }
  }
}
