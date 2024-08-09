#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> 

#include <Servo.h>

Servo microservo;
unsigned long millisTempoled = millis();

int BUZZER = 9;
int led = 7;

//link baixar biblioteca lcd:  https://robojax.com/learn/arduino/?vid=robojax-LCD2004-I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

 
int distancia = 0;
int sensorluz = 0;
int switch1 = 10;
int switch2 = 11;
int switch3 = 12;
int switch4 = 13;

int statusD1 = 0;
int statusD2 = 0;
int statusD3 = 0;
int statusD4 = 0;

unsigned long timer = 0;

unsigned long tempoLimite = 60000;
int faseAtual = 1;
boolean perdeu = false;

int enderecoRecordeCronometro = 0;
int recordeCronometro = 0;
int enderecoRecordeFase = 0;
int recordeFase = 0;
boolean carroequilibrado = false;


void takeOnMe () {  //toca Take On Me (A-HA)
  #define NOTE_B0  31
  #define NOTE_C1  33
  #define NOTE_CS1 35
  #define NOTE_D1  37
  #define NOTE_DS1 39
  #define NOTE_E1  41
  #define NOTE_F1  44
  #define NOTE_FS1 46
  #define NOTE_G1  49
  #define NOTE_GS1 52
  #define NOTE_A1  55
  #define NOTE_AS1 58
  #define NOTE_B1  62
  #define NOTE_C2  65
  #define NOTE_CS2 69
  #define NOTE_D2  73
  #define NOTE_DS2 78
  #define NOTE_E2  82
  #define NOTE_F2  87
  #define NOTE_FS2 93
  #define NOTE_G2  98
  #define NOTE_GS2 104
  #define NOTE_A2  110
  #define NOTE_AS2 117
  #define NOTE_B2  123
  #define NOTE_C3  131
  #define NOTE_CS3 139
  #define NOTE_D3  147
  #define NOTE_DS3 156
  #define NOTE_E3  165
  #define NOTE_F3  175
  #define NOTE_FS3 185
  #define NOTE_G3  196
  #define NOTE_GS3 208
  #define NOTE_A3  220
  #define NOTE_AS3 233
  #define NOTE_B3  247
  #define NOTE_C4  262
  #define NOTE_CS4 277
  #define NOTE_D4  294
  #define NOTE_DS4 311
  #define NOTE_E4  330
  #define NOTE_F4  349
  #define NOTE_FS4 370
  #define NOTE_G4  392
  #define NOTE_GS4 415
  #define NOTE_A4  440
  #define NOTE_AS4 466
  #define NOTE_B4  494
  #define NOTE_C5  523
  #define NOTE_CS5 554
  #define NOTE_D5  587
  #define NOTE_DS5 622
  #define NOTE_E5  659
  #define NOTE_F5  698
  #define NOTE_FS5 740
  #define NOTE_G5  784
  #define NOTE_GS5 831
  #define NOTE_A5  880
  #define NOTE_AS5 932
  #define NOTE_B5  988
  #define NOTE_C6  1047
  #define NOTE_CS6 1109
  #define NOTE_D6  1175
  #define NOTE_DS6 1245
  #define NOTE_E6  1319
  #define NOTE_F6  1397
  #define NOTE_FS6 1480
  #define NOTE_G6  1568
  #define NOTE_GS6 1661
  #define NOTE_A6  1760
  #define NOTE_AS6 1865
  #define NOTE_B6  1976
  #define NOTE_C7  2093
  #define NOTE_CS7 2217
  #define NOTE_D7  2349
  #define NOTE_DS7 2489
  #define NOTE_E7  2637
  #define NOTE_F7  2794
  #define NOTE_FS7 2960
  #define NOTE_G7  3136
  #define NOTE_GS7 3322
  #define NOTE_A7  3520
  #define NOTE_AS7 3729
  #define NOTE_B7  3951
  #define NOTE_C8  4186
  #define NOTE_CS8 4435
  #define NOTE_D8  4699
  #define NOTE_DS8 4978
  #define REST      0

  int tempo = 140;

  int melody[] = {
    NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
    REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
    NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
    REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
    NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
        
    REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
    NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
    REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
    NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
    REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
        
    NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
    REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,    
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

    tone(BUZZER, melody[thisNote], noteDuration * 0.9);

    //adicionar função para piscar leds

    delay(noteDuration);

    noTone(BUZZER);
  }
}


void somPerdeu() {  //reproduz o áudio de quando o jogador perdeu
  //definir o som que o buzzer irá fazer
}

void atualizaTimer () { //atualiza o valor da variável 'timer'
  timer = millis();
}


void diminuiLimite () { //diminui o tempo limite
  tempoLimite -= 5000;
}

void verificaEquilibrio () { //verifica se o carro stá equilibrado
  if (carroequilibrado) {
    faseAtual++;
    diminuiLimite();
    timer = 0;
  }
}

void modoFase () { //roda o modo de jogo baseado em fases (provavelmente vai dar errado)
  while (!perdeu) {
    while (timer <= tempoLimite) {
      atualizaTimer();
      verificaEquilibrio();
    }
    if (timer > tempoLimite) {
      perdeu = true;
      somPerdeu();
      if (faseAtual > recordeFase) {
        EEPROM.write(enderecoRecordeFase, recordeFase);
        // EEPROM.commit();
        takeOnMe();
      }
    }
  }
}

unsigned long intervaloPiscar = 500;  // Intervalo desejado para piscar o LED em milissegundos
unsigned long ultimaTrocaEstado = 0;  // Armazena o tempo da última troca de estado do LED
bool modoFoiSelecionado = false; // Controla se o jogo está ativo
void modoHighscore () { //roda o modo de jogo baseado em durar mais tempo

  do{

  
  microservo.write(map(analogRead(A0), 0, 1023, 40, 140)); //move o servo motor com base na leitura do pino A0
 
  Serial.println(sensorluz);
  sensorluz = analogRead(A2); //lê o valor do sensor de luz que encontra no pino A2
  
  cronometro(); //chama o cronômetro para marcar o tempo;
  
  //criar função verificaSensor();
  if (sensorluz < 300 && ((millis() - millisTempoled) < 4000)) { 
    // do {
    //   digitalWrite(led, HIGH);
    //   // delay(200);
    //   digitalWrite(led, LOW);
    //   delay(200);
    // } while (((millis() - millisTempoled) < 4000) && (sensorluz > 300));

    if (millis() - ultimaTrocaEstado >= intervaloPiscar) {
      digitalWrite(7, !digitalRead(7));  // Inverte o estado do LED
      ultimaTrocaEstado = millis();      // Atualiza o tempo da última troca de estado
    }

  }
  if (sensorluz < 300 && ((millis() - millisTempoled) > 4000)) { // se a intesidade de luz no sensor for menor que 300 e o tempo for maior que 4 segundos
    carroequilibrado = true; //armazena que o carro foi equilibrado
    digitalWrite(7, HIGH); //liga o led
  } 
  else {
    if (sensorluz > 300) { //se o sensor de luz tiver com intesidade acima de 300 
      digitalWrite(7, LOW);  // led permanece desligado;
      millisTempoled = millis();  //millistempoled recebe o atual;
    }
  }
  }while(!carroequilibrado);
}

void modoHighscoreCronNoFim () { //roda o modo de jogo baseado em durar mais tempo(cronometro so aparece no fim)
  microservo.write(map(analogRead(A0), 0, 1023, 40, 140));
 
  Serial.println(sensorluz);  
  sensorluz = analogRead(A2);
  
  //criar função verificaSensor();
  if (sensorluz < 300 && ((millis() - millisTempoled) < 4000)) { 
    do {
      digitalWrite(led, HIGH);
      delay(200);
      digitalWrite(led, LOW);
      delay(200);
    } while (((millis() - millisTempoled) < 4000) && (sensorluz > 300));
  }
  if (sensorluz < 300 && ((millis() - millisTempoled) > 4000)) { 
    carroequilibrado = true;
    digitalWrite(7, HIGH);
  }
  else {
    if (sensorluz > 300) {
      digitalWrite(7, LOW); 
      millisTempoled = millis(); 
    }
  }
}

int ultimaGravacaoCronometro = 0;
bool lcdInicialLimpo = false; //Variavel para ver se o lcd ja foi limpo;
void cronometro () {  //faz a contagem do tempo e printa no lcd

  // //antes de mostrar na tela, verifica se a ultima vez que mandou gravar na tela passou pelo menos 1 segundo
  // if(millis() - ultimaGravacaoCronometro < 1000) return;
  // ultimaGravacaoCronometro = millis();
  
  // timer = millis();
  // unsigned long tempo = timer / 1000;
  // unsigned long minutos = int(tempo / 60);
  // unsigned long segundos = (tempo % 60);

  // lcd.clear();
  // lcd.print("tempo");
  // lcd.setCursor(0, 1); //colocar posição correta
  // lcd.print(minutos);
  // lcd.print(":");
  // if(segundos < 10){
  //   lcd.print("0");
  // }
  // lcd.print(segundos);
  // //delay(1000);


  if( !lcdInicialLimpo ) { //se o lcd não tiver sido limpo, vai limpar
    lcd.clear();
    lcdInicialLimpo = true;
  }

  lcd.setCursor(0, 0);
  lcd.print("Tempo");

 // Verifica se já passou 1 segundo desde a última atualização
  if (millis() - ultimaGravacaoCronometro < 1000) return;
  ultimaGravacaoCronometro = millis();
  
  unsigned long tempo = millis() / 1000;
  unsigned long minutos = tempo / 60;
  unsigned long segundos = tempo % 60;

  // Posiciona o cursor e imprime os minutos e segundos
  
  lcd.setCursor(0, 1); 
  if (minutos < 10) { //formata para exibir zeros a esquerda caso o numero seja menor que 10
    lcd.print("0");
  }
  lcd.print(minutos);
  lcd.print(":");
  if (segundos < 10) { //formata para exibir zeros a esquerda
    lcd.print("0");
  }
  lcd.print(segundos);

}

void zerarCronometro() {
  timer = 0; // Inicializa o cronômetro
  ultimaGravacaoCronometro = 0; // Inicializa o tempo da última gravação
}

int ultimaGravacaoTelaLinha1 = 0; 
void escreve(const char * texto){
  
    //antes de mostrar na tela, verifica se a ultima vez que mandou gravar na tela passou pelo menos 1 segundo
    if(millis() - ultimaGravacaoTelaLinha1 < 1000) return;
    ultimaGravacaoTelaLinha1 = millis();

    lcd.clear();
    lcd.home();
    lcd.print(texto);
}


void selecaoModos () {
  statusD1 = digitalRead(switch1);
  statusD2 = digitalRead(switch2);
  statusD3 = digitalRead(switch3);
  statusD4 = digitalRead(switch4);

  if (!statusD1) {
    //lcd.clear();
    //lcd.home();
    //lcd.print("Highscore");

      // if( !modoFoiSelecionado ){
      //   zerarCronometro();
      //   modoFoiSelecionado = true;
      // }else {
    modoHighscore();
    escreve("Ganhou!!");
    takeOnMe();
    
    
  }
  if (!statusD2) {
    //lcd.clear();
    //lcd.home();
    //lcd.print("Fases");
    escreve("Fases");
  }

  if (!statusD3) {
    //lcd.clear();
    //lcd.home();
    //lcd.print("Fases");

    escreve("highscore");

    //modoHighscore();
    modoHighscoreCronNoFim();

  }

  // if(digitalRead(switch3) == LOW){
  //   lcd.clear();
  //   lcd.home();
  //   lcd.print("Teste");

  //   modoHighscore();
  // }

  if(digitalRead(switch4) == LOW){
    cronometro();
  }
}

 
void setup() {
 
  //incializa a EEPROM
  EEPROM.begin();

  //recupera os recordes da EEPROM
  recordeCronometro = EEPROM.read(enderecoRecordeCronometro);
  recordeFase = EEPROM.read(enderecoRecordeFase);


  //microservo

  pinMode(A0, INPUT);
  microservo.attach(8, 550, 2100);
  Serial.begin(9600);
  pinMode(A2, INPUT);
  pinMode(7, OUTPUT);

 // Botões: 
  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);
  pinMode(switch3, INPUT_PULLUP);
  pinMode(switch4, INPUT_PULLUP);

  //Buzzer:
  pinMode(BUZZER, OUTPUT);

  //Lcd: 
  lcd.begin();   // INICIALIZA O DISPLAY LCD
  lcd.clear();
  lcd.backlight();
  lcd.clear();
 

  //Mensagem inicial no LCD: 
  lcd.setCursor(0, 0);
  lcd.print("#  CEFET  #");
  lcd.setCursor(0, 1);
  lcd.print("JogoDoEquilibrio");

}


void loop() {   
  selecaoModos();
}
 
 