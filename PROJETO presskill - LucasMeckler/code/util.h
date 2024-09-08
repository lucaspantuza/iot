void beep(int qtd)
{
    for (int i = 0; i < qtd; i++)
    {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(100);
        digitalWrite(BUZZER_PIN, LOW);
        delay(100);
    }
}

void beep()
{
    beep(1);
}

// Função para apagar todos os Leds
void apagaLeds()
{
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AZUL, LOW);
}

// Função para acender todos os Leds
void acendeLeds()
{
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_AZUL, HIGH);
}

void acenderLuzesAleatorias()
{ // função para piscar as luzes aleatoriamente
    bool ligarLED_AZUL = random(2) == 1;
    bool ligarLED_AMARELO = random(2) == 1;
    bool ligarLED_VERDE = random(2) == 1;
    bool ligarLED_VERMELHO = random(2) == 1;

    apagaLeds();

    if (ligarLED_AZUL)
    {
        digitalWrite(LED_AZUL, HIGH);
    }
    if (ligarLED_AMARELO)
    {
        digitalWrite(LED_AMARELO, HIGH);
    }
    if (ligarLED_VERDE)
    {
        digitalWrite(LED_VERDE, HIGH);
    }
    if (ligarLED_VERMELHO)
    {
        digitalWrite(LED_VERMELHO, HIGH);
    }
}

void telaBoasVindas()
{
    lcd.init();
    lcd.backlight();
    lcd.setCursor(5, 0); // COLUNA, LINHA
    lcd.print("CEFET");
    lcd.setCursor(2, 1);
    lcd.print("Extensao OAs");
}

void telaMenuLinhaTopo()
{
    lcd.clear();
    lcd.home();

    lcd.write((digitalRead(BOTAO_SELECAO_ESQ) == LOW) ? byte(3) : byte(0));
    lcd.print("Music ");

    lcd.write((digitalRead(BOTAO_SELECAO_ESQ) == HIGH && digitalRead(BOTAO_SELECAO_DIR) == HIGH) ? byte(4) : byte(1));
    lcd.print("DJ ");

    lcd.write((digitalRead(BOTAO_SELECAO_DIR) == LOW) ? byte(5) : byte(2));
    lcd.print("Game");
}

void telaMenuLinha(char *linha)
{
    telaMenuLinhaTopo();

    lcd.setCursor(0, 1);
    lcd.print(linha);
}

void telaMenuLinha(char *linha_inicio, int icon, char *linha_fim)
{
    telaMenuLinhaTopo();

    lcd.setCursor(0, 1);
    lcd.print(linha_inicio);
    lcd.write(byte(6));
    lcd.print(linha_fim);
}

void telaDuasLinhas(char *linha1, char *linha2)
{
    lcd.clear();
    lcd.home();
    lcd.print(linha1);
    lcd.setCursor(0, 1);
    lcd.print(linha2);
}

// void telaMenuInicial()
// {
//     telaDuasLinhas("oo* SIMON o*o DJ", "   *oo SONGS    ");

//     lcd.clear();
//     lcd.home();
//     // lcd.write(0);
//     // lcd.print(linha1);
//     // lcd.setCursor(0, 1);
//     // lcd.print(linha2);

//     lcd.write(byte(0));
// }

// char chaine[] = "Salut";
// lcd.printf("%s", chaine);