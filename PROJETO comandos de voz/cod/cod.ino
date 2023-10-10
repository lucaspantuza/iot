int led = 4;//Atribui o pino 8 a variável led
int ky = 32;//Atribui o pino 9 - conectado ao sensor, a variável ky
int valorky = 0;//Declara a variável valorky do tipo inteiro
bool statusLed = false;//Declara a variável statusLed do tipo booleano

void setup() {
  pinMode (led, OUTPUT);//Define led (porta digital 8) como saída
  pinMode (ky, INPUT);//Define ky (porta analógico 9) como saída
  Serial.begin(9600);//Inicialização da comunicação serial, com velocidade de comunicação de 9600
}
void loop() {
  valorky = digitalRead(ky);//Lê o valor do sensor e armazena na variável valorky
  Serial.println(valorky);//Imprime na serial os dados de valorky
  delay(20);//Intervalo de 20 milissegundos
  if (valorky == HIGH && statusLed == false) { //Se valorky for igual a 1 (HIGH) e statusLed for igual a false:
    delay(100);
    digitalWrite(led, HIGH);//Coloca led em alto para acioná-lo
    statusLed = true;//Coloca statusLed como true
  }
  else {//Senão:
    if (valorky == HIGH && statusLed == true) { //Se valorky for igual a 1 (HIGH) e statusLed for igual a true
      delay(100);
      digitalWrite(led, LOW);//Coloca led em baixo para desligá-lo
      statusLed = false;//Retorna statusLed como false
    }
  }
}