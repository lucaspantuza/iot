const int buttonPin = 7;  // Pino do botão
int lastButtonState = LOW;  // Estado anterior do botão
int randomValue;  // Variável para armazenar o número aleatório

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
  pinMode(buttonPin, INPUT_PULLUP);  // Configura o pino do botão como entrada com resistor pull-up interno
  randomSeed(analogRead(0));  // Inicializa a semente para gerar números aleatórios
}

void loop() {
  int buttonState = digitalRead(buttonPin);  // Lê o estado atual do botão

  // Verifica se o botão foi pressionado e o estado anterior era não pressionado
  if (buttonState == LOW && lastButtonState == HIGH) {
    randomValue = random(0, 100);  // Gera um número aleatório entre 0 e 99
    Serial.print("Número Aleatório: ");
    Serial.println(randomValue);  // Envia o número aleatório para a porta serial
  }

  lastButtonState = buttonState;  // Atualiza o estado anterior do botão
}
