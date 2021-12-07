#ifndef SERVO360_H
#define SERVO360_H

#include <Servo.h> 

#define SERVO360_H_VALORPARADO 90
#define SERVO360_H_VALORMAX 270
#define SERVO360_H_VALORMIN 0
#define SERVO360_H_DELAY 50
#define SERVO360_H_ACELERAR false


class Servo360 {
private:

    Servo s; //OBJETO DO TIPO SERVO
    int pino;
    //    int posicao;
    bool isAtuando;
    
    
    //    void liga(){
    //        if(!isAtuando) s.attach(this->pino);
    //    }
    //    void desliga(){
    //        s.detach();
    ////        this->posicao = 90;
    //        this->isAtuando = false;
    //    }
public:

    Servo360(int pino) {
        this->pino = pino;
        //        this->posicao = 0;
        //        s.attach(this->pino); //ASSOCIAÇÃO DO PINO DIGITAL AO OBJETO DO TIPO SERVO
        //        s.write(90); //INICIA O MOTOR NA POSIÇÃO 0º  
        //        s.detach();
        this->isAtuando = false;
    }

    void stop() {
        s.detach();
        this->isAtuando = false;
    }

    void goA() {

        if (!isAtuando) {
            s.attach(this->pino);
            this->isAtuando = true;

            //aceleracao
            for (int posicao = SERVO360_H_VALORPARADO; SERVO360_H_ACELERAR && posicao < SERVO360_H_VALORMAX; posicao++) {
                s.write(posicao);
                delay(SERVO360_H_DELAY);
            }
        } else
            s.write(SERVO360_H_VALORMAX);
    }

    void goB() {
        
        if (!isAtuando) {
            s.attach(this->pino);
            this->isAtuando = true;

            //aceleracao
            for (int posicao = SERVO360_H_VALORPARADO; SERVO360_H_ACELERAR && posicao > SERVO360_H_VALORMIN; posicao--) {
                s.write(posicao);
                delay(SERVO360_H_DELAY);
            }
        } else
            s.write(SERVO360_H_VALORMIN);
    }
};

#endif /* SERVO360_H */
