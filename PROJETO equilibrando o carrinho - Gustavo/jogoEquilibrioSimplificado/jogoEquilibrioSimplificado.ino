#include <EEPROM.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>


Servo microservo;                               //Objeto para controlar o servo motor
Adafruit_SSD1306 display = Adafruit_SSD1306();  //OBJETO DO TIPO Adafruit_SSD1306


//Variáveis de controle do tempo e estado do LED
int ultimaGravacaoCronometro = 0;         // Ultima gravacao do cronometro
unsigned long millisTempoled = millis();  // Armazena o tempo atual em milissegundos desde o início do programa
unsigned long intervaloPiscar = 500;      // Intervalo desejado para piscar o LED em milissegundos
unsigned long ultimaTrocaEstado = 0;      // Armazena o tempo da última troca de estado do LED
boolean carroequilibrado = false;         //inicia estado como não equilibrado
unsigned long timer = 0;                  // Armazena o tempo decorrido para controle de cronômetro e temporizadores.
int startCronometro;                      //Define a variavel para controle de zerar o cronometro
int sensorluz = 0;                        //Define a variavel sensor luz para controlar a luminosidade recebida
long tempo = 0;                           //Armazena o tempo decorrido para controle de cronômetro e temporizadores.

// Endereço na EEPROM onde o recorde será armazenado
int enderecoRecorde = 0;
int recorde = 0;


#define POTENTIOMETER_PIN 15
#define BUZZER_PIN 25
#define LED_PIN 33
#define SERVO_PIN 26
#define LDR_PIN 34
#define CHAVE1_PIN 12
#define CHAVE2_PIN 14




void acendeLed() {
  digitalWrite(LED_PIN, HIGH);
}

void apagaLed() {
  digitalWrite(LED_PIN, LOW);
}

void salvaRecorde() {
  if ((millis() - startCronometro) > recorde) {
    display.clearDisplay();
    display.setCursor(5, 5);          // Define o cursor na posição (0, 0)
    display.print("Novo Recorde:   ");  // Imprime um texto fixo
    display.print(ultimaGravacaoCronometro);             // Imprime o valor da variável

    display.setCursor(5, 20);            // Define o cursor na posição (0, 0)
    display.print("Recorde antigo:   ");  // Imprime um texto fixo
    display.print(recorde);             // Imprime o valor da variável

    display.display();  // Exibe o conteúdo do buffer no display

    recorde = millis() - ultimaGravacaoCronometro;
    //Serial.println("salvaRecorde()");
    EEPROM.write(enderecoRecorde, recorde);
    EEPROM.commit();  // Isso é importante para gravar os dados na EEPROM
  }
}


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

    acendeLed();

    //adicionar função para piscar leds

    delay(noteDuration);

    apagaLed();

    noTone(BUZZER_PIN);
  }
}


void ganhaJogo() {
  display.clearDisplay();
  display.setCursor(30, 10);
  display.print("Voce ganhou!!!");
  display.display();
  // takeOnMe();
  delay(1000);
  salvaRecorde();
  delay(1000);
  display.clearDisplay();
  
}


void somPerdeu() {  //reproduz o áudio de quando o jogador perdeu
  //definir o som que o buzzer irá fazer
}

void atualizaTimer() {  //atualiza o valor da variável 'timer'
  timer = millis();
}


void jogo() {  //roda o modo de jogo baseado em durar mais tempo
  
  do {
    int potenciometroValor = map(analogRead(POTENTIOMETER_PIN), 2500, 0, 0, 68); //2500
  
    microservo.write(potenciometroValor);  //move o servo motor com base na leitura do pino A0 
    // Serial.print("Potenciometro:");
    // Serial.println(potenciometroValor);
    // Serial.println("Max:70");
    // Serial.println("Min:-44");
    
    //Serial.println(sensorluz);

    sensorluz = analogRead(LDR_PIN);  //lê o valor do sensor de luz que encontra no pino A2
    Serial.print("Sensor de luz: ");
    Serial.println(sensorluz);
    cronometro();  //chama o cronômetro para marcar o tempo;

    //Pisca o LED enquanto o sensor de luz estiver abaixo de 300 e o tempo for menor que 4 segundos
    if (sensorluz < 1500 && ((millis() - millisTempoled) < 4000)) {
      if (millis() - ultimaTrocaEstado >= intervaloPiscar) {  // Verifica se o tempo decorrido desde a última troca de estado do LED é maior ou igual ao intervalo definido para piscar o LED.
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));                     // Inverte o estado do LED
        digitalWrite(BUZZER_PIN, !digitalRead(BUZZER_PIN));                           //Inverte o estado do BUZZER
        ultimaTrocaEstado = millis();                         // Atualiza o tempo da última troca de estado

      }
      
    }

    // Se o sensor de luz estiver abaixo de 300 e o tempo for maior que 4 segundos, o carro está equilibrado
    if (sensorluz < 1500 && ((millis() - millisTempoled) > 4000)) {
      digitalWrite(BUZZER_PIN, LOW);
      ganhaJogo();
      carroequilibrado = true;  //armazena que o carro foi equilibrado
    } else {
      // Se o sensor de luz estiver acima de 300, desliga o LED e atualiza o tempo
      if (sensorluz > 1500) {        //se o sensor de luz tiver com intesidade acima de 300
        digitalWrite(LED_PIN, LOW);       // led permanece desligado;
        millisTempoled = millis();  //millistempoled recebe o atual;
      }
    }


  } while (carroequilibrado == false && digitalRead(CHAVE1_PIN) == LOW);  //Repete a função enquanto carro não esta equilibrado e o pino 1 encontra ativo
  
  display.setCursor(5,10);
  escreve("Reinicie...");
  display.display();

  
}


int tempoInicio;

void salvaTempoInicio() {
  tempoInicio = millis();
}




bool cronometroZerado = false;
bool displayInicialLimpo = false;  //Variavel para ver se o lcd ja foi limpo;
void cronometro() {                //faz a contagem do tempo e printa no lcd

  if (!displayInicialLimpo) {  //se o lcd não tiver sido limpo, vai limpar
    display.clearDisplay();
    displayInicialLimpo = true;
  }

  if(!cronometroZerado){
    // startCronometro = millis() - ultimaGravacaoCronometro;
    startCronometro = millis() - tempoInicio;

    cronometroZerado = true;
  }
  
  // Antes de mostrar na tela, verifica se a ultima vez que mandou gravar na tela passou pelo menos 1 segundo
 
  if (millis() - ultimaGravacaoCronometro < 1000) return;
  ultimaGravacaoCronometro = millis();

  //timer = millis();
  // unsigned long tempo = timer / 1000;
  // unsigned long tempo = millis() / 1000;
  unsigned long tempo = (millis() - startCronometro) / 1000;
  unsigned long minutos = tempo / 60;
  unsigned long segundos = tempo % 60;


  display.setCursor(10,5);
  escreve("Tempo: ");
  // Posiciona o cursor e imprime os minutos e segundos
  display.setCursor(10, 20);
  if (minutos < 10) {  //formata para exibir zeros a esquerda caso o numero seja menor que 10
    display.print("0");
  }
  display.print(minutos);
  display.print(":");

  if (segundos < 10) {  //formata para exibir zeros a esquerda
    display.print("0");
  
  }
  display.print(segundos);
  
  display.display();  
}


int ultimaGravacaoTelaLinha1 = 0;
void escreve(const char* texto) {

  //Antes de mostrar na tela, verifica se a ultima vez que mandou gravar na tela passou pelo menos 1 segundo
  if (millis() - ultimaGravacaoTelaLinha1 < 1000) return;
  ultimaGravacaoTelaLinha1 = millis();

  display.clearDisplay();
  display.print(texto);
  // display.display();

}


void selecaoModos() {
  display.setCursor(50, 10);

  if (digitalRead(CHAVE1_PIN) == LOW) {
    delay(2000);
    jogo();

  } else if (digitalRead(CHAVE2_PIN) == LOW) {
    display.clearDisplay();
    display.setCursor(5, 5);
    display.print("Recorde atual: ");
    unsigned long tempo = recorde / 1000;
    unsigned long minutos = tempo / 60;
    unsigned long segundos = tempo % 60;

    display.setCursor(10, 20);
    if (minutos < 10) {  //formata para exibir zeros a esquerda caso o numero seja menor que 10
      display.print("0");
    }
    display.print(minutos);
    display.print(":");

    if (segundos < 10) {  //formata para exibir zeros a esquerda
      display.print("0");
    }
    display.print(segundos);
    display.display();  

  } else{
    carroequilibrado = false; //Força o jogo ter o status false para carrinhoequilibrado
    cronometroZerado = false;  //Força o jogo ter o status false para cronometroZerado
    display.clearDisplay();  //Limpa o display
    display.setCursor(7, 2); //Posiciona em x = 7 e y = 2
    display.print("Jogo"); //Imprime a String Jogo
    display.setCursor(5, 10); ///Posiciona em 5, 10
    display.print("<---");  //Imprime seta esquerda
    display.setCursor(85, 2); //Posiciona em 85, 2
    display.print("Score"); //Imprime a String Score
    display.setCursor(95, 10); //Posiciona em 95, 10
    display.print("--->");  //Imprime seta direita
    display.setCursor(15,20);  //Posiciona em 15, 20
    display.print("Selecione o modo"); // Imprime a String "Selecione o modo"
  }


  display.display();  //inicializa as impressões de fato na tela
}

void setup() {

  salvaTempoInicio();
  // Inicializa a EEPROM
  EEPROM.begin(512);

  // Recupere o recorde da EEPROM
  recorde = EEPROM.read(enderecoRecorde);


  microservo.attach(SERVO_PIN, 500, 2400);

  Serial.begin(9600);
 

  // Botões:

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
  display.setCursor(40, 3);
  display.print("# CEFET #");
  display.setCursor(10, 15);
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


void loop() {
  selecaoModos();
}
