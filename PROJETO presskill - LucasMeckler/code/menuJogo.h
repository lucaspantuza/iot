#define MAX_FASES 16

void firulaRoletaCores()
{

  for (int roleta = 1;;)
  {

    // qualquer botao ou troque selecao sai da funcao
    if ((digitalRead(BOTAO_SELECAO_DIR) != LOW) || (digitalRead(BOTAO_AZUL) == HIGH) || (digitalRead(BOTAO_AMARELO) == HIGH) || (digitalRead(BOTAO_VERDE) == HIGH) || (digitalRead(BOTAO_VERMELHO) == HIGH) || (digitalRead(BOTAO_AMARELO) == HIGH))
    {
      while (digitalRead(BOTAO_AZUL) == HIGH)
        delay(50);
      while (digitalRead(BOTAO_VERDE) == HIGH)
        delay(50);
      while (digitalRead(BOTAO_VERMELHO) == HIGH)
        delay(50);
      while (digitalRead(BOTAO_AMARELO) == HIGH)
        delay(50);
      apagaLeds();
      return;
    }

    if (roleta % 9)
    { // ele faz leitura de botao X vezes para uma mudanca de led, devido delay
      switch (roleta)
      {
      case 1:
        digitalWrite(LED_AZUL, HIGH);
        break;
      case 2:
        digitalWrite(LED_VERDE, HIGH);
        break;
      case 3:
        digitalWrite(LED_VERMELHO, HIGH);
        break;
      case 4:
        digitalWrite(LED_AMARELO, HIGH);
        break;
      case 5:
        digitalWrite(LED_AZUL, LOW);
        break;
      case 6:
        digitalWrite(LED_VERDE, LOW);
        break;
      case 7:
        digitalWrite(LED_VERMELHO, LOW);
        break;
      case 8:
        digitalWrite(LED_AMARELO, LOW);
        break;
      }
    }

    roleta = (roleta + 1) % 9; // volta ao inicio
    delay(50);
  }

  apagaLeds();
}

void firulaParaComecarJogo()
{
  for (int i = 0; i < 10; i++)
  {

    // Criterio de saida do jogo via chave seletora de funcao
    if (digitalRead(BOTAO_SELECAO_DIR) != LOW)
      return;

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

// A linha de cima é customizavel, a de baixo sao bolinhas até o limite de fases, sendo o valor parametrizado em preto
void telaIntrucaoPlacar(char *linhaSuperior, int placar)
{
  lcd.clear();
  lcd.home();
  lcd.print(linhaSuperior);

  lcd.setCursor(0, 1);
  for (int i = 1; i <= MAX_FASES; i++)
  {
    if ((i < placar))
    {
      lcd.write(byte(7));
    }
    else
    {
      lcd.print("o");
    }
  }
}

void tocaCorretoAteFase(int fase, int *coresSorteadas, int tempo_nota, int tempo_entrenota)
{
  apagaLeds();

  for (int nota = 0; nota < fase; nota++)
  {
    if (coresSorteadas[nota] == 1)
    {
      tone(BUZZER_PIN, 392);
      digitalWrite(LED_AZUL, HIGH);
    }
    else if (coresSorteadas[nota] == 2)
    {
      tone(BUZZER_PIN, 440);
      digitalWrite(LED_VERDE, HIGH);
    }
    else if (coresSorteadas[nota] == 3)
    {
      tone(BUZZER_PIN, 468);
      digitalWrite(LED_VERMELHO, HIGH);
    }
    else if (coresSorteadas[nota] == 4)
    {
      tone(BUZZER_PIN, 663);
      digitalWrite(LED_AMARELO, HIGH);
    }

    delay(tempo_nota); // espera na nota

    // Para a nota e a luz do botao respectivo
    apagaLeds();
    noTone(BUZZER_PIN);

    delay(tempo_entrenota); // entre notas

    // Criterio de saida do jogo via chave seletora de funcao
    if (digitalRead(BOTAO_SELECAO_DIR) != LOW)
      return;
  }
}

// aguarda usuario apertar um botao
int leAteCodigoBotao()
{
  for (;;)
  {
    // Criterio de saida do jogo via chave seletora de funcao
    if (digitalRead(BOTAO_SELECAO_DIR) != LOW)
      return 0;

    if (digitalRead(BOTAO_AZUL) == HIGH)
    {
      digitalWrite(LED_AZUL, HIGH);
      tone(BUZZER_PIN, 392);
      while (digitalRead(BOTAO_AZUL) == HIGH)
        delay(10);
      digitalWrite(LED_AZUL, LOW);
      noTone(BUZZER_PIN);
      return 1;
    }

    if (digitalRead(BOTAO_VERDE) == HIGH)
    {
      digitalWrite(LED_VERDE, HIGH);
      tone(BUZZER_PIN, 440);
      while (digitalRead(BOTAO_VERDE) == HIGH)
        delay(10);
      digitalWrite(LED_VERDE, LOW);
      noTone(BUZZER_PIN);
      return 2;
    }

    if (digitalRead(BOTAO_VERMELHO) == HIGH)
    {
      digitalWrite(LED_VERMELHO, HIGH);
      tone(BUZZER_PIN, 468);
      while (digitalRead(BOTAO_VERMELHO) == HIGH)
        delay(10);
      digitalWrite(LED_VERMELHO, LOW);
      noTone(BUZZER_PIN);
      return 3;
    }
    if (digitalRead(BOTAO_AMARELO) == HIGH)
    {
      digitalWrite(LED_AMARELO, HIGH);
      tone(BUZZER_PIN, 663);
      while (digitalRead(BOTAO_AMARELO) == HIGH)
        delay(10);
      digitalWrite(LED_AMARELO, LOW);
      noTone(BUZZER_PIN);
      return 4;
    }

    delay(50);
  }
}

// quando errar a ordem
void perdeuFase()
{
  tone(BUZZER_PIN, 200);
  for (int i = 1; i <= 3; i++)
  {
    acendeLeds();
    delay(200);
    apagaLeds();
    delay(200);
  }
  noTone(BUZZER_PIN);

  telaDuasLinhas("  Voce perdeu!", "Jogue de novo...");
  firulaRoletaCores();
}

void ganhouFase()
{
  for (int i = 0; i < 3; i++)
  {
    tone(BUZZER_PIN, 500 + (i * 100));
    delay(100);
    noTone(BUZZER_PIN);
    delay(100);
  }
}

void ganhouTudo()
{
  ganhouFase();
  ganhouFase();
  ganhouFase();
  tocaMusicaTakeOnMe(true);

  telaDuasLinhas("   PARABENS!", "Jogue de novo...");
  firulaRoletaCores();
}

void menuJogo()
{

  // Firula para comecar o jogo
  // - fica piscando as luzes ate o usuario pressionar alguma tecla
  telaMenuLinha("Pressione botao");
  firulaRoletaCores();

  // No inicio do jogo, o computador sorteia ja as cores que serao usadas
  int coresSorteadas[MAX_FASES];
  for (int i = 0; i < MAX_FASES; i++)
    coresSorteadas[i] = random(1, 5); // randomiza cores: 1 = AZUL; 2 = VERDE; 3 = VERMELHO; 4 = AMARELO

  telaDuasLinhas(" Prepare-se...", "");
  firulaParaComecarJogo();
  delay(1000);

  // o usuario comeca da fase 1 e vai ate a fase MAX_FASES
  for (int fase = 1; fase <= MAX_FASES; fase++) // pula as fases do jogo
  {

    // Criterio de saida do jogo via chave seletora de funcao
    if (digitalRead(BOTAO_SELECAO_DIR) != LOW)
      return;

    telaIntrucaoPlacar("Veja e escute...", fase);
    delay(2000);
    tocaCorretoAteFase(fase, coresSorteadas, 500, 200);
    delay(500);

    telaIntrucaoPlacar("Sua vez...", fase);
    bool perdeu = false;
    for (int i = 0; i < fase; i++) // faz as notas ate o limite da fase atual
    {
      if (coresSorteadas[i] != leAteCodigoBotao())
      {
        // usuario errou
        perdeu = true;
        break; // for INTERNO
      }
    }

    delay(1000);

    if (perdeu)
    {
      perdeuFase();
      break; // for EXTERNO - volta para o inicio do jogo
    }

    if (fase == MAX_FASES)
    {
      ganhouTudo();
      break; // for EXTERNO - volta para o inicio do jogo
    }

    ganhouFase();
    delay(2000);
  }
}
