#ifndef SERVOPONTEH_H
#define SERVOPONTEH_H

#include <Arduino.h>

class ServoPonteH {
private:

    int pino1;
    int pino2;

public:

    ServoPonteH(int pino1, int pino2) {
        this->pino1 = pino1;
        this->pino2 = pino2;

        pinMode(this->pino1, OUTPUT);
        pinMode(this->pino2, OUTPUT);

        digitalWrite(this->pino1, LOW);
        digitalWrite(this->pino2, LOW);
    }

    void stop() {
        digitalWrite(this->pino1, LOW);
        digitalWrite(this->pino2, LOW);
    }

    void goA() {
        digitalWrite(this->pino1, HIGH);
        digitalWrite(this->pino2, LOW);
    }

    void goB() {
        digitalWrite(this->pino1, LOW);
        digitalWrite(this->pino2, HIGH);
    }
};

#endif /* SERVOPONTEH_H */

