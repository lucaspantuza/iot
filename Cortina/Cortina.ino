#include "defines.h"
#include <Arduino.h>
#include <IRremote.h>  
#include "ServoPonteH.h"
#include "Servo360.h"

//-------

//Servos
Servo360 servoComprimento(ACAO_CORTINA_COMPRIMENTO);
Servo360 servoBlackout(ACAO_CORTINA_BLACKOUT);
ServoPonteH servoAba(ACAO_CORTINA_ABA1, ACAO_CORTINA_ABA2);

//Ultimo print millis
unsigned long isPrintMillis = 0;

//-------

void setup() {

    // Inicia a Serial
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println();

    //Pinagem do projeto
    pinMode(SEN_CORTINA_POTENCIOMETRO_ABAS, INPUT);
    pinMode(SEN_CORTINA_POTENCIOMETRO_ABAS_CONFIG_MIN, INPUT);
    pinMode(SEN_CORTINA_POTENCIOMETRO_ABAS_CONFIG_MAX, INPUT);

    pinMode(SEN_CORTINA_INICIO, INPUT_PULLUP);
    pinMode(SEN_CORTINA_MEIO, INPUT_PULLUP);
    pinMode(SEN_CORTINA_FIM, INPUT_PULLUP);

    pinMode(SEN_BLACKOUT_INICIO, INPUT_PULLUP);
    pinMode(SEN_BLACKOUT_MEIO, INPUT_PULLUP);
    pinMode(SEN_BLACKOUT_FIM, INPUT_PULLUP);

    pinMode(ACAO_CORTINA_ABA1, OUTPUT);
    pinMode(ACAO_CORTINA_ABA2, OUTPUT);
    digitalWrite(ACAO_CORTINA_ABA1, LOW);
    digitalWrite(ACAO_CORTINA_ABA2, LOW);

    // Inicializa o receptor IR  
    IrReceiver.begin(SEN_IR, ENABLE_LED_FEEDBACK);
}

void loop() {

    // acoes do IR
    if (IrReceiver.decode()) {
        int pos_original;
        
        switch (IrReceiver.decodedIRData.command) {

            case CR_ABRE_TUDO: //arreganha tudo
                Serial.println("CR_ABRE_TUDO");
                blackout_abrir();
                cortina_aba_para_valor(90);
                cortina_abrir(); 
                break;
            case CR_LUZ_DIARIA: //deixa veneziana fechada a 45
                Serial.println("CR_LUZ_DIARIA");
                blackout_abrir();
                cortina_aba_para_valor(90);
                cortina_fechar();
                cortina_aba_para_valor(45);
                break;
            case CR_FECHA_TUDO:
                Serial.println("CR_FECHA_TUDO");
                cortina_aba_para_valor(90);
                cortina_fechar();
                cortina_aba_para_valor(0);
                blackout_fechar();
                break;

                
            case CR_CORTINA_ABRIR:
                Serial.println("CR_CORTINA_ABRIR");
                pos_original = cortina_aba_para_valor(90);
                cortina_abrir();
                cortina_aba_para_valor(pos_original);
                break;
            case CR_CORTINA_MEIO:
                Serial.println("CR_CORTINA_MEIO");
                pos_original = cortina_aba_para_valor(90);
                cortina_semi_abrir();
                cortina_aba_para_valor(pos_original);
                break;
            case CR_CORTINA_FECHAR:
                Serial.println("CR_CORTINA_FECHAR");
                pos_original = cortina_aba_para_valor(90);
                cortina_fechar();
                cortina_aba_para_valor(pos_original);
                break;

                
            case CR_ABAS_000g:
                Serial.println("CR_ABAS_000g");
                cortina_aba_para_valor(0);
                break;
            case CR_ABAS_045g:
                Serial.println("CR_ABAS_045g");
                cortina_aba_para_valor(45);
                break;
            case CR_ABAS_090g:
                Serial.println("CR_ABAS_090g");
                cortina_aba_para_valor(90);
                break;
            case CR_ABAS_135g:
                Serial.println("CR_ABAS_135g");
                cortina_aba_para_valor(135);
                break;
            case CR_ABAS_180g:
                Serial.println("CR_ABAS_180g");
                cortina_aba_para_valor(180);
                break;

                
            case CR_BLACKOUT_ABRIR:
                Serial.println("CR_BLACKOUT_ABRIR");
                blackout_abrir();
                break;
            case CR_BLACKOUT_MEIO:
                Serial.println("CR_BLACKOUT_MEIO");
                blackout_semi_abrir();
                break;
            case CR_BLACKOUT_FECHAR:
                Serial.println("CR_BLACKOUT_FECHAR");
                blackout_fechar();
                break;

                
            default:
                printSensoresForce(true);
        }
        IrReceiver.resume();
    }

    delay(TEMPO_LOOP_MILLIS);
}

//----------------------------

void printSensores() {
    printSensoresForce(false);
}

void printSensoresForce(bool force) {

    //Verifica se ja passou o tempo do ultimo print
    if (!force) {
        if (millis() - isPrintMillis > TEMPO_ENTRE_PRINT) {
            isPrintMillis = millis();
        } else return;
    }

    Serial.println();
    Serial.println("---");
    Serial.println("----------------------------------------");

    Serial.print("Valor lido do controle remoto: ");
    Serial.println(IrReceiver.decodedIRData.command);
    Serial.println("-");
    Serial.print(" ABA analogic................: ");
    Serial.println(analogRead(SEN_CORTINA_POTENCIOMETRO_ABAS));
    Serial.print(" ABA analogic config MIN.....: ");
    Serial.println(analogRead(SEN_CORTINA_POTENCIOMETRO_ABAS_CONFIG_MIN));
    Serial.print(" ABA analogic config MAX.....: ");
    Serial.println(analogRead(SEN_CORTINA_POTENCIOMETRO_ABAS_CONFIG_MAX));
    Serial.print(" ABA analogic convertido.....: ");
    Serial.println(le_potenciometro_aba());
    Serial.println("-");
    Serial.print(" SEN_CORTINA_INICIO: ");
    Serial.println(digitalRead(SEN_CORTINA_INICIO));
    Serial.print(" SEN_CORTINA_MEIO..: ");
    Serial.println(digitalRead(SEN_CORTINA_MEIO));
    Serial.print(" SEN_CORTINA_FIM...: ");
    Serial.println(digitalRead(SEN_CORTINA_FIM));
    Serial.println("-");
    Serial.print(" SEN_BLACKOUT_INICIO: ");
    Serial.println(digitalRead(SEN_BLACKOUT_INICIO));
    Serial.print(" SEN_BLACKOUT_MEIO..: ");
    Serial.println(digitalRead(SEN_BLACKOUT_MEIO));
    Serial.print(" SEN_BLACKOUT_FIM...: ");
    Serial.println(digitalRead(SEN_BLACKOUT_FIM));

    Serial.println("----------------------------------------");
    Serial.println("---");
    Serial.println();
}

//---

int le_potenciometro_aba() {
    int val = analogRead(SEN_CORTINA_POTENCIOMETRO_ABAS);
    int valMin = analogRead(SEN_CORTINA_POTENCIOMETRO_ABAS_CONFIG_MIN);
    int valMax = analogRead(SEN_CORTINA_POTENCIOMETRO_ABAS_CONFIG_MAX);
    if (val > valMax) val = valMax;
    if (val < valMin) val = valMin;

    return map(val,
            valMin,
            valMax,
            0,
            180);
}

int cortina_aba_para_valor(int valor) {

    // Guarda para retorno da funcao
    int pot_original = le_potenciometro_aba();
    
    if ((valor == 0 || valor == 180) && digitalRead(SEN_CORTINA_FIM) != LOW) {
        //So pode girar com cortina fechada para esse valor (0 ou 180)
        return;
    } else if ((valor == 45 || valor == 135) && digitalRead(SEN_CORTINA_FIM) != LOW && digitalRead(SEN_CORTINA_MEIO) != LOW) {
        //So pode girar com cortina semiaberta/fechada para esse valor (45 ou 135)
        return;
    }

    int pot = pot_original;

    // Se ja estiver fechado
    if (pot >= (valor - FAIXA_SEGURANCA_VALOR_ANALOGIC) && pot <= (valor + FAIXA_SEGURANCA_VALOR_ANALOGIC)) return;

    // direcao A do servo
    while (pot > valor) {
        servoAba.goB();
        delay(TEMPO_LOOP_MILLIS);
        pot = le_potenciometro_aba();
    }
    servoAba.stop();

    // direcao B do servo
    while (pot < valor) {
        servoAba.goA();
        delay(TEMPO_LOOP_MILLIS);
        pot = le_potenciometro_aba();
    }
    servoAba.stop();

    return pot_original;
}

//---

void cortina_abrir() {
    // direcao A do servo
    while (digitalRead(SEN_CORTINA_INICIO) != LOW) {
        servoComprimento.goA();
        delay(TEMPO_LOOP_MILLIS);
    }
    servoComprimento.stop();
}

void cortina_fechar() {
    // direcao B do servo
    while (digitalRead(SEN_CORTINA_FIM) != LOW) {
        servoComprimento.goB();
        delay(TEMPO_LOOP_MILLIS);
    }
    servoComprimento.stop();
}

void cortina_semi_abrir() {
    if (digitalRead(SEN_CORTINA_INICIO) == LOW) {
        while (digitalRead(SEN_CORTINA_MEIO) != LOW) {
            servoComprimento.goB();
            delay(TEMPO_LOOP_MILLIS);
        }
        servoComprimento.stop();
    } else if (digitalRead(SEN_CORTINA_FIM) == LOW) {
        while (digitalRead(SEN_CORTINA_MEIO) != LOW) {
            servoComprimento.goA();
            delay(TEMPO_LOOP_MILLIS);
        }
        servoComprimento.stop();
    } else {
        // neste caso a cortina esta parada no limbo. Abre tudo pra depois ir pro meio
        // direcao A do servo (abre ate o inicio ou meio, o que acontecer primeiro)
        while (digitalRead(SEN_CORTINA_INICIO) != LOW && digitalRead(SEN_CORTINA_MEIO) != LOW) {
            servoComprimento.goA();
            delay(TEMPO_LOOP_MILLIS);
        }
        servoComprimento.stop();

        // Caso tenha precisado ir ate o inicio, agora vai pra metade
        if (digitalRead(SEN_CORTINA_INICIO) == LOW)
            cortina_semi_abrir();
    }
}

//---

void blackout_abrir() {
    while (digitalRead(SEN_BLACKOUT_INICIO) != LOW) {
        servoBlackout.goB();
        delay(TEMPO_LOOP_MILLIS);
    }
    servoBlackout.stop();
}

void blackout_fechar() {
    while (digitalRead(SEN_BLACKOUT_FIM) != LOW) {
        servoBlackout.goA();
        delay(TEMPO_LOOP_MILLIS);
    }
    servoBlackout.stop();
}

void blackout_semi_abrir() {
    if (digitalRead(SEN_BLACKOUT_INICIO) == LOW) {
        while (digitalRead(SEN_BLACKOUT_MEIO) != LOW) {
            servoBlackout.goA();
            delay(TEMPO_LOOP_MILLIS);
        }
        servoBlackout.stop();
    } else if (digitalRead(SEN_BLACKOUT_FIM) == LOW) {
        while (digitalRead(SEN_BLACKOUT_MEIO) != LOW) {
            servoBlackout.goB();
            delay(TEMPO_LOOP_MILLIS);
        }
        servoBlackout.stop();
    } else {
        // neste caso a cortina esta parada no limbo. Abre tudo pra depois ir pro meio
        // (abre ate o inicio ou meio, o que acontecer primeiro)
        while (digitalRead(SEN_BLACKOUT_INICIO) != LOW && digitalRead(SEN_BLACKOUT_MEIO) != LOW) {
            servoBlackout.goB();
            delay(TEMPO_LOOP_MILLIS);
        }
        servoBlackout.stop();

        // Caso tenha precisado ir ate o inicio, agora vai pra metade
        if (digitalRead(SEN_BLACKOUT_INICIO) == LOW)
            blackout_semi_abrir();
    }
}
