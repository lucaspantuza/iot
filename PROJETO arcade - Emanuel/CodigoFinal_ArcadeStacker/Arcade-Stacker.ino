// biblioteca para trabalhar com a matriz
#include "LedControl.h"

// constantes da matriz e do botao
int DIN = 11;
int CS = 7;
int   CLK = 13;
int BUTTON = 4;
LedControl lc=LedControl(DIN, CLK, CS,0);

// variaveis do botao
bool botaoOn = false;
int entradaBotao;

// variaveis para acender os LEDs na ordem
int colunaAtual = 0;
int linhaAtual = 0;
int sentidoLed = 1;
int tempo = 0;
int colunaEscolhida = -1; // linha atual do jogo

// variaveis do jogo (dificuldade)
int tempoReiniciar = 1000;
int aumentoVelocidade = 20;
int velocidadeAtual = 200;
int velocidadeInicial = 200;

// mensagens de inicio/derrota e vitoria
bool comecouJogo = false;
int telaInicial = 0;

bool vencedor = false;
int telaVitoria = 0;

int StackerMatriz[8][46] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,1,1,1,1,1,0,1,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,1,0,0,1,0,1,1,1,0,1,1,1,0,0,0,0,0,0},
  {0,0,1,1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,1,1,0,0},
  {1,0,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,1,1,0,0,0,1,1,1,0,1,0,0,1,0,0,0,0,1},
  {0,0,1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,0,1,0,1,0,0,1,0,0,0,1,1,1,0,0,1,1,0,0},
  {0,0,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,1,0,1,0,0,1,0,1,1,1,0,1,0,0,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

int VencedorMatriz[8][43] = {
  {1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
  {0,1,0,1,0,0,1,0,1,0,1,0,1,1,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1,0,1,1,1,0,0,0,1,0,1,0},
  {1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,0,1,1,0,0,1,0,1,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,1},
  {0,1,0,1,0,0,1,0,1,0,1,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,0,1,0,0,1,0,0,1,0,1,0},
  {1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,0,1,0,0,1,1,0,1,0,0,1,1,0,1,0,0,0,0,1,1,1,0,0,1,0,1,0,1},
  {0,1,0,1,0,0,0,1,0,1,0,0,1,1,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1,0,1,0,0,1,0,0,1,0,1,0},
  {1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
  {0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0},
};

void setup()   {
  Serial.begin(9600);
  lc.shutdown(0,false);
  lc.setIntensity(0,0);
  lc.clearDisplay(0);
  pinMode(BUTTON, INPUT);

  // valor incial do botao antes do jogo iniciar
  InicioBotao();
}

void   loop() {
  if(vencedor){
    if(LeituraBotao()){
      ReinicioJogo();
    }
    VitoriaUsuario();
  }
  else if(comecouJogo == false){
    LoopInicial();
    if(LeituraBotao()){
      lc.clearDisplay(0);
      comecouJogo = true;
    }
  }
  else{
    LoopDuranteJogo();
  }
  delay(1);
}

void LoopDuranteJogo(){
  // tempo para acender o proximo LED
  tempo++;
  if(tempo >= velocidadeAtual){
    ProximoLed();
  }
  
  if(LeituraBotao()){
    delay(200);
    ProximaLinha();
  }

  if(linhaAtual == 8){
    delay(tempoReiniciar);
    vencedor = true;
  }
}

void ProximoLed(){
  tempo = 0;
  lc.setLed(0, colunaAtual, linhaAtual, false);
  colunaAtual += sentidoLed;
  if(colunaAtual == 7 || colunaAtual == 0){
    sentidoLed = sentidoLed * -1;
  }
  lc.setLed(0, colunaAtual, linhaAtual, true);
}

void ProximaLinha(){
  linhaAtual++;
  velocidadeAtual -= aumentoVelocidade;
  if(colunaEscolhida == -1){
    colunaEscolhida = colunaAtual;
  }
  else{
    if(colunaEscolhida != colunaAtual){
      ReinicioJogo();
    }
  }
}

bool LeituraBotao(){
  // leitura da entrada do botao pra definir HIGH
  entradaBotao = digitalRead(BUTTON);
  if(entradaBotao == HIGH){
    if(botaoOn == false){
      botaoOn = true;
      return true;
    }
    else{
      return false;
    }
  }
  else{
    if(botaoOn == true){
      botaoOn = false;
      return false;
    }
    else{
      return false;
    }
  }
}

void ReinicioJogo(){
    delay(tempoReiniciar);
    lc.clearDisplay(0);
    linhaAtual = 0;
    velocidadeAtual = velocidadeInicial;
    InicioBotao();
    colunaEscolhida = -1;
    comecouJogo = false;
    telaInicial = 0;
    vencedor = false;
    telaVitoria = 0;
}

void InicioBotao(){
  entradaBotao = digitalRead(BUTTON);
  if(entradaBotao == HIGH){
    botaoOn = true;
  }else{
    botaoOn = false;
  }
}

void LoopInicial(){
  for(int j=0; j<8; j++){
    for(int i=0; i<8; i++){
      lc.setLed(0, i, 7-j, StackerMatriz[j][(i+telaInicial)-abs((i+telaInicial)/46)*46]);
    }
  }
  telaInicial++;
}

void VitoriaUsuario(){
  for(int j=0; j<8; j++){
    for(int i=0; i<8; i++){
      lc.setLed(0, i, 7-j, VencedorMatriz[j][i + telaVitoria]);
    }
  }
  telaVitoria++;
  if(telaVitoria >= 36){
    ReinicioJogo();
  }
}