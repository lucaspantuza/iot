//  Para Larissa



#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "multimidia.h"

#define B1 14   //aumenta
#define B2 27   //diminui
#define B3 26   //start
#define B4 25   //tirar
#define B5 33   //tirar
#define B6 32   //tirar
#define BUZZER 19

#define ledVd 16
#define ledVm 17
#define ledAz 4


LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x3F for a 20 chars and 4 line display



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
    /*NOTE_FS5,8, NOTE_FS5,8,/*NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
        
    REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
    NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
    REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
    NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
    REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
        
    NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
    REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,*/
        
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
  numSecreto = random(10);
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
  numSecreto = 0;
  numUsuario = 0;
  vidas = 5;
  erros = 0;
  tentativas = 0;
  resultado = 0;

  apagaLeds(ledVm, ledVd, ledAz);
}

void fechaJogo () {   //função que chama função exit(0);
  exit(0);
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

  if (digitalRead(B4) == HIGH) {
    som();
    fechaJogo();
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
  pinMode(B4, INPUT);
  pinMode(B5, INPUT);
  pinMode(B6, INPUT);
  pinMode(ledVd, OUTPUT);
  pinMode(ledVm, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Console serial
  Serial.begin(9600);
  Serial.println("inicio");

  // CONFIGURACAO INICIAL DO LCD ***********************
  lcd.init();  // initialize the lcd
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
