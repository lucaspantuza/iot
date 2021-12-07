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


//Controle de panico
bool isPanic = false;
unsigned long isPanicMillis = 0;

//Ultimo print millis
unsigned long isPrintMillis = 0;

//-------

void setup() {

    // Inicia a Serial
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println();

    //Comandos - chaves fisicas
    pinMode(COM_PANIC, INPUT_PULLUP);

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

    if (digitalRead(COM_PANIC) == LOW) {
        setPanic();
    }

    // acoes do IR
    if (IrReceiver.decode()) {
        switch (IrReceiver.decodedIRData.command) {

            case CR_DIA: //arreganha tudo
                blackout_abrir();
                cortina_abrir(); //ja manda aba pra 90
                break;
            case CR_LUZDIA: //deixa veneziana fechada a 45
                cortina_aba_para_valor(45);
                blackout_abrir();
                break;
            case CR_NOITE:
                blackout_fechar();
                cortina_fechar();
                cortina_aba_para_valor(0);
                break;

            case CR_CORTINA_ABRIR:
                cortina_abrir();
                break;
            case CR_CORTINA_MEIO:
                cortina_semi_abrir();
                break;
            case CR_CORTINA_FECHAR:
                cortina_fechar();
                break;

            case CR_ABAS_000g:
                Serial.println("cortina_aba_0");
                cortina_aba_para_valor(0);
                break;
            case CR_ABAS_045g:
                Serial.println("cortina_aba_45");
                cortina_aba_para_valor(45);
                break;
            case CR_ABAS_090g:
                Serial.println("cortina_aba_90");
                cortina_aba_para_valor(90);
                break;
            case CR_ABAS_135g:
                Serial.println("cortina_aba_135");
                cortina_aba_para_valor(135);
                break;
            case CR_ABAS_180g:
                Serial.println("cortina_aba_180");
                cortina_aba_para_valor(180);
                break;

            case CR_BLACKOUT_ABRIR:
                blackout_abrir();
                break;
            case CR_BLACKOUT_MEIO:
                blackout_semi_abrir();
                break;
            case CR_BLACKOUT_FECHAR:
                blackout_fechar();
                break;
                
            case CR_PANIC:
                setPanic();
                printSensoresForce(true);
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
    //    Serial.print(CONFIG_CORTINA_POTENCIOMETRO_ABAS_VALOR_MIN);
    //    Serial.print("~");
    //    Serial.print(CONFIG_CORTINA_POTENCIOMETRO_ABAS_VALOR_MAX);
    //    Serial.print(": ");
    Serial.println(le_potenciometro_aba());
    Serial.println("-");
    Serial.print(" COM_PANIC.......: ");
    Serial.println(digitalRead(COM_PANIC));
    Serial.print(" funcao isntPanicTime(): ");
    Serial.println(isntPanicTime());
    Serial.print(" variavel isPanic: ");
    Serial.println(isPanic);
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

void setPanic() {
    isPanic = true;
    isPanicMillis = millis();

    Serial.println("PANIC!");
}

bool isntPanicTime() {
    return !isPanicTime();
}

bool isPanicTime() {

    //Panic pelo botao
    if (digitalRead(COM_PANIC) == LOW) {
        setPanic();
    }

    //Panic pelo controle
    if (IrReceiver.decode()) {
        if (IrReceiver.decodedIRData.command == CR_PANIC) {
            setPanic();
        }
        IrReceiver.resume();
    }

    // Atualiza a valiavel caso ela esteja obsoleta
    if (isPanic && millis() - isPanicMillis > PANIC_OBSOLETO) {
        isPanic = false;
    }

    return isPanic;
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

void cortina_aba_para_valor(int valor) {

    if ((valor == 0 || valor == 180) && digitalRead(SEN_CORTINA_FIM) != LOW) {
        Serial.println("So pode girar com cortina fechada para esse valor (0 ou 180)");
        return;
    } else if ((valor == 45 || valor == 135) && digitalRead(SEN_CORTINA_FIM) != LOW && digitalRead(SEN_CORTINA_MEIO) != LOW) {
        Serial.println("So pode girar com cortina semiaberta/fechada para esse valor (45 ou 135)");
        return;
    }

    Serial.print("vai para: ");
    Serial.println(valor);

    int pot = le_potenciometro_aba();

    // Se ja estiver fechado
    if (pot >= (valor - FAIXA_SEGURANCA_VALOR_ANALOGIC) && pot <= (valor + FAIXA_SEGURANCA_VALOR_ANALOGIC)) return;

    // direcao A do servo
    while (pot > valor && isntPanicTime()) {
        servoAba.goB();
        delay(TEMPO_LOOP_MILLIS);
        pot = le_potenciometro_aba();
    }
    servoAba.stop();

    // direcao B do servo
    while (pot < valor && isntPanicTime()) {
        servoAba.goA();
        delay(TEMPO_LOOP_MILLIS);
        pot = le_potenciometro_aba();
    }
    servoAba.stop();

}

//---

void cortina_abrir() {
    Serial.println("cortina_abrir");

    // Primeiro abre as abas para deslocamento
    cortina_aba_para_valor(90);

    // direcao A do servo
    while (digitalRead(SEN_CORTINA_INICIO) != LOW && isntPanicTime()) {
        servoComprimento.goA();
        delay(TEMPO_LOOP_MILLIS);
    }
    servoComprimento.stop();
}

void cortina_fechar() {
    Serial.println("cortina_fechar");

    // Primeiro abre as abas para deslocamento
    cortina_aba_para_valor(90);

    // direcao B do servo
    while (digitalRead(SEN_CORTINA_FIM) != LOW && isntPanicTime()) {
        servoComprimento.goB();
        delay(TEMPO_LOOP_MILLIS);
    }
    servoComprimento.stop();

    // Por fim, fecha as abas
    //    cortina_fechar_aba();
}

void cortina_semi_abrir() {
    Serial.println("cortina_semi_abrir");

    cortina_aba_para_valor(90);

    if (digitalRead(SEN_CORTINA_INICIO) == LOW) {
        while (digitalRead(SEN_CORTINA_MEIO) != LOW && isntPanicTime()) {
            servoComprimento.goB();
            delay(TEMPO_LOOP_MILLIS);
        }
        servoComprimento.stop();
    } else if (digitalRead(SEN_CORTINA_FIM) == LOW) {
        while (digitalRead(SEN_CORTINA_MEIO) != LOW && isntPanicTime()) {
            servoComprimento.goA();
            delay(TEMPO_LOOP_MILLIS);
        }
        servoComprimento.stop();
    } else {
        // neste caso a cortina esta parada no limbo. Abre tudo pra depois ir pro meio
        Serial.println("primeiro abre pra depois mandar parar no meio");
        cortina_abrir();
        cortina_semi_abrir();
    }
}

//---

void blackout_abrir() {
    Serial.print("CR_BLACKOUT_ABRIR");

    while (digitalRead(SEN_BLACKOUT_INICIO) != LOW && isntPanicTime()) {
        servoBlackout.goB();
        delay(TEMPO_LOOP_MILLIS);
    }
    servoBlackout.stop();
}

void blackout_semi_abrir() {
    Serial.print("CR_BLACKOUT_MEIO");
    if (digitalRead(SEN_BLACKOUT_INICIO) == LOW) {
        while (digitalRead(SEN_BLACKOUT_MEIO) != LOW && isntPanicTime()) {
            servoBlackout.goA();
            delay(TEMPO_LOOP_MILLIS);
        }
        servoBlackout.stop();
    } else if (digitalRead(SEN_BLACKOUT_FIM) == LOW) {
        while (digitalRead(SEN_BLACKOUT_MEIO) != LOW && isntPanicTime()) {
            servoBlackout.goB();
            delay(TEMPO_LOOP_MILLIS);
        }
        servoBlackout.stop();
    } else {
        // neste caso a cortina esta parada no limbo. Abre tudo pra depois ir pro meio
        Serial.println("primeiro abre pra depois mandar parar no meio");
        blackout_abrir();
        blackout_semi_abrir();
    }
}

void blackout_fechar() {
    Serial.print("CR_BLACKOUT_FECHAR");

    while (digitalRead(SEN_BLACKOUT_FIM) != LOW && isntPanicTime()) {
        servoBlackout.goA();
        delay(TEMPO_LOOP_MILLIS);
        printSensores();
    }
    servoBlackout.stop();
}
