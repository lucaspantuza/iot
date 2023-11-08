// Code by Joeri Ridder and some other fine folks.
// Code source for button pressing: https://www.arduino.cc/en/Tutorial/StateChangeDetection
// Code source for timer: https://www.arduino.cc/en/tutorial/BlinkWithoutDelay and https://forum.arduino.cc/index.php?topic=384760.0

/*#define DIPS1 16
#define B5 15
#define B6 2*/
#define BUZZER 23
/*
const int b1 = 14;
const int b2 = 12;
const int b3 = 32;
const int b4 = 35;

const int led_azul = 26;
const int led_amarelo = 27;
const int LED_VERDE = 25;
const int LED_VERMELHO = 33;*/

const int b1 = 14;
const int b2 = 12;
const int b3 = 32;
const int b4 = 35;

const int LED_AZUL = 26;
const int LED_AMARELO = 27;
const int LED_VERDE = 25;
const int LED_VERMELHO = 33;


int b1State = 0;
int b1LastState = 0;
int b2State = 0;
int b2LastState = 0;
int b3State = 0;
int b3LastState = 0;
int b4State = 0;
int b4LastState = 0;

int p1State = 1;                         // Player states: 0=out, 1=in, 2=win;
int p2State = 1;
int p3State = 1;
int p4State = 1;
int p1Points = 0;
int p2Points = 0;
int p3Points = 0;
int p4Points = 0;
const int pointsToWin = 5;              // Points needed to win the game.

bool deadZone = false;
unsigned long dZTimerStart = 0;
const long dZTimerDuration = 5000;     // Duration of the timer in milliseconds

bool gameWin = false;
unsigned long winTimerStart = 0;
const long winTimerDuration = 250;     // Duration of the timer in milliseconds
int winLedState = LOW;                 // State of the led of the winning player

unsigned long resetTimerStart = 0;
const long resetTimerDuration = 10000;   // Duration in milliseconds

//    TAKE ON ME
void luzinha () { //função para piscar as luzes aleatoriamente
  bool ligarLED_AZUL = random(2) == 1;
  bool ligarLED_AMARELO = random(2) == 1;
  bool ligarLED_VERDE = random(2) == 1;
  bool ligarLED_VERMELHO = random(2) == 1;

  if (ligarLED_AZUL) {
    digitalWrite(LED_AZUL, HIGH);
    delay(1);
    digitalWrite(LED_AZUL, LOW);
  } else{
    digitalWrite(LED_AZUL, LOW);
  }
  if (ligarLED_AMARELO) {
    digitalWrite(LED_AMARELO, HIGH);
    delay(1);
    digitalWrite(LED_AMARELO, LOW);
  } else{
    digitalWrite(LED_AMARELO, LOW);
  }
  if (ligarLED_VERDE) {
    digitalWrite(LED_VERDE, HIGH);
    delay(1);
    digitalWrite(LED_VERDE, LOW);
  } else{
    digitalWrite(LED_VERDE, LOW);
  }
  if (ligarLED_VERMELHO) {
    digitalWrite(LED_VERMELHO, HIGH);
    delay(1);
    digitalWrite(LED_VERMELHO, LOW);
  } else{
    digitalWrite(LED_VERMELHO, LOW);
  }
}

void takeOnMe () { //função para tocar música
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

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(BUZZER);
  }
}


void setup() {
  Serial.begin(9600);
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
}

void loop() {
  // Button press testing
  b1LastState = ButtonTest(b1, b1State, b1LastState, p1State, 1);
  b2LastState = ButtonTest(b2, b2State, b2LastState, p2State, 2);
  b3LastState = ButtonTest(b3, b3State, b3LastState, p3State, 3);
  b4LastState = ButtonTest(b4, b4State, b4LastState, p4State, 4);

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

int ButtonTest(int buttonPin, int state, int lastState, int playerState, int buttonNumber) {
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
  takeOnMe();

  winTimerStart = millis();
  resetTimerStart = millis();
  gameWin = true;
  // Set the state of the player to the given states. Winning player gets 2 (win), everone else gets 0 (loose).
  p1State = p1NewState;
  p2State = p2NewState;
  p3State = p3NewState;
  p4State = p4NewState;
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
    // Reset all important variables so the game can be player again.
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
