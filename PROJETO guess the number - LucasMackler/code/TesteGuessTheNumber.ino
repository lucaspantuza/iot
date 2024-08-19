//  Para Larissa



#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define B1 26   //aumenta 
#define B2 25   //diminui
#define B3 27   //enter

#define BUZZER 19

#define ledVd 16
#define ledVm 17
#define ledAz 4


LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x3F for a 20 chars and 4 line display

byte setaCima[] = {   //cria um caractere com uma seta para cima
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

byte setaBaixo[] = {  //cria um caractere com uma seta para baixo
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100
};

byte coracao[] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};

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
  B00000,
  B00100,
  B00110,
  B00100,
  B01100,
  B01100
};


int statusB1 = 0;
int statusB2 = 0;
int statusB3 = 0;
int statusB4 = 0;
int statusB5 = 0;
int statusB6 = 0;

int numSecreto = 0;
int numUsuario = 0;
int resultado = 0;
int vidas = 5;
int erros = 0;
int tentativas = 0;
int statusJogo = 0;

String strVidas = "";

void setColor(int red, int green, int blue) {
  analogWrite(ledVm, red);
  analogWrite(ledVd, green);
  analogWrite(ledAz, blue);
}

void apagaLeds (int red, int green, int blue) {
  setColor(0, 0, 0);
}

void corzinha (int red, int green, int blue) {
  red = random(255);
  green = random(255);
  blue = random(255);

  setColor(red, green , blue);
}

void takeOnMe () { //toca Take On Me 
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
    corzinha(ledVm, ledVd, ledAz);

    // stop the waveform generation before the next note.
    noTone(BUZZER);
  }
  apagaLeds(ledVm, ledVd, ledAz);
}

void som() {
  tone(BUZZER,663);    
  delay(100);
  noTone(BUZZER);
}

void luzinhaBranca(int red, int green, int blue) {
  setColor(50, 50, 50);
}

void luzinhaVerde (int red, int green, int blue) {
  setColor(255, 0, 0);
}

void luzinhaVermelha (int red, int green, int blue) {
  setColor(0, 255, 0);
  delay(100);
  apagaLeds(ledVm, ledVd, ledAz);
}

void converte () { //converte as vidas do usuário em string para printar no lcd
  strVidas = String(vidas);
}

void numAleatorio () {  //gera um número aleatório
  numSecreto = random(101);
}

void debounceStart () {  //impede que haja leituras erradas do botão start
  delay(500);
}

void debounceSeta () {  //impede que haja leituras erradas das setas
  delay(100);
}

void verificaResposta () {  //verifica a resposta do usuário
  tentativas++;

  if (numSecreto == numUsuario) {
    resultado = 1;
  }
  if (numSecreto < numUsuario) {
    vidas--;
    erros++;
    resultado = 2;
  }
  if (numSecreto > numUsuario) {
    vidas--;
    erros++;
    resultado = 3;
  }
  if (vidas <= 0) {
    resultado = 4;
  }
}

void reiniciaJogo () {  //função para reinciar o jogo
  numAleatorio();
  numUsuario = 0;
  vidas = 5;
  erros = 0;
  tentativas = 0;
  resultado = 0;

  apagaLeds(ledVm, ledVd, ledAz);
}

void ganhaJogo () { //função para quando ganhar o jogo
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Acertou!");
  lcd.setCursor(6, 1);
  lcd.write(5);
  lcd.write(4);
  lcd.write(5);
  lcd.write(4);
  
  takeOnMe();

  luzinhaVerde(ledVm, ledVd, ledAz);
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("PRESSIONE ");
  lcd.write(0);
  lcd.print(" ou ");
  lcd.write(1);
  lcd.setCursor(1, 1);
  lcd.print("PARA REINICIAR");
  apagaLeds(ledVm, ledVd, ledAz);

  reiniciaJogo();
}

void numMaior () {  //quando a tentativa do usuario for mais alta que o valor certo
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Mais baixo!");
  luzinhaVermelha(ledVm, ledVd, ledAz);
  
  lcd.setCursor(7, 1);
  lcd.print(numUsuario);
}

void numMenor () {  //quando a tentativa do usuario for mais baixa que o valor certo
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Mais alto!");
  luzinhaVermelha(ledVm, ledVd, ledAz);
  
  lcd.setCursor(7, 1);
  lcd.print(numUsuario);
}

void perdeJogo () { //função para quando ganhar o jogo
  lcd.clear();
  luzinhaVermelha(ledVm, ledVd, ledAz);
  lcd.setCursor(4, 0);
  lcd.print("Perdeu!");
  lcd.setCursor(5, 1);
  for (int i = 0; i < 5; i++) {
    lcd.write(3);
  }
  delay(3000);
  lcd.setCursor(0, 0);
  lcd.print("PRESSIONE ");
  lcd.write(0);
  lcd.print(" ou ");
  lcd.write(1);
  lcd.setCursor(1, 1);
  lcd.print("PARA REINICIAR");


  reiniciaJogo();
}

void verificaBotao () { //verifica se algum botão foi pressionado
  if (digitalRead(B1) == HIGH) {
    som();
    luzinhaBranca(ledVm, ledVd, ledAz);

    numUsuario += 1;
    if (numUsuario > 10) {
      numUsuario = 0;
    }
    converte();
    lcd.clear();
    lcd.home();
    for (int i = 1; i <= vidas; i++) {
      lcd.write(2);
    }
    for (int i = 1; i <= erros; i++) {
      lcd.write(3);
    }
    lcd.setCursor(7, 1);
    lcd.print(numUsuario);
    apagaLeds(ledVm, ledVd, ledAz);
    debounceSeta();
  }

  if (digitalRead(B2) == HIGH) {
    som();
    luzinhaBranca(ledVm, ledVd, ledAz);

    numUsuario -= 1;
    if (numUsuario < 0) {
      numUsuario = 10;
    }
    converte();
    lcd.clear();
    lcd.setCursor(0, 0);
    for (int i = 1; i <= vidas; i++) {
      lcd.write(2);
    }
    for (int i = 1; i <= erros; i++) {
      lcd.write(3);
    }
    lcd.setCursor(7, 1);
    lcd.print(numUsuario);
    apagaLeds(ledVm, ledVd, ledAz);
    debounceSeta();
  }

  if (digitalRead(B3) == HIGH) {
    som();
    
    verificaResposta();
    if (resultado == 1) {
      ganhaJogo();
    }
    if (resultado == 2) {
      numMaior();
    }
    if (resultado == 3) {
      numMenor();
    }
    if (resultado == 4) {
      perdeJogo();
    }
    debounceStart();
  }
}

void jogo () {
  numAleatorio();
  while (true) {
    verificaBotao();
  }
}


// the setup function runs once when you press reset or power the board
void setup() {
  // Configuracao de pinos dos botoes
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);

  pinMode(ledVd, OUTPUT);
  pinMode(ledVm, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Console serial
  Serial.begin(9600);
  Serial.println("inicio");

  // CONFIGURACAO INICIAL DO LCD ***********************
  lcd.begin();  // initialize the lcd
  lcd.backlight();
  lcd.createChar(0, setaCima);
  lcd.createChar(1, setaBaixo);
  lcd.createChar(2, coracao);
  lcd.createChar(3, caveira);
  lcd.createChar(4, notaMusical1);
  lcd.createChar(5, notaMusical2);


  luzinhaBranca(ledVm, ledVd, ledAz);

  // lcd.setCursor(COLUNA, LINHA);
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("CEFET");
  lcd.setCursor(2, 1);
  lcd.print("Extensao OAs");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Guess the number");
  delay(2000);
  lcd.clear();
  apagaLeds(ledVm, ledVd, ledAz);

  converte();
  lcd.setCursor(0, 0);
  //lcd.print("Vidas: " + strVidas);
  for (int i = 1; i <= vidas; i++) {
    lcd.write(2);
  }
  lcd.setCursor(7, 1);
  lcd.print(numUsuario);
}

// the loop function runs over and over again forever
void loop() {
  apagaLeds(ledVm, ledVd, ledAz);
  jogo();
}
