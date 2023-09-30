#include <Keypad.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h> 

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include <bits/stdc++.h>

//A tela possui 16 caracteres
//1234567890123456
//=? tecle =

//D8     NAO DA como entrada, mas DA como saida
//Tx==1  NAO DA como entrada, mas DA como saida
//Rx==3
//sk==10
//S3==9

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte n_rows = 4;
const byte n_cols = 4;
char keys[n_rows][n_cols] = {{'1','2','3','+'},{'4','5','6','-'},{'7','8','9','*'},{'c','0','=','/'}};
byte colPins[n_rows] = {D6, D5, D4, D3};
byte rowPins[n_cols] = {10, 9, 3, D7};
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, n_rows, n_cols); 

int BUZZ_PIN = D8; 

bool calculando = false;

// recebe quantidade de milisegundos do bip que o buzz irá fazer
void buzzBip(int milis){
  digitalWrite(BUZZ_PIN,HIGH);
  delay(milis);
  digitalWrite(BUZZ_PIN,LOW);
}

void setup(){
  Serial.begin(9600);
  pinMode(BUZZ_PIN,OUTPUT);
  lcd.init();   // INICIALIZA O DISPLAY LCD
  lcd.clear();
  lcd.backlight(); // HABILITA O BACKLIGHT (LUZ DE FUNDO) 
  lcd.setCursor(0, 0); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print("# PETIT  CEFET #"); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
  //lcd.print("# CEFET  PETIT #"); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
  lcd.setCursor(0, 1); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print(" VENHA CALCULAR "); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
}

void reinicia(){
  calculando = false;
  lcd.clear();
  lcd.setCursor(0, 0); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print("# PETIT  CEFET #"); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
  //lcd.print("# CEFET  PETIT #"); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
  lcd.setCursor(0, 1); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print(" VENHA CALCULAR "); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD]
  /*
  lcd.clear();
  lcd.setCursor(0, 0); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print(" VENHA CALCULAR "); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
  //lcd.print("# CEFET  PETIT #"); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
  lcd.setCursor(0, 1); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print("               0"); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
  */
}

void limpa(){
  lcd.setCursor(0, 0); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print("# PETIT  CEFET #"); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
  //lcd.print("# CEFET  PETIT #"); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
  lcd.setCursor(0, 1); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print(" VENHA CALCULAR "); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD]
  //#lcd.setCursor(0, 0);
  //lcd.print("                "); //limpa
  //escreveSegundaLinha(0);
}

void escreveSegundaLinha(float r){
  Serial.print(r);
  Serial.print("\n");
  lcd.setCursor(0, 1);
  lcd.print("                "); //limpa
  int num = r;
  if(r == 0){
    num = 1;
  }
  int n = int(log10(num) + 1);
  int rInt = int(r);
  if(r - rInt != 0){
    n += 3;
  }
  lcd.print(n);
  lcd.setCursor(16-n, 1); //volta o cursor
  lcd.print(r);
}

void escrevePrimeiraLinha(char vet[], int cont, int tam){
  lcd.setCursor(0, 0);
  lcd.print("                "); //limpa
  lcd.setCursor(0, 0); //volta o cursor
  int i = 0;
  if(cont > 16){
    i = cont - 16;
  }
  for(; i < tam && i < cont; i++){
    lcd.print(vet[i]);
  }
}

void vetorizaManual(char vet[], float nums[], int tam, int nOps){
  int pos = nOps*2;
  int quant = nOps*2 + 1;
  int i = 0;
  for(; i < nOps*2 + 1; i++){
    nums[i] = 0;
  }
  i = tam - 1;
  for(; pos >= 0; pos -= 2){
    int mult = 1;
    Serial.println("NUMVET: ");
    Serial.println(nums[pos]);
    for(; i >= 0 && vet[i] >= '0' && vet[i] <= '9'; i--){
      switch(vet[i])
      {
          case '1':
              nums[pos] += 1*mult;
              break;
          case '2':
              nums[pos] += 2*mult;
              break;
          case '3':
              nums[pos] += 3*mult;
              break;
          case '4':
              nums[pos] += 4*mult;
              break;
          case '5':
              nums[pos] += 5*mult;
              break;
          case '6':
              nums[pos] += 6*mult;
              break;
          case '7':
              nums[pos] += 7*mult;
              break;
          case '8':
              nums[pos] += 8*mult;
              break;
          case '9':
              nums[pos] += 9*mult;
      }
      Serial.println("NUMVET: ");
      Serial.println(nums[pos]);
      mult *= 10;
    }
    if(pos > 0){
      switch(vet[i])
      {
          case '-':
              nums[pos - 1] = -1;
              break;
          case '+':
              nums[pos - 1] = -2;
              break;
          case '*':
              nums[pos - 1] = -3;
              break;
          case '/':
              nums[pos - 1] = -4;
      }
    }
    i--;
  }
}

void criaVetOp(float vetNum[], float vetOp[], int tam){
  float pilha[5];
  int contP = 0, contOp = 0;
  int i = 0;
  for(; i < tam; i++){
    vetOp[i] = 0;
  }
  i = 0;
  for(; i < 5; i++){
    pilha[i] = 0;
  }
  i = 0;
  do{
    if(vetNum[i] >= 0){ //eh numero
      vetOp[contOp] = vetNum[i];
      contOp++;
      if(contP > 0 && pilha[contP - 1] < -2){ // o ultimo da pilha eh * ou /
        contP--;
        vetOp[contOp] = pilha[contP];
        pilha[contP] = 0;
        contOp++;
      }
    }else{//eh operador
      if(vetNum[i] > -3){ // eh + ou -
        if(contP > 0 && pilha[contP - 1] > -3){ //o ultimo da pilha eh + ou -
          contP--;
          vetOp[contOp] = pilha[contP]; //Desempilha o ultimo
          contOp++;
          pilha[contP] = 0;
        }
      }
      pilha[contP] = vetNum[i];
      contP++;
    }
    i++;
  }while(i < tam);
  contP--;
  if (contOp < tam) {
    vetOp[contOp] = pilha[contP]; //Desempilha o ultimo
  }
  contOp++;
}

float calcula(float vetOp[], int tam){
  int n = tam;
  int i = 0;
  int posops[((tam - 1)/2)];
  int j = 0;
  for (int j = 0; i < (tam - 1)/2 && j < tam; j++) {
    if (vetOp[j] < 0) {
      posops[i] = j;
      i++;
    }
  }
  int dif = 0;
  while(n > 1){
    i = 0;
    while(posops[i] < 0){
      i++;
    }
    i = posops[i] + dif;
    switch((int)vetOp[i])
    {
      case -1:
          vetOp[i - 2] = vetOp[i - 2] - vetOp[i - 1];
          break;
      case -2:
          vetOp[i - 2] = vetOp[i - 2] + vetOp[i - 1];
          break;
      case -3:
          vetOp[i - 2] = vetOp[i - 2] * vetOp[i - 1];
          break;
      case -4:
          vetOp[i - 2] = vetOp[i - 2] / vetOp[i - 1];
    }
    for(int c = i - 1; c < n - -1; c++ ){
      vetOp[c] = vetOp[c + 2];
    }
    n -= 2;
    dif -= 2;
    posops[-1 - (dif)/2] = -1;
  }
  return vetOp[0];
}

void imprime(char vet[], int tam){  
  int i = 0;
  for(; i < tam; i++){
    if(vet[i] > '9' || vet[i] < '0'){
      Serial.print(" ");
      Serial.print(vet[i]);
      Serial.print(" ");
    }else{
      Serial.print(vet[i]);
    }
  }
  Serial.println("\n");
}

void imprimef(float vet[], int tam){  
  int i = 0;
  for(; i < tam; i++){
    if(vet[i] > '9' || vet[i] < '0'){
      Serial.print(" ");
      Serial.print(vet[i]);
      Serial.print(" ");
    }else{
      Serial.print(vet[i]);
    }
  }
  Serial.println("\n");
}

float realizaCalculo(char vet[], float nums[], float vetOp[]){
  int tam = 0;
  int i = 0;
  int nOps = 0;
  for(; vet[i] != '\0'; i++){
    tam++;
    if(vet[i] < '0' || vet[i] > '9'){ //nao e numero
      nOps++;
    }
  
  }
  Serial.print("nops: ");
  Serial.println(nOps);
  Serial.println("------------");

  Serial.println("nums antes vetoriza: ");
  imprimef(nums, nOps*2 + 1);
  Serial.println("------------");

  vetorizaManual(vet, nums, tam, nOps);

  Serial.println("nums depois vetoriza: ");
  imprimef(nums, nOps*2 + 1);
  Serial.println("------------");

  criaVetOp(nums, vetOp, nOps*2 + 1);

  Serial.println("------------");

  Serial.println("vetOp: ");
  imprimef(vetOp, nOps*2 + 1);
  Serial.println("------------");

  float r = calcula(vetOp, nOps*2 + 1);
  Serial.print("RESULTADO: ");
  Serial.println(r);
  return r;
}

//===================================================================================================================================================

int tam = 100;
char vet[100];
float nums[100];
float vetOp[100];
int cont = 0;
bool clear = false;
float result = 0;
char myKey = NULL;

//===================================================================================================================================================
//===================================================================================================================================================
//===================================================================================================================================================
//===================================================================================================================================================
//===================================================================================================================================================
//=========================================================================================================== LOOP
//===================================================================================================================================================

/*
  float a = 0.2, b = 0.3, c = 0.4;
  printf("%e\n", (a + b + c) - (c + b + a));
  
  char v[] = {'1','3','0','5'};
  int num = strtol(v, NULL, 10);
  //sscanf(v, "%d", &num);
  printf("num: %d\n",num+10);*/
  //vet[] = {'2', ' ', '1', '2', ' ', '*', ' ', '5', ' ', '5', ' ', '/', ' ', '+', ' ', '3', ' ', '-', ' ', '\0'}
  //nums[] = {13, 14, 34, 15, 23, 47}
  //oper[] = { *,  +,  /,  -,  + }
  //             13        *    14        +    34        /    15        -    23        +    47         = 
  //char vet[] = {'1', '3', '*', '1', '4', '+', '3', '4', '/', '1', '5', '-', '2', '3', '+', '4', '7','\0'};
  //2 * 12 + 5 / 5 - 3
  //char vet[] = {'2', '*', '1', '2', '+', '5', '/', '5', '-',  '3', '\0'};
  //char vet[] = {'6', '*', '3', '\0'};
  //char vet[] = {'8', '*', '0', '6', '\0'};
  //char vet[] = {'9', '*', '0', '3', '\0'};
  //char vet[] = {'2', '5', '/', '2', '\0'};
  

void loop(){
  myKey = myKeypad.getKey();
  if (myKey != NULL){//================================== APERTOU TECLA
    //Serial.print("Key pressed: ");
    //Serial.println(myKey);
    //mykey = "teste "+mykey;
    if(!calculando && (myKey >= '0' && myKey <= '9')){ // !calculando E myKey é numero
      calculando = true;
      cont = 0;
    }
    //{1','2','3','+'},{'4','5','6','-'},{'7','8','9','*'},{'c','0','=','/'}
    if(calculando){//=========================================== CALCULANDO
      if(myKey == '='){//==================================================== CALCULAR (IGUAL APERTADO =)
        vet[cont] = '\0';
        result = realizaCalculo(vet, nums, vetOp);
        //buzzBip(500);
        digitalWrite(BUZZ_PIN,HIGH);
        calculando = false;
        delay(400);
        digitalWrite(BUZZ_PIN,LOW);
        //cont = 0;
        //escreveSegundaLinha(result);
      }else{//====================================================  ELSE (NAO EH IGUAL =)
        vet[cont] = myKey;
        cont++;
        if(myKey == 'c'){//====================================================================== CLEAR
          clear = true;
        }else{//======================================================================  ELSE CLEAR
          buzzBip(25);
        }
      }
      Serial.println("----------------------");
      imprime(vet, cont);
    }else{//====================================================  CALCULO FEITO
      if(myKey >= '0' && myKey <= '9'){//====================================================================== EH NUMERO
        calculando = true;
        int i = 0;
        for(; i < 50; i++){
          vet[i] = 0;
          nums[i] = 0;
          vetOp[i] = 0;
        }
      }else if(myKey == 'c'){//====================================================================== CLEAR
        clear = true;
      }
    }
    if(clear){
      limpa();
      cont = 0;
      vet[0] = '\0';
      calculando = false;;
      buzzBip(70);
      result = 0;
      clear =  false;
    }else{
      escrevePrimeiraLinha(vet, cont, tam);
      escreveSegundaLinha(result);
    }    
    // buzzBip(5);
  }
}
