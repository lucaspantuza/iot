#ifndef SERVO360_H
#define SERVO360_H

#include <Servo.h> 
#include <Arduino.h>

//#define SERVO360_H_VALORPARADO 90
#define SERVO360_H_VALORMAX 180
#define SERVO360_H_VALORMIN 0
//#define SERVO360_H_DELAY 50
//#define SERVO360_H_ACELERAR false
#define SERVO360_H_TEMPOPOSATTACH 500

class Servo360 {
private:

    Servo s; //OBJETO DO TIPO SERVO
    int pino;
    //    int posicao;
    bool isAtuando;
    bool direcaoInvertida;


    //    void liga(){
    //        if(!isAtuando) s.attach(this->pino);
    //    }
    //    void desliga(){
    //        s.detach();
    ////        this->posicao = 90;
    //        this->isAtuando = false;
    //    }
public:

    Servo360(int pino, bool direcaoInvertida = false) {
        this->pino = pino;
        this->direcaoInvertida = direcaoInvertida;
        pinMode(this->pino, OUTPUT);
        this->isAtuando = false;
    }

    void stop() {
        //        if (this->isAtuando) {
        this->s.detach();
        delay(SERVO360_H_TEMPOPOSATTACH);
        this->isAtuando = false;
        //        }
    }

    void goA() {

        if (!this->isAtuando) {
            this->s.attach(this->pino);
            delay(SERVO360_H_TEMPOPOSATTACH);
            this->isAtuando = true;

            //            //aceleracao
            //            for (int posicao = SERVO360_H_VALORPARADO; SERVO360_H_ACELERAR && posicao < SERVO360_H_VALORMAX; posicao++) {
            //                this->s.write(posicao);
            //                delay(SERVO360_H_DELAY);
            //            }
        } //else

        this->s.write((!direcaoInvertida) ? SERVO360_H_VALORMAX : SERVO360_H_VALORMIN);
    }

    void goB() {

        if (!this->isAtuando) {
            this->s.attach(this->pino);
            delay(SERVO360_H_TEMPOPOSATTACH);
            this->isAtuando = true;

            //            //aceleracao
            //            for (int posicao = SERVO360_H_VALORPARADO; SERVO360_H_ACELERAR && posicao > SERVO360_H_VALORMIN; posicao--) {
            //                this->s.write(posicao);
            //                delay(SERVO360_H_DELAY);
            //            }
        } //else
        this->s.write((!direcaoInvertida) ? SERVO360_H_VALORMIN : SERVO360_H_VALORMAX);
    }
};

#endif /* SERVO360_H */
