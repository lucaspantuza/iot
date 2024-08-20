//Para Larissa 


int x = 0;
int y = 0;

#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// set the LCD address to 0x3F for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define B1 14
#define B2 12
#define B3 32
#define B4 35

#define B5 15
#define B6 2

#define BUZZER 23

#define DIPS1 16
#define DIPS2 17
#define DIPS3 5
#define DIPS4 18

#define LED_AZUL 26
#define LED_AMARELO 27
#define LED_VERDE 25
#define LED_VERMELHO 33


//  Caracteres especiais
byte play[] = {
  B00000,
  B01000,
  B01100,
  B01110,
  B01111,
  B01110,
  B01100,
  B01000
};

byte yalp[] = {
  B00000,
  B00010,
  B00110,
  B01110,
  B11110,
  B01110,
  B00110,
  B00010
};//

byte caveira[] = {
  B00000,
  B01110,
  B10101,
  B11011,
  B01110,
  B01110,
  B00000,
  B00000
};

byte notaMusical1[] = {
  B00001,
  B00011,
  B00101,
  B01001,
  B01001,
  B01011,
  B11011,
  B11000
};

byte notaMusical2[] = {
  B00000,
  B00000,
  B00100,
  B00110,
  B00100,
  B01100,
  B01100,
  B00000
};

byte tetrisLCD[] = {
  B00111,
  B11010,
  B11000,
  B00001,
  B11101,
  B10001,
  B01101,
  B11000
};

byte maquina[] = {
  B11111,
  B10001,
  B10001,
  B11111,
  B10101,
  B11111,
  B11111,
  B11111
};

byte snow[] = {
  B01000,
  B11101,
  B01011,
  B00001,
  B00100,
  B01110,
  B00100,
  B10000
};//


//  Variáveis menu
int statusD1 = 0;
int statusD2 = 0;
int statusD3 = 0;
int statusD4 = 0;
int stateB5 = 0;

//  Variáveis e constantes presskill
int b1State = 0;
int b1LastState = 0;
int b2State = 0;
int b2LastState = 0;
int b3State = 0;
int b3LastState = 0;
int b4State = 0;
int b4LastState = 0;

int p1State = 1;  // Player states: 0=out, 1=in, 2=win;
int p2State = 1;
int p3State = 1;
int p4State = 1;
int p1Points = 0;
int p2Points = 0;
int p3Points = 0;
int p4Points = 0;
const int pointsToWin = 5;  // Points needed to win the game.

bool deadZone = false;
unsigned long dZTimerStart = 1;
const long dZTimerDuration = 5000;  // Duration of the timer in milliseconds

bool gameWin = false;
unsigned long winTimerStart = 0;
const long winTimerDuration = 250;  // Duration of the timer in milliseconds
int winLedState = LOW;  // State of the led of the winning player

unsigned long resetTimerStart = 0;
const long resetTimerDuration = 10000;  // Duration in milliseconds


//  Constantes simon
const int tamMemoria = 100;  // Número máximo de combinações ou fases de jogo
const int tempoCor = 1000;   // tempo de cada cor, 1000 millisegundos

// Endereço na EEPROM onde o recorde será armazenado
int enderecoRecorde = 0;
int recorde = 0;

//  Variáveis simon
int statusB1 = 0;   // Status dos botões
int statusB2 = 0;
int statusB3 = 0;
int statusB4 = 0;
int statusB5 = 0;
int statusB6 = 0;

int currentTime = 0;        // temporizadores
int lastTime = 0;

int demoLed = 0;          // Indicador de modo demonstração pré-jogo

int statusJogo = 0;       // 0 = modo demonstração ; 1 = modo Jogo
int memJogo[tamMemoria];  // array com sequencia de cores para jogar responder
int etapaJogo;            // 0 = introdução; 1 = jogo; 2 = perdeu; 3 = ganhou
int faseJogo = 1;         // evolução do jogador, vai até o valor de tamMemoria
int respJogador = 0;       // guarda resposta do jogador
int botaoPress = 0;       // variável para guardar botão pressionado pelo jogador
int perdeuJogo = 0;       // indicador para perdeu o jogo
int tempoJogador = 5000;  // Tempo da vez do jogador, para cada cor

//  FUNÇÕES
void luzinha () { //função para piscar as luzes aleatoriamente
  bool ligarLED_AZUL = random(2) == 1;
  bool ligarLED_AMARELO = random(2) == 1;
  bool ligarLED_VERDE = random(2) == 1;
  bool ligarLED_VERMELHO = random(2) == 1;

  apagaLeds();

  if (ligarLED_AZUL) {
    digitalWrite(LED_AZUL, HIGH);
  } /*else{
    digitalWrite(LED_AZUL, LOW);
  }*/
  if (ligarLED_AMARELO) {
    digitalWrite(LED_AMARELO, HIGH);
  } /*else{
    digitalWrite(LED_AMARELO, LOW);
  }*/
  if (ligarLED_VERDE) {
    digitalWrite(LED_VERDE, HIGH);
  } /*else{
    digitalWrite(LED_VERDE, LOW);
  }*/
  if (ligarLED_VERMELHO) {
    digitalWrite(LED_VERMELHO, HIGH);
  } /*else{
    digitalWrite(LED_VERMELHO, LOW);
  }*/
}

void takeOnMeSemLuzinha () { //toca Take On Me (não pisca os leds)
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

  // notes of the moledy followed by the duration.
  // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // !!negative numbers are used to represent dotted notes,
  // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
  int melody[] = {

    // Take on me, by A-ha
    // Score available at https://musescore.com/user/27103612/scores/4834399
    // Arranged by Edward Truong

    NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
    REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
    NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
    REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,    
  };

  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(BUZZER, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(BUZZER);
  }
}

void furElise() { //toca furElise //nota1
  #define NOTE_C4  262
  #define NOTE_E4  330
  #define NOTE_GS4 415
  #define NOTE_A4  440
  #define NOTE_B4  494
  #define NOTE_C5  523
  #define NOTE_D5  587
  #define NOTE_DS5 622
  #define NOTE_E5  659
  #define REST      0

  // change this to make the song slower or faster
  int tempo = 80;

  // change this to whichever pin you want to use
  int buzzer = 23;

  // notes of the moledy followed by the duration.
  // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // !!negative numbers are used to represent dotted notes,
  // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
  const int melody[] PROGMEM = {
    NOTE_DS5, 16, NOTE_E5, 16, NOTE_DS5, 16,
    NOTE_E5, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16,
    NOTE_A4, 8, REST, 16, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16,
      
    NOTE_B4, 8, REST, 16, NOTE_E4, 16, NOTE_GS4, 16, NOTE_B4, 16,
    NOTE_C5, 8, REST, 16, NOTE_E4, 16, NOTE_E5, 16,  NOTE_DS5, 16,
    NOTE_E5, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16,
    NOTE_A4, 8, REST, 16, NOTE_C4, 16, NOTE_E4, 16, NOTE_A4, 16,
    NOTE_B4, 8, REST, 16, NOTE_E4, 16, NOTE_C5, 16, NOTE_B4, 16,
    NOTE_A4, 8,
  };

  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;

  if (digitalRead(B1) == HIGH) {
    lcd.clear();
    lcd.home();
    lcd.write(0);
    lcd.print("Fur Elise");
    lcd.setCursor(0, 1);
    lcd.print("Beethoven ");
    lcd.write(4);

    // iterate over the notes of the melody.
    // Remember, the array is twice the number of notes (notes + durations)
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

      // calculates the duration of each note
      divider = pgm_read_word_near(melody+thisNote + 1);
      if (divider > 0) {
        // regular note, just proceed
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        // dotted notes are represented with negative durations!!
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5; // increases the duration in half for dotted notes
      }

      // we only play the note for 90% of the duration, leaving 10% as a pause
      tone(buzzer, pgm_read_word_near(melody+thisNote), noteDuration * 0.9);

      luzinha();

      // Wait for the specief duration before playing the next note.
      delay(noteDuration);
      encerraJogo();

      // stop the waveform generation before the next note.
      noTone(buzzer);

    }
    lcd.clear();
  }
}

void takeOnMe () { //toca Take On Me (pisca os leds)  //maquina
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

  // notes of the moledy followed by the duration.
  // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // !!negative numbers are used to represent dotted notes,
  // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
  int melody[] = {

    // Take on me, by A-ha
    // Score available at https://musescore.com/user/27103612/scores/4834399
    // Arranged by Edward Truong

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

  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(BUZZER, melody[thisNote], noteDuration * 0.9);

    luzinha(); //faz os LEDs piscarem aleatoriamente durante a música
    encerraJogo();

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(BUZZER);
  }
}

void takeOnMeDemo () { //toca Take On Me (pisca os leds)  //maquina
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

  // notes of the moledy followed by the duration.
  // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // !!negative numbers are used to represent dotted notes,
  // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
  int melody[] = {

    // Take on me, by A-ha
    // Score available at https://musescore.com/user/27103612/scores/4834399
    // Arranged by Edward Truong

    NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
    REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
    NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
    REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,       
  };

  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(BUZZER, melody[thisNote], noteDuration * 0.9);

    luzinha(); //faz os LEDs piscarem aleatoriamente durante a música

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(BUZZER);
  }
}

void theGodfather () {  //toca The Godfather Theme (O Poderoso Chefão)  //caveira
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


  // change this to make the song slower or faster
  int tempo = 80;

  // notes of the moledy followed by the duration.
  // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // !!negative numbers are used to represent dotted notes,
  // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
  int melody[] = {

    // The Godfather theme
    // Score available at https://musescore.com/user/35463/scores/55160

    REST, 4, REST, 8, REST, 8, REST, 8, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8, //1
    NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8, NOTE_G4, 8,
    NOTE_E4, 2, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8,
    NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_E4, 8, NOTE_DS4, 8,
    
    NOTE_D4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8, //5
    NOTE_B4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8,
    NOTE_A4, 2, NOTE_C4, 8, NOTE_C4, 8, NOTE_G4, 8, 
    NOTE_F4, 8, NOTE_E4, 8, NOTE_G4, 8, NOTE_F4, 8, NOTE_F4, 8, NOTE_E4, 8, NOTE_E4, 8, NOTE_GS4, 8,

    NOTE_A4, 2, REST,8, NOTE_A4, 8, NOTE_A4, 8, NOTE_GS4, 8, //9
    NOTE_G4, 2, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8, 
    NOTE_E4, 2, NOTE_E4, 8, NOTE_G4, 8, NOTE_E4, 8,
    NOTE_D4, 2, NOTE_D4, 8, NOTE_D4, 8, NOTE_F4, 8, NOTE_DS4, 8, 
    
    NOTE_E4, 2, REST, 8, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8, //13

    //repeats from 2
    NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8, NOTE_G4, 8, //2
    NOTE_E4, 2, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8,
    NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_E4, 8, NOTE_DS4, 8,
    
    NOTE_D4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8, //5
    NOTE_B4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8,
    NOTE_A4, 2, NOTE_C4, 8, NOTE_C4, 8, NOTE_G4, 8, 
    NOTE_F4, 8, NOTE_E4, 8, NOTE_G4, 8, NOTE_F4, 8, NOTE_F4, 8, NOTE_E4, 8, NOTE_E4, 8, NOTE_GS4, 8,

    NOTE_A4, 2, REST,8, NOTE_A4, 8, NOTE_A4, 8, NOTE_GS4, 8, //9
    NOTE_G4, 2, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8, 
    NOTE_E4, 2, NOTE_E4, 8, NOTE_G4, 8, NOTE_E4, 8,
    NOTE_D4, 2, NOTE_D4, 8, NOTE_D4, 8, NOTE_F4, 8, NOTE_DS4, 8, 
    
    NOTE_E4, 2 //13
  };

  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(BUZZER, melody[thisNote], noteDuration * 0.9);

    luzinha(); //faz os LEDs piscarem aleatoriamente durante a música

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    encerraJogo();

    // stop the waveform generation before the next note.
    noTone(BUZZER);
  }
}

void silentNight () { //toca Silent Night //snow
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


  // change this to make the song slower or faster
  int tempo = 140;


  // notes of the moledy followed by the duration.
  // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // !!negative numbers are used to represent dotted notes,
  // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
  int melody[] = {

    // Silent Night, Original Version
    // Score available at https://musescore.com/marcsabatella/scores/3123436

    NOTE_G4,-4, NOTE_A4,8, NOTE_G4,4,
    NOTE_E4,-2, 
    NOTE_G4,-4, NOTE_A4,8, NOTE_G4,4,
    NOTE_E4,-2, 
    NOTE_D5,2, NOTE_D5,4,
    NOTE_B4,-2,
    NOTE_C5,2, NOTE_C5,4,
    NOTE_G4,-2,

    NOTE_A4,2, NOTE_A4,4,
    NOTE_C5,-4, NOTE_B4,8, NOTE_A4,4,
    NOTE_G4,-4, NOTE_A4,8, NOTE_G4,4,
    NOTE_E4,-2, 
    NOTE_A4,2, NOTE_A4,4,
    NOTE_C5,-4, NOTE_B4,8, NOTE_A4,4,
    NOTE_G4,-4, NOTE_A4,8, NOTE_G4,4,
    NOTE_E4,-2, 
    
    NOTE_D5,2, NOTE_D5,4,
    NOTE_F5,-4, NOTE_D5,8, NOTE_B4,4,
    NOTE_C5,-2,
    NOTE_E5,-2,
    NOTE_C5,4, NOTE_G4,4, NOTE_E4,4,
    NOTE_G4,-4, NOTE_F4,8, NOTE_D4,4,
    NOTE_C4,-2,
    NOTE_C4,-1,
    
    
    
    
    
    
  };

  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(BUZZER, melody[thisNote], noteDuration * 0.9);

    luzinha(); //faz os LEDs piscarem aleatoriamente durante a música

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    encerraJogo();

    // stop the waveform generation before the next note.
    noTone(BUZZER);
  }
}

void brahms () { //toca Brahms’ Lullaby (Wiegenlied)  //nota2
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


  // change this to make the song slower or faster
  int tempo = 76;

  // notes of the moledy followed by the duration.
  // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // !!negative numbers are used to represent dotted notes,
  // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
  int melody[] = {

    // Wiegenlied (Brahms' Lullaby)
    // Score available at https://www.flutetunes.com/tunes.php?id=54

    NOTE_G4, 4, NOTE_G4, 4, //1
    NOTE_AS4, -4, NOTE_G4, 8, NOTE_G4, 4,
    NOTE_AS4, 4, REST, 4, NOTE_G4, 8, NOTE_AS4, 8,
    NOTE_DS5, 4, NOTE_D5, -4, NOTE_C5, 8,
    NOTE_C5, 4, NOTE_AS4, 4, NOTE_F4, 8, NOTE_G4, 8,
    NOTE_GS4, 4, NOTE_F4, 4, NOTE_F4, 8, NOTE_G4, 8,
    NOTE_GS4, 4, REST, 4, NOTE_F4, 8, NOTE_GS4, 8,
    NOTE_D5, 8, NOTE_C5, 8, NOTE_AS4, 4, NOTE_D5, 4,

    NOTE_DS5, 4, REST, 4, NOTE_DS4, 8, NOTE_DS4, 8, //8
    NOTE_DS5, 2, NOTE_C5, 8, NOTE_GS4, 8,
    NOTE_AS4, 2, NOTE_G4, 8, NOTE_DS4, 8,
    NOTE_GS4, 4, NOTE_AS4, 4, NOTE_C5, 4,
    NOTE_AS4, 2, NOTE_DS4, 8, NOTE_DS4, 8,
    NOTE_DS5, 2, NOTE_C5, 8, NOTE_GS4, 8,
    NOTE_AS4, 2, NOTE_G4, 8, NOTE_DS4, 8,
    NOTE_AS4, 4, NOTE_G4, 4, NOTE_DS4, 4,
    NOTE_DS4, 2

  };

  // sizeof gives the number of bytes, each int valsmaue is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(BUZZER, melody[thisNote], noteDuration * 0.9);

    luzinha(); //faz os LEDs piscarem aleatoriamente durante a música

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    encerraJogo();

    // stop the waveform generation before the next note.
    noTone(BUZZER);
  }
}

void tetris () { //toca tema de tetris e verifica modo de jogo  //tetris
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
  #define REST 0

  // change this to make the song slower or faster
  int tempo=144; 

  // notes of the moledy followed by the duration.
  // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // !!negative numbers are used to represent dotted notes,
  // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
  int melody[] = {

    //Based on the arrangement at https://www.flutetunes.com/tunes.php?id=192
    
    NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
    NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
    NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
    NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,8,  NOTE_A4,4,  NOTE_B4,8,  NOTE_C5,8,

    NOTE_D5, -4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
    NOTE_E5, -4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
    NOTE_B4, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
    NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST, 4,

    NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
    NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
    NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
    NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,8,  NOTE_A4,4,  NOTE_B4,8,  NOTE_C5,8,

    NOTE_D5, -4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
    NOTE_E5, -4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
    NOTE_B4, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
    NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST, 4,
    

    NOTE_E5,2,  NOTE_C5,2,
    NOTE_D5,2,   NOTE_B4,2,
    NOTE_C5,2,   NOTE_A4,2,
    NOTE_GS4,2,  NOTE_B4,4,  REST,8, 
    NOTE_E5,2,   NOTE_C5,2,
    NOTE_D5,2,   NOTE_B4,2,
    NOTE_C5,4,   NOTE_E5,4,  NOTE_A5,2,
    NOTE_GS5,2,

  };

  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  int notes=sizeof(melody)/sizeof(melody[0])/2; 

  // this calculates the duration of a whole note in ms (60s/tempo)*4 beats
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody. 
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(BUZZER, melody[thisNote], noteDuration*0.9);

    luzinha(); //faz os LEDs piscarem aleatoriamente durante a música

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    encerraJogo();
    
    // stop the waveform generation before the next note.
    noTone(BUZZER);
  }
}


//  FUNÇÕES PRESSKILL
void lcdP1 () {
  lcd.home();
  lcd.print("Azul: ");
  if (p1State = 0) {
    lcd.write(3);
  }
  if (p1State = 1) {
    lcd.print(p1Points);
  }
}

void lcdP2 () {
  lcd.setCursor(0, 1);
  lcd.print("Amarelo: ");
  if (p2State = 0) {
    lcd.write(3);
  }
  if (p2State = 1) {
    lcd.print(p2Points);
  }
}

void lcdP3 () {
  lcd.setCursor(7, 0);
  lcd.print("Verde: ");
  if (p3State = 0) {
    lcd.write(3);
  }
  if (p3State = 1) {
    lcd.print(p3Points);
  }
}

void lcdP4 () {
  lcd.setCursor(5, 1);
  lcd.print("Vermelho: ");
  if (p4State = 0) {
    lcd.write(3);
  }
  if (p4State = 1) {
    lcd.print(p4Points);
  }
}

void lcdPresskill() {
  lcdP1();
  lcdP2();
  lcdP3();
  lcdP4();
}

int ButtonTest(int buttonPin, int state, int lastState, int playerState, int buttonNumber) {
  if (digitalRead(B5) == HIGH) {
    encerraJogo();
  }
  // Test if the state of the button is different from the last recorded state. If so, and the digitalRead is now HIGH, the button has been pressed.
  state = digitalRead(buttonPin);
  if (state != lastState) {
    if (state == HIGH) {
      Serial.print("Button ");
      Serial.print(buttonNumber);
      Serial.println(" was pushed");
      if (playerState == 1 and !gameWin) {
        ButtonPressed(buttonNumber);
      }
    }
    delay(50); // delay a little bit to avoid bouncing
  }
  return state;
}

void ButtonPressed(int playerNumber) {
  lcdPresskill();

  if (deadZone == true) {
    // If a player hit the button during the deadzone, they loose.
    if (playerNumber == 1) { p1State = 0; }
    if (playerNumber == 2) { p2State = 0; }
    if (playerNumber == 3) { p3State = 0; }
    if (playerNumber == 4) { p4State = 0; }
  }
  else {
    // If a player hit the button after the deadzone they get a point.
    // They win if they have enough points.
    if (playerNumber == 1) {
      p1Points++;
      if (p1Points >= pointsToWin) { PlayerWin(2, 0, 0, 0); }
    }
    if (playerNumber == 2) {
      p2Points++;
      if (p2Points >= pointsToWin) { PlayerWin(0, 2, 0, 0); }
    }
    if (playerNumber == 3) {
      p3Points++;
      if (p3Points >= pointsToWin) { PlayerWin(0, 0, 2, 0); }
    }
    if (playerNumber == 4) {
      p4Points++;
      if (p4Points >= pointsToWin) { PlayerWin(0, 0, 0, 2); }
    }
    // Start the deadzone!
    dZTimerStart = millis();
    deadZone = true;
  }
  
  // When only one player is left, that player wins. (The sum of the player states is 1 when only one player is in the game)
  if (p1State + p2State + p3State + p4State == 1) {
    if (p1State == 1) { PlayerWin(2, 0, 0, 0); }
    if (p2State == 1) { PlayerWin(0, 2, 0, 0); }
    if (p3State == 1) { PlayerWin(0, 0, 2, 0); }
    if (p4State == 1) { PlayerWin(0, 0, 0, 2); }
  }
}

void PlayerLed(int playerState, int ledPin) {
  int ledState;
  if (playerState == 0) { ledState = LOW; }
  if (playerState == 1) { ledState = HIGH; }
  if (playerState == 2) { ledState = winLedState; }
  digitalWrite(ledPin, ledState);
}

void PlayerWin(int p1NewState, int p2NewState, int p3NewState, int p4NewState) {
  winTimerStart = millis();
  resetTimerStart = millis();
  gameWin = true;
  // Set the state of the player to the given states. Winning player gets 2 (win), everone else gets 0 (loose).
  p1State = p1NewState;
  p2State = p2NewState;
  p3State = p3NewState;
  p4State = p4NewState;

  apagaLeds();
  lcd.clear();
  if (p1State == 2) {
    lcd.setCursor(2, 0);
    lcd.print("Jogador azul");
    lcd.setCursor(1, 1);
    lcd.print("ganhou o jogo!");
    digitalWrite(LED_AZUL, HIGH);
  } else if (p2State == 2) {
    lcd.home();
    lcd.print("Jogador amarelo");
    lcd.setCursor(1, 1);
    lcd.print("ganhou o jogo!");
    digitalWrite(LED_AMARELO, HIGH);
  } else if (p3State == 2) {
    lcd.setCursor(2, 0);
    lcd.print("Jogador verde");
    lcd.setCursor(1, 1);
    lcd.print("ganhou o jogo!");
    digitalWrite(LED_VERDE, HIGH);
  } else if (p4State == 2) {
    lcd.home();
    lcd.print("Jogador vermelho");
    lcd.setCursor(1, 1);
    lcd.print("ganhou o jogo!");
    digitalWrite(LED_VERMELHO, HIGH);
  }
  takeOnMeSemLuzinha();
  lcd.clear();
}

void WinTimer() {
  if (millis() - winTimerStart >= winTimerDuration) {
    winTimerStart = millis();
    if (winLedState == LOW) {
      winLedState = HIGH;
    } else {
      winLedState = LOW;
    }
  }
}

void ResetTimer() {
  if (millis() - resetTimerStart >= resetTimerDuration) {
    // Reset all important variables so the game can be played again.
    p1State = 1;
    p2State = 1;
    p3State = 1;
    p4State = 1;
    p1Points = 0;
    p2Points = 0;
    p3Points = 0;
    p4Points = 0;
    deadZone = false;
    gameWin = false;
    dZTimerStart = 0;
    winTimerStart = 0;
    resetTimerStart = 0;
  }
}

void DeadZoneTimer() {
  if (millis() - dZTimerStart >= dZTimerDuration) {
    deadZone = false;
  }
}

void Debug() {
  /*
  Serial.print("b1State = ");
  Serial.print(b1State);
  Serial.print(" | b2State = ");
  Serial.print(b2State);
  Serial.print(" | b3State = ");
  Serial.print(b3State);
  Serial.print(" | b4State = ");
  Serial.println(b4State);
  delay(10);
  */

  Serial.print("p1State = ");
  Serial.print(p1State);
  Serial.print(" | p2State = ");
  Serial.print(p2State);
  Serial.print(" | p3State = ");
  Serial.print(p3State);
  Serial.print(" | p4State = ");
  Serial.print(p4State);
  Serial.print(" | timer = ");
  Serial.print(millis() - dZTimerStart);
  Serial.print(" | deadZone = ");
  Serial.println(deadZone);
}


//  FUNÇÕES SIMON
void modoDemo() {
  lcd.setCursor(4, 0);
  lcd.print("PRESSIONE");
  lcd.setCursor(4, 1);
  lcd.print("UM BOTAO");


  currentTime = millis();
  if ((currentTime - lastTime) > 100) {
    demoLed++;
    if (demoLed > 9) {
      demoLed = 1;
    }
    lastTime = currentTime;
  }
  switch (demoLed) {
    case 1:
      apagaLeds();
      digitalWrite(LED_VERMELHO, HIGH);
      break;
    case 2:
      digitalWrite(LED_AMARELO, HIGH);
      break;
    case 3:
      digitalWrite(LED_VERDE, HIGH);
      break;
    case 4:
      digitalWrite(LED_AZUL, HIGH);
      break;
    case 5:
      digitalWrite(LED_VERMELHO, LOW);
      break;
    case 6:
      digitalWrite(LED_AMARELO, LOW);
      break;
    case 7:
      digitalWrite(LED_VERDE, LOW);
      break;
    case 8:
      digitalWrite(LED_AZUL, LOW);
      break;
    case 9:
      apagaLeds();
      break;
    default:
      apagaLeds();
      break;
  }
  delay (100);
}

// Função Modo Jogo, dividida em duas partes, inicialização e Jogo propriamente dito
void modoJogo() {
  switch (etapaJogo) {
    case 0:
      inicioJogo();   // Faz efeito de leds de inicialização
      etapaJogo++;
      break;
    case 1:
      turnoArduino();
      turnoJogador();
      break;
  }
  delay (100);
}

// Função de efeitos de início do jogo e carregamento da memória
void inicioJogo() {
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("SIMON");
  Serial.println("Iniciando Jogo...");
  for (int i = 0; i < 10; i++) {
    digitalWrite(LED_VERMELHO, LOW);
    delay(40);
    digitalWrite(LED_AMARELO, HIGH);
    delay(40);
    digitalWrite(LED_VERDE, LOW);
    delay(40);
    digitalWrite(LED_AZUL, HIGH);
    delay(40);
    digitalWrite(LED_VERMELHO, HIGH);
    delay(40);
    digitalWrite(LED_AMARELO, LOW);
    delay(40);
    digitalWrite(LED_VERDE, HIGH);
    delay(40);
    digitalWrite(LED_AZUL, LOW);
    delay(40);
  }
  digitalWrite(LED_AMARELO, HIGH);
  digitalWrite(LED_AZUL, HIGH);
  delay(1000);

  // sorteia memoria
  for (int i = 0; i < tamMemoria ; i++) {
    memJogo[i] = random(1, 5);              // randomiza cores: 1 = Verm; 2 = Amar; 3 = Verd; 4 = Azul
  }

  // Zera variáveis
  apagaLeds();
  respJogador = 0;
  perdeuJogo = 0;
  faseJogo = 1;
}

// Função de Jogo para turno do Arduino, acender os Leds conforme memória e fase atual
void turnoArduino() {
  lcd.clear();
  lcd.print("Fase atual -> ");
  lcd.print(faseJogo);
  lcd.setCursor(0,1);
  lcd.print("Recorde -> ");
  lcd.print(recorde);

  Serial.print("Turno Arduino, Fase: ");
  Serial.println(faseJogo);       // variável faseJogo é o quanto o Jogador vai avançando, Arduino exibe até onde Jogador está

  for (int i = 0; i < faseJogo ; i++) {
    switch (memJogo[i]) {
      case 1:
        acendeLeds(1, 0, 0, 0);
        break;
      case 2:
        acendeLeds(0, 1, 0, 0);
        break;
      case 3:
        acendeLeds(0, 0, 1, 0);
        break;
      case 4:
        acendeLeds(0, 0, 0, 1);
        break;
      default:
        acendeLeds(0, 0, 0, 0);
        break;
    }
    delay(tempoCor);
    apagaLeds();
    delay(100);
  }
}

// Função de Jogo para o turno do Jogador,
void turnoJogador() {
  lcd.clear();
  lcd.print("Fase atual -> ");
  lcd.print(faseJogo);
  lcd.setCursor(0,1);
  lcd.print("Recorde -> ");
  lcd.print(recorde);

  Serial.print("Turno Jogador, Fase: ");
  Serial.println(faseJogo);

  int terminoTurno = 0;

  // Para cada fase alcançada, jogador tem que repetir sequencia do Arduino
  for (int i = 0 ; i < faseJogo ; i++) {
    botaoPress = leituraBotoesJogo(i);    // Checa botão pressionado pelo jogador
    if (botaoPress == 1) {    // Pressionou corretamente
      Serial.println("Resposta certa");
      terminoTurno = 1;
      delay (100);
    } else {                  // Errou
      Serial.println("Resposta errada, Perdeu o jogo!");
      perdeuJogo == 1;
      statusJogo = 0;
      etapaJogo = 0;
      perdeJogo();
      break;
    }
  }
  delay(500);
  faseJogo++;             // Incrementa fase
  if (faseJogo == sizeof(memJogo) / sizeof(memJogo[0])) {
    ganhouJogo();     // ganhou jogo e faz efeito do ganhador
  }
  apagaLeds();
}

// Função para ler botões no modo demonstação, com lógica para sair do modo se pressionou botão
void leituraBotoes() {
  statusB4 = digitalRead(B4);
  statusB2 = digitalRead(B2);
  statusB2 = digitalRead(B3);
  statusB1 = digitalRead(B1);
  statusB5 = digitalRead(B5);
  statusB6 = digitalRead(B6);
  if (statusJogo == 0) {
    if (statusB4 || statusB2 || statusB3 || statusB1) { // algum botão foi pressionado
      apagaLeds();
      demoLed = 1;
      statusJogo = 1;
    }
    if (statusB5) {
      encerraJogo();
    }
  }
  delay(50);
}

// Função para leitura dos botões durante jogo, inclui debounce para evitar leituras espúrias
int leituraBotoesJogo(int fase) {
  int botao = 0;
  int debounce = 0;
  int tempoTurno = 0;
  int inicioTurno = millis();
  while (botao == 0 || debounce == 0) {   // fica dentro do while enquanto não pressionar botão e debounce acabar
    statusB4 = digitalRead(B4);
    statusB2 = digitalRead(B2);
    statusB3 = digitalRead(B3);
    statusB1 = digitalRead(B1);
    statusB5 = digitalRead(B5);
    statusB6 = digitalRead(B6);
    if (statusB4) {
      botao = 1;
      somVM();
    }
    if (statusB2) {
      botao = 2;
      somAM();
    }
    if (statusB3) {
      botao = 3;
      somVD();
    }
    if (statusB1) {
      botao = 4;
      somAZ();
    }
    if (statusB5) {
      encerraJogo();
    }
    acendeLeds(statusB4, statusB2, statusB3, statusB1);
    // Faz debounce, só sai do while se botão foi depressionado
    if (statusB4 == 0 && statusB2  == 0 && statusB2  == 0 && statusB2  == 0 && botao > 0 ) {
      debounce = 1;
    }
    delay(100);
    tempoTurno = millis();
    if ((tempoTurno - inicioTurno) > tempoJogador) return 0;  // Tempo de 5 segundos excedido
  }
  // confere se botão pressionado foi o correto e retorna com resultado
  if (botao == memJogo[fase]) {
    return 1;     // Acertou
  } else {
    return 0;     // Errou
  }
}

// Função com efeitos de Perdeu o Jogo
void perdeJogo () {
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("Errou!");
  somPerdeu();
  if (faseJogo > recorde) {
    recorde = faseJogo - 1;
    lcd.setCursor(0, 0);
    lcd.print("Recorde batido!");
    lcd.setCursor(0, 1);
    lcd.print("Novo recorde->");
    lcd.print(recorde);
    takeOnMeDemo();
    // EEPROM.write(enderecoRecorde, recorde);
    // EEPROM.commit();  // Isso é importante para gravar os dados na EEPROM
  }
  Serial.println("perdeJogo()");
  Serial.print("Pontuação atingida: ");
  Serial.println(faseJogo);
  Serial.print("Recorde: ");
  Serial.println(recorde);


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fase -> ");
  lcd.print(faseJogo);
  lcd.setCursor(0,1);
  lcd.print("Recorde -> ");
  lcd.print(recorde);

  for (int i = 0; i < 15; i++) {
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AZUL, LOW);
    delay(100);
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_AZUL, HIGH);
    delay(100);
  }
  apagaLeds();
}

// Função com efeitos de Ganhou o Jogo
void ganhouJogo () {
  lcd.setCursor(4, 0);
  lcd.print("PARABENS");
  lcd.setCursor(2, 1);
  lcd.print("VOCE VENCEU!");

  takeOnMeDemo();
  Serial.print("ganhouJogo()");

  for (int i = 0; i < 20; i++) {
    digitalWrite(LED_VERMELHO, LOW);
    delay(40);
    digitalWrite(LED_AMARELO, HIGH);
    delay(40);
    digitalWrite(LED_VERDE, LOW);
    delay(40);
    digitalWrite(LED_AZUL, HIGH);
    delay(40);
    digitalWrite(LED_VERMELHO, HIGH);
    delay(40);
    digitalWrite(LED_AMARELO, LOW);
    delay(40);
    digitalWrite(LED_VERDE, HIGH);
    delay(40);
    digitalWrite(LED_AZUL, LOW);
    delay(40);
  }
  apagaLeds();
}

// Função para acender os Leds, conforme status passado pelas variáveis (apenas SIMON)
void acendeLeds(int ledVM, int ledAM, int ledVD, int ledAZ) {
  digitalWrite(LED_VERMELHO, ledVM);
  digitalWrite(LED_AMARELO, ledAM);
  digitalWrite(LED_VERDE, ledVD);
  digitalWrite(LED_AZUL, ledAZ);
}

// Função para apagar todos os Leds
void apagaLeds() {
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AZUL, LOW);
}


// Funções de Sons
void somVM() {
  tone(BUZZER,663);    
  delay(100);
  noTone(BUZZER);
}

void somAM() {;
  tone(BUZZER,440);    
  delay(100);
  noTone(BUZZER);
}

void somVD() {
  tone(BUZZER,468);    
  delay(100);
  noTone(BUZZER);
}

void somAZ() {
  tone(BUZZER,392);    
  delay(100);
  noTone(BUZZER);
}

void somPerdeu() {
  tone(BUZZER,200); 
    for (int i = 1; i <= 3; i++) { //quando errar a ordem
    digitalWrite(LED_AZUL, HIGH);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, HIGH);
    delay(200);
    digitalWrite(LED_AZUL, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    delay(200);
  }   
  noTone(BUZZER);
}


// ***MODOS DE JOGO***
void simon () { //função com o modo de jogo simon
  // Loop fica em dois whiles, ou está no modo pré-jogo (demonstração), ou está no modo jogo
  while (statusJogo != 1) {
    modoDemo();
    leituraBotoes();  // Se pressionar algum botão, sai do modo demo e entra no modo jogo
    Serial.print(".");
  }
  while (statusJogo == 1) {
    modoJogo();
  }
}

void presskill () { //função com o modo de jogo presskill
  while (gameWin == false){
    lcd.setCursor(3, 0);
    lcd.print("PRESSKILL");
    // Button press testing
    b1LastState = ButtonTest(B1, b1State, b1LastState, p1State, 1);
    b2LastState = ButtonTest(B2, b2State, b2LastState, p2State, 2);
    b3LastState = ButtonTest(B3, b3State, b3LastState, p3State, 3);
    b4LastState = ButtonTest(B4, b4State, b4LastState, p4State, 4);

    // deadzone timer
    if (deadZone == true) {
      DeadZoneTimer();
    }

    // win timer
    if (gameWin == true) {
      WinTimer();
      ResetTimer();
    }

    // Player states
    PlayerLed(p1State, LED_AZUL);
    PlayerLed(p2State, LED_AMARELO);
    PlayerLed(p3State, LED_VERDE);
    PlayerLed(p4State, LED_VERMELHO);

    // Debug to the console
    Debug();
  }
  return;
}

void verificaModo () {
  while (true) {
    statusD1 = digitalRead(DIPS1);  //SIMON
    statusD2 = digitalRead(DIPS2);  //PRESSKILL
    statusD3 = digitalRead(DIPS3);  //SONG
    statusD4 = digitalRead(DIPS4);  //DJ

    if (!statusD1) { //Simon
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("SIMON");
      digitalWrite(LED_AZUL, HIGH);
      digitalWrite(LED_AMARELO, HIGH);
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_VERMELHO, HIGH);
      delay(1000);
      apagaLeds();
      delay(500);
      lcd.clear();

      while (!statusD1) {
        lcd.clear();
        simon();
        statusD1 = digitalRead(DIPS1);
      }
      break;
    }
    if (!statusD2) { //Presskill
      lcd.clear();
      presskill();
      statusD2 = digitalRead(DIPS2);
      break;
    }
    if (!statusD3) { //Songs
      lcd.clear();

      while (!statusD3) {
        lcd.setCursor(4, 0);
        lcd.write(0);
        lcd.print("Music");
        lcd.write(5);
        lcd.setCursor(4, 1);
        lcd.write(4);
        lcd.print("Player");
        lcd.write(1);
        apagaLeds();
        furElise(); //B1
        if (digitalRead(B2) == HIGH) { //silent night
          lcd.clear();
          lcd.home();
          lcd.write(0);
          lcd.print("Silent Night");
          lcd.setCursor(0, 1);
          lcd.print("Frank Sinatra ");
          lcd.write(1);
          silentNight();
          lcd.clear();
        }
        if (digitalRead(B3) == HIGH) { //take on me
          lcd.clear();
          lcd.home();
          lcd.write(0);
          lcd.print("Take on me");
          lcd.setCursor(0, 1);
          lcd.print("A-HA ");
          lcd.write(7);
          takeOnMe();
          lcd.clear();
        }
        if (digitalRead(B4) == HIGH) {  //Brahms
          lcd.clear();
          lcd.home();
          lcd.write(0);
          lcd.print("Wiegenlied");
          lcd.setCursor(0, 1);
          lcd.print("Johannes Brahms ");
          lcd.write(5);
          brahms();
          lcd.clear();
        }
        if (digitalRead(B5) == HIGH) {  //Tetris's Theme Song
          lcd.clear();
          lcd.home();
          lcd.write(0);
          lcd.print("Tetris theme");
          lcd.setCursor(0, 1);
          lcd.print("Tetris ");
          lcd.write(6);
          tetris();
          lcd.clear();
        }
        if (digitalRead(B6) == HIGH) {  //The Godfather theme
          lcd.clear();
          lcd.home();
          lcd.write(0);
          lcd.print("The Godfather");
          lcd.setCursor(0, 1);
          lcd.print("Nino Rota ");
          lcd.write(3);
          theGodfather();
          lcd.clear();
        }
        statusD3 = digitalRead(DIPS3);
      }
      break;
    }
    if (!statusD4) { //DJ
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.write(0);
      lcd.print("DJ");
      lcd.write(1);
      apagaLeds();

      while (!statusD4) {
        if (digitalRead(B1) == HIGH) {
          tone(BUZZER,392);  
          digitalWrite(LED_AZUL, HIGH);  
          delay(100);
          noTone(BUZZER);
          digitalWrite(LED_AZUL, LOW);
        }
        if (digitalRead(B2) == HIGH) {
          tone(BUZZER,440);
          digitalWrite(LED_AMARELO, HIGH); 
          delay(100);
          noTone(BUZZER);
          digitalWrite(LED_AMARELO, LOW);
        }
        if (digitalRead(B3) == HIGH) {
          tone(BUZZER,468);
          digitalWrite(LED_VERDE, HIGH);  
          delay(100);
          noTone(BUZZER);
          digitalWrite(LED_VERDE, LOW);
        }
        if (digitalRead(B4) == HIGH) {
          tone(BUZZER,663);
          digitalWrite(LED_VERMELHO, HIGH);   
          delay(100);
          noTone(BUZZER);
          digitalWrite(LED_VERMELHO, LOW);
        }
        if (digitalRead(B5) == HIGH) {
          tone(BUZZER,178);
          digitalWrite(LED_AZUL, HIGH);
          digitalWrite(LED_AMARELO, HIGH);
          delay(100);
          noTone(BUZZER);
          digitalWrite(LED_AZUL, LOW);
          digitalWrite(LED_AMARELO, LOW);
        }
        if (digitalRead(B6) == HIGH) {
          tone(BUZZER,781);
          digitalWrite(LED_VERDE, HIGH);
          digitalWrite(LED_VERMELHO, HIGH);  
          delay(100);
          noTone(BUZZER);
          digitalWrite(LED_VERDE, LOW);
          digitalWrite(LED_VERMELHO, LOW);
        }
        statusD4 = digitalRead(DIPS4);
      }
      break;
    }
  }
}

void encerraJogo () {
  stateB5 = digitalRead(B5);

  if (stateB5) {
    apagaLeds();
    exit(0);
  }
}

void baratinha () {
  lcd.clear();
  lcd.home();
  lcd.print("1)SIMON  3)SONGS");
  lcd.setCursor(0, 1);
  lcd.print("2)PRESSKILL 4)DJ");

  verificaModo(); 
}


// the setup function runs once when you press reset or power the board
void setup() {
  // Inicializa a EEPROM
  EEPROM.begin(512);

  // Recupere o recorde da EEPROM
  recorde = EEPROM.read(enderecoRecorde);


  // CONFIGURACAO INICIAL DO LCD ***********************
  lcd.init();  // initialize the lcd
  lcd.backlight();
  // lcd.setCursor(COLUNA, LINHA);
  lcd.setCursor(5, 0);
  lcd.print("CEFET");
  lcd.setCursor(2, 1);
  lcd.print("Extensao OAs");
  delay(1000);


  // Configuracao de pinos dos botoes
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
  pinMode(B4, INPUT);
  pinMode(B5, INPUT);
  pinMode(B6, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  pinMode(DIPS1, INPUT_PULLUP);
  pinMode(DIPS2, INPUT_PULLUP);
  pinMode(DIPS3, INPUT_PULLUP);
  pinMode(DIPS4, INPUT_PULLUP);

  //criar caracter especial
  lcd.createChar(0, play);
  lcd.createChar(1, snow);
  lcd.createChar(3, caveira);
  lcd.createChar(4, notaMusical1);
  lcd.createChar(5, notaMusical2);
  lcd.createChar(6, tetrisLCD);
  lcd.createChar(7, maquina);


  // Console serial
  Serial.begin(9600);
  Serial.println("inicio");

  // Registro de tempo e inicializa randomização
  lastTime = millis();
  randomSeed(analogRead(0));

}


// the loop function runs over and over again forever
void loop() {
  baratinha();
}

// ACENDE|APAGA OS LEDS - LOW:apaga, HIGH:acende

