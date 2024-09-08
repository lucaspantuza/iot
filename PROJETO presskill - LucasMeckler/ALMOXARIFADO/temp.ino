

//  Variáveis menu
int statusD1 = 0;
int statusD2 = 0;


//  Constantes simon
const int tamMemoria = 100;  // Número máximo de combinações ou fases de jogo
const int tempoCor = 1000;   // tempo de cada cor, 1000 millisegundos

// Endereço na EEPROM onde o recorde será armazenado
int enderecoRecorde = 0;
int recorde = 0;

//  Variáveis simon
int statusB1 = 0;  // Status dos botões
int statusB2 = 0;
int statusB3 = 0;
int statusB4 = 0;

int currentTime = 0;  // temporizadores
int lastTime = 0;

int demoLed = 0;  // Indicador de modo demonstração pré-jogo

int statusJogo = 0;       // 0 = modo demonstração ; 1 = modo Jogo
int memJogo[tamMemoria];  // array com sequencia de cores para jogar responder
int etapaJogo;            // 0 = introdução; 1 = jogo; 2 = perdeu; 3 = ganhou
int faseJogo = 1;         // evolução do jogador, vai até o valor de tamMemoria
int respJogador = 0;      // guarda resposta do jogador
int botaoPress = 0;       // variável para guardar botão pressionado pelo jogador
int perdeuJogo = 0;       // indicador para perdeu o jogo
int tempoJogador = 5000;  // Tempo da vez do jogador, para cada cor

//  FUNÇÕES




//  FUNÇÕES SIMON


// Função Modo Jogo, dividida em duas partes, inicialização e Jogo propriamente dito
void modoJogo() {
  switch (etapaJogo) {
    case 0:
      inicioJogo();  // Faz efeito de leds de inicialização
      etapaJogo++;
      break;
    case 1:
      turnoArduino();
      turnoJogador();
      break;
  }
  delay(100);
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
  for (int i = 0; i < tamMemoria; i++) {
    memJogo[i] = random(1, 5);  // randomiza cores: 1 = Verm; 2 = Amar; 3 = Verd; 4 = Azul
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
  lcd.setCursor(0, 1);
  lcd.print("Recorde -> ");
  lcd.print(recorde);

  Serial.print("Turno Arduino, Fase: ");
  Serial.println(faseJogo);  // variável faseJogo é o quanto o Jogador vai avançando, Arduino exibe até onde Jogador está

  for (int i = 0; i < faseJogo; i++) {
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
  lcd.setCursor(0, 1);
  lcd.print("Recorde -> ");
  lcd.print(recorde);

  Serial.print("Turno Jogador, Fase: ");
  Serial.println(faseJogo);

  int terminoTurno = 0;

  // Para cada fase alcançada, jogador tem que repetir sequencia do Arduino
  for (int i = 0; i < faseJogo; i++) {
    botaoPress = leituraBotoesJogo(i);  // Checa botão pressionado pelo jogador
    if (botaoPress == 1) {              // Pressionou corretamente
      Serial.println("Resposta certa");
      terminoTurno = 1;
      delay(100);
    } else {  // Errou
      Serial.println("Resposta errada, Perdeu o jogo!");
      perdeuJogo == 1;
      statusJogo = 0;
      etapaJogo = 0;
      perdeJogo();
      break;
    }
  }
  delay(500);
  faseJogo++;  // Incrementa fase
  if (faseJogo == sizeof(memJogo) / sizeof(memJogo[0])) {
    ganhouJogo();  // ganhou jogo e faz efeito do ganhador
  }
  apagaLeds();
}

// Função para ler botões no modo demonstação, com lógica para sair do modo se pressionou botão
void leituraBotoes() {
  statusB4 = digitalRead(BOTAO_VERMELHO);
  statusB2 = digitalRead(BOTAO_AMARELO);
  statusB2 = digitalRead(BOTAO_VERDE);
  statusB1 = digitalRead(BOTAO_AZUL);
  statusB5 = digitalRead(B5);
  statusB6 = digitalRead(B6);
  if (statusJogo == 0) {
    if (statusB4 || statusB2 || statusB3 || statusB1) {  // algum botão foi pressionado
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
  while (botao == 0 || debounce == 0) {  // fica dentro do while enquanto não pressionar botão e debounce acabar
    statusB4 = digitalRead(BOTAO_VERMELHO);
    statusB2 = digitalRead(BOTAO_AMARELO);
    statusB3 = digitalRead(BOTAO_VERDE);
    statusB1 = digitalRead(BOTAO_AZUL);
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
    if (statusB4 == 0 && statusB2 == 0 && statusB2 == 0 && statusB2 == 0 && botao > 0) {
      debounce = 1;
    }
    delay(100);
    tempoTurno = millis();
    if ((tempoTurno - inicioTurno) > tempoJogador) return 0;  // Tempo de 5 segundos excedido
  }
  // confere se botão pressionado foi o correto e retorna com resultado
  if (botao == memJogo[fase]) {
    return 1;  // Acertou
  } else {
    return 0;  // Errou
  }
}

// Função com efeitos de Perdeu o Jogo
void perdeJogo() {
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
  lcd.setCursor(0, 1);
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
void ganhouJogo() {
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





