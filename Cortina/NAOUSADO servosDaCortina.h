#include <Servo.h>
#include "defines.h"

class ServosDaCortina {
    
private:
    Servo servoAlgulo;
    Servo servoComprimento;
    Servo servoBlackout;
    
public:

    ServosDaCortina() {
    }

    void anguloAbra() {
        servoAlgulo.attach(SERVO_ANGULO);
        servoAlgulo.write(180);
    }

    void anguloPare() {
        servoAlgulo.detach();
    }

    void anguloFeche() {
        servoAlgulo.attach(SERVO_ANGULO);
        servoAlgulo.write(0);
    }

    //---
    
    void comprimentoAbra() {
        servoComprimento.attach(SERVO_COMPRIMENTO);
        servoComprimento.write(180);
    }

    void comprimentoPare() {
        servoComprimento.detach();
    }

    void comprimentoFeche() {
        servoComprimento.attach(SERVO_COMPRIMENTO);
        servoComprimento.write(0);
    }
    
    //---
    
    void blackoutAbra() {
        servoBlackout.attach(SERVO_BLACKOUT);
        servoBlackout.write(180);
    }

    void blackoutPare() {
        servoBlackout.detach();
    }

    void blackoutFeche() {
        servoBlackout.attach(SERVO_BLACKOUT);
        servoBlackout.write(0);
    }
};