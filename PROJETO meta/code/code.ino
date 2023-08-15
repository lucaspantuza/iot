// Gira 90 graus nos 2 sentidos
#include <Stepper.h>  // inclue a biblioteca Stepper.h

const int PassoPorVolta = 500;  // Passo por Volta do Motor de Passo

// Inicializa a biblioteca Stepper.h
// O motor de passo =>  MotorP
Stepper MotorP(PassoPorVolta, 8, 10, 9, 11);

void setup() {
  // Ajusta velocidade para 60 RPM
  MotorP.setSpeed(60);
}

void loop() {
  // Gira 360 graus no sentido horario
  // Em 3 degraus de 120 graus
  for (int i = 0; i < 3; i++) {
    MotorP.step(682);
    delay(1000);
  }
  // Gira 360 graus no sentido anti-horario
  // Em 3 degraus de 120 graus
  for (int i = 0; i < 3; i++) {
    MotorP.step(-682);
    delay(1000);
  }
}