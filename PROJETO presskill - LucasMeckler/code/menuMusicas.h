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
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
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
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

// Funções de Sons
void somVM()
{
    tone(BUZZER_PIN, 663);
    delay(100);
    noTone(BUZZER_PIN);
}

void somAM()
{
    ;
    tone(BUZZER_PIN, 440);
    delay(100);
    noTone(BUZZER_PIN);
}

void somVD()
{
    tone(BUZZER_PIN, 468);
    delay(100);
    noTone(BUZZER_PIN);
}

void somAZ()
{
    tone(BUZZER_PIN, 392);
    delay(100);
    noTone(BUZZER_PIN);
}

void somPerdeu()
{
    tone(BUZZER_PIN, 200);
    for (int i = 1; i <= 3; i++)
    { // quando errar a ordem
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
    noTone(BUZZER_PIN);
}

void tocaMusicaEscolhida(int *melody, int sizeOfMelody, int tempo, bool luzesAleatorias)
{
    // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
    // there are two values per note (pitch and duration), so for each note there are four bytes
    int notes = sizeOfMelody / sizeof(melody[0]) / 2;

    // this calculates the duration of a whole note in ms
    int wholenote = (60000 * 4) / tempo;

    int divider = 0, noteDuration = 0;

    // iterate over the notes of the melody.
    // Remember, the array is twice the number of notes (notes + durations)
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2)
    {

       if (digitalRead(BOTAO_SELECAO_ESQ) != LOW)
           return; // mudou na chave selecao

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0)
        {
            // regular note, just proceed
            noteDuration = (wholenote) / divider;
        }
        else if (divider < 0)
        {
            // dotted notes are represented with negative durations!!
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // we only play the note for 90% of the duration, leaving 10% as a pause
        tone(BUZZER_PIN, melody[thisNote], noteDuration * 0.9);

        // faz os LEDs piscarem aleatoriamente durante a música
        if (luzesAleatorias)
            acenderLuzesAleatorias();

        // Wait for the specief duration before playing the next note.
        delay(noteDuration);
        // encerraJogo();

        // stop the waveform generation before the next note.
        noTone(BUZZER_PIN);
    }
}

void tocaMusicaFurElise()
{
    int tempo = 80;
    int melody[] = {
        NOTE_DS5,
        16,
        NOTE_E5,
        16,
        NOTE_DS5,
        16,
        NOTE_E5,
        16,
        NOTE_DS5,
        16,
        NOTE_E5,
        16,
        NOTE_B4,
        16,
        NOTE_D5,
        16,
        NOTE_C5,
        16,
        NOTE_A4,
        8,
        REST,
        16,
        NOTE_C4,
        16,
        NOTE_E4,
        16,
        NOTE_A4,
        16,

        NOTE_B4,
        8,
        REST,
        16,
        NOTE_E4,
        16,
        NOTE_GS4,
        16,
        NOTE_B4,
        16,
        NOTE_C5,
        8,
        REST,
        16,
        NOTE_E4,
        16,
        NOTE_E5,
        16,
        NOTE_DS5,
        16,
        NOTE_E5,
        16,
        NOTE_DS5,
        16,
        NOTE_E5,
        16,
        NOTE_B4,
        16,
        NOTE_D5,
        16,
        NOTE_C5,
        16,
        NOTE_A4,
        8,
        REST,
        16,
        NOTE_C4,
        16,
        NOTE_E4,
        16,
        NOTE_A4,
        16,
        NOTE_B4,
        8,
        REST,
        16,
        NOTE_E4,
        16,
        NOTE_C5,
        16,
        NOTE_B4,
        16,
        NOTE_A4,
        8,
    };
    tocaMusicaEscolhida(melody, sizeof(melody), tempo, true);
}

void tocaMusicaTakeOnMe(bool luzesAleatorias)
{
    int tempo = 140;
    int melody[] = {

        // Take on me, by A-ha
        // Score available at https://musescore.com/user/27103612/scores/4834399
        // Arranged by Edward Truong

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
    tocaMusicaEscolhida(melody, sizeof(melody), tempo, luzesAleatorias);
}

void tocaMusicaTakeOnMeDemo()
{
    int tempo = 140;
    int melody[] = {

        // Take on me, by A-ha
        // Score available at https://musescore.com/user/27103612/scores/4834399
        // Arranged by Edward Truong

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
    tocaMusicaEscolhida(melody, sizeof(melody), tempo, true);
}

void tocaMusicaSilentNight()
{
    int tempo = 140;
    int melody[] = {

        // Silent Night, Original Version
        // Score available at https://musescore.com/marcsabatella/scores/3123436

        NOTE_G4,
        -4,
        NOTE_A4,
        8,
        NOTE_G4,
        4,
        NOTE_E4,
        -2,
        NOTE_G4,
        -4,
        NOTE_A4,
        8,
        NOTE_G4,
        4,
        NOTE_E4,
        -2,
        NOTE_D5,
        2,
        NOTE_D5,
        4,
        NOTE_B4,
        -2,
        NOTE_C5,
        2,
        NOTE_C5,
        4,
        NOTE_G4,
        -2,

        NOTE_A4,
        2,
        NOTE_A4,
        4,
        NOTE_C5,
        -4,
        NOTE_B4,
        8,
        NOTE_A4,
        4,
        NOTE_G4,
        -4,
        NOTE_A4,
        8,
        NOTE_G4,
        4,
        NOTE_E4,
        -2,
        NOTE_A4,
        2,
        NOTE_A4,
        4,
        NOTE_C5,
        -4,
        NOTE_B4,
        8,
        NOTE_A4,
        4,
        NOTE_G4,
        -4,
        NOTE_A4,
        8,
        NOTE_G4,
        4,
        NOTE_E4,
        -2,

        NOTE_D5,
        2,
        NOTE_D5,
        4,
        NOTE_F5,
        -4,
        NOTE_D5,
        8,
        NOTE_B4,
        4,
        NOTE_C5,
        -2,
        NOTE_E5,
        -2,
        NOTE_C5,
        4,
        NOTE_G4,
        4,
        NOTE_E4,
        4,
        NOTE_G4,
        -4,
        NOTE_F4,
        8,
        NOTE_D4,
        4,
        NOTE_C4,
        -2,
        NOTE_C4,
        -1,

    };
    tocaMusicaEscolhida(melody, sizeof(melody), tempo, true);
}

void tocaMusicaTetris()
{
    int tempo = 144;
    int melody[] = {

        // Based on the arrangement at https://www.flutetunes.com/tunes.php?id=192

        NOTE_E5,
        4,
        NOTE_B4,
        8,
        NOTE_C5,
        8,
        NOTE_D5,
        4,
        NOTE_C5,
        8,
        NOTE_B4,
        8,
        NOTE_A4,
        4,
        NOTE_A4,
        8,
        NOTE_C5,
        8,
        NOTE_E5,
        4,
        NOTE_D5,
        8,
        NOTE_C5,
        8,
        NOTE_B4,
        -4,
        NOTE_C5,
        8,
        NOTE_D5,
        4,
        NOTE_E5,
        4,
        NOTE_C5,
        4,
        NOTE_A4,
        4,
        NOTE_A4,
        8,
        NOTE_A4,
        4,
        NOTE_B4,
        8,
        NOTE_C5,
        8,

        NOTE_D5,
        -4,
        NOTE_F5,
        8,
        NOTE_A5,
        4,
        NOTE_G5,
        8,
        NOTE_F5,
        8,
        NOTE_E5,
        -4,
        NOTE_C5,
        8,
        NOTE_E5,
        4,
        NOTE_D5,
        8,
        NOTE_C5,
        8,
        NOTE_B4,
        4,
        NOTE_B4,
        8,
        NOTE_C5,
        8,
        NOTE_D5,
        4,
        NOTE_E5,
        4,
        NOTE_C5,
        4,
        NOTE_A4,
        4,
        NOTE_A4,
        4,
        REST,
        4,

        NOTE_E5,
        4,
        NOTE_B4,
        8,
        NOTE_C5,
        8,
        NOTE_D5,
        4,
        NOTE_C5,
        8,
        NOTE_B4,
        8,
        NOTE_A4,
        4,
        NOTE_A4,
        8,
        NOTE_C5,
        8,
        NOTE_E5,
        4,
        NOTE_D5,
        8,
        NOTE_C5,
        8,
        NOTE_B4,
        -4,
        NOTE_C5,
        8,
        NOTE_D5,
        4,
        NOTE_E5,
        4,
        NOTE_C5,
        4,
        NOTE_A4,
        4,
        NOTE_A4,
        8,
        NOTE_A4,
        4,
        NOTE_B4,
        8,
        NOTE_C5,
        8,

        NOTE_D5,
        -4,
        NOTE_F5,
        8,
        NOTE_A5,
        4,
        NOTE_G5,
        8,
        NOTE_F5,
        8,
        NOTE_E5,
        -4,
        NOTE_C5,
        8,
        NOTE_E5,
        4,
        NOTE_D5,
        8,
        NOTE_C5,
        8,
        NOTE_B4,
        4,
        NOTE_B4,
        8,
        NOTE_C5,
        8,
        NOTE_D5,
        4,
        NOTE_E5,
        4,
        NOTE_C5,
        4,
        NOTE_A4,
        4,
        NOTE_A4,
        4,
        REST,
        4,

        NOTE_E5,
        2,
        NOTE_C5,
        2,
        NOTE_D5,
        2,
        NOTE_B4,
        2,
        NOTE_C5,
        2,
        NOTE_A4,
        2,
        NOTE_GS4,
        2,
        NOTE_B4,
        4,
        REST,
        8,
        NOTE_E5,
        2,
        NOTE_C5,
        2,
        NOTE_D5,
        2,
        NOTE_B4,
        2,
        NOTE_C5,
        4,
        NOTE_E5,
        4,
        NOTE_A5,
        2,
        NOTE_GS5,
        2,

    };
    tocaMusicaEscolhida(melody, sizeof(melody), tempo, true);
}

void telaMenuMusicas()
{
    telaMenuLinha(" Selecione cor");
}

void menuMusicas()
{
    telaMenuMusicas();

    while (digitalRead(BOTAO_SELECAO_ESQ) == LOW)
    {

        if (digitalRead(BOTAO_AZUL) == HIGH)
        {
            // telaDuasLinhas("Fur Elise", "Beethoven");
            telaMenuLinha("  ", 6, " Fur Elise");
            tocaMusicaFurElise();
            telaMenuMusicas();
        }
        else if (digitalRead(BOTAO_AMARELO) == HIGH)
        {
            // telaDuasLinhas("Silent Night", "Frank Sinatra ");
            telaMenuLinha(" ", 6, " Silent Night");
            tocaMusicaSilentNight();
            telaMenuMusicas();
        }
        else if (digitalRead(BOTAO_VERDE) == HIGH)
        {
            // telaDuasLinhas("Take on me", "A-HA ");
            telaMenuLinha("  ", 6, " Take on me");
            tocaMusicaTakeOnMe(true);
            telaMenuMusicas();
        }
        else if (digitalRead(BOTAO_VERMELHO) == HIGH)
        {
            // telaDuasLinhas("Tetris theme", "Tetris ");
            telaMenuLinha(" ", 6, " Tetris theme");
            tocaMusicaTetris();
            telaMenuMusicas();
        }

        delay(100);
    }
}