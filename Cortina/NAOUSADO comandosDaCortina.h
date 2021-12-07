#include "defines.h"
#include "NAOUSADO servosDaCortina.h"
#include <Arduino.h>

bool isPanic = false;
unsigned long isPanicMillis = 0;

void setPanic() {
    isPanic = true;
    isPanicMillis = millis();

    Serial.println("PANIC!");

    // Leitura das entradas
    Serial.print(" ABA ");
    Serial.println(map(analogRead(SEN_CORTINA_POTENCIOMETRO_ABAS), 0, 1024, 0, 10));
    Serial.print(" ABAanalogic ");
    Serial.println(analogRead(SEN_CORTINA_POTENCIOMETRO_ABAS));
    Serial.print(" ABAanalogic convertido ");
    Serial.println(le_potenciometro_aba());
    Serial.print(" COM_PANIC ");
    Serial.println(digitalRead(COM_PANIC));
    Serial.print(" SEN_CORTINA_INICIO ");
    Serial.println(digitalRead(SEN_CORTINA_INICIO));
    Serial.print(" SEN_CORTINA_MEIO ");
    Serial.println(digitalRead(SEN_CORTINA_MEIO));
    Serial.print(" SEN_CORTINA_FIM ");
    Serial.println(digitalRead(SEN_CORTINA_FIM));
    Serial.println();
    Serial.println();
}

bool noPanic() {

    // Atualiza a valiavel caso ela esteja obsoleta
    if (isPanic && millis() - isPanicMillis > PANIC_OBSOLETO) {
        isPanic = false;
    }

    return isPanic;
}

//---

void descartaPressionamento(int cod) {
    while (digitalRead(cod) == LOW);
}

int le_potenciometro_aba() {
    return map(analogRead(SEN_CORTINA_POTENCIOMETRO_ABAS),
            SEN_CORTINA_POTENCIOMETRO_ABAS_VALOR_MIN,
            SEN_CORTINA_POTENCIOMETRO_ABAS_VALOR_MAX,
            SEN_CORTINA_POTENCIOMETRO_ABAS_POS_FECHADO_A,
            SEN_CORTINA_POTENCIOMETRO_ABAS_POS_FECHADO_B);
}

//---

void cortina_aba_para_valor(int valor) {

    //    if(digitalRead(SEN_CORTINA_FIM) != LOW){
    //        Serial.println("So pode girar com cortina fechada");
    //        return;
    //    }

    int pot = le_potenciometro_aba();

    // Se ja estiver fechado
    if (pot == valor) return;

    // direcao A do servo
    while (pot > valor && noPanic()) {
        digitalWrite(ACAO_CORTINA_ABA2, HIGH);
        delay(TEMPO_LOOP_MILLIS);
        pot = le_potenciometro_aba();
    }
    digitalWrite(ACAO_CORTINA_ABA2, LOW);

    // direcao B do servo
    while (pot < valor && noPanic()) {
        digitalWrite(ACAO_CORTINA_ABA1, HIGH);
        delay(TEMPO_LOOP_MILLIS);
        pot = le_potenciometro_aba();
    }
    digitalWrite(ACAO_CORTINA_ABA1, LOW);
}

void cortina_fechar_aba() {
    Serial.println("cortina_fechar_aba");
    cortina_aba_para_valor(SEN_CORTINA_POTENCIOMETRO_ABAS_POS_FECHADO_A);
}

void cortina_virar_aba() {
    Serial.println("cortina_virar_aba");
    int pot = le_potenciometro_aba();
    if (pot == SEN_CORTINA_POTENCIOMETRO_ABAS_POS_FECHADO_A)
        cortina_aba_para_valor(SEN_CORTINA_POTENCIOMETRO_ABAS_POS_FECHADO_B);
    else
        cortina_aba_para_valor(SEN_CORTINA_POTENCIOMETRO_ABAS_POS_FECHADO_A);
}

void cortina_abrir_aba() {
    Serial.println("cortina_abrir_aba");
    int pos = (SEN_CORTINA_POTENCIOMETRO_ABAS_POS_FECHADO_B - SEN_CORTINA_POTENCIOMETRO_ABAS_POS_FECHADO_A) / 2;
    cortina_aba_para_valor(pos);
}

void cortina_girando_a_aba() {
    Serial.println("cortina_girando_a_aba");

    // direcao A do servo
    while (digitalRead(COM_CORTINA_GIRANDO_A_ABA) == LOW && noPanic()) {
        digitalWrite(ACAO_CORTINA_ABA1, HIGH);
        delay(TEMPO_LOOP_MILLIS);
    }
    digitalWrite(ACAO_CORTINA_ABA1, LOW);
}

void cortina_girando_b_aba() {
    Serial.println("cortina_girando_b_aba");

    // direcao A do servo
    while (digitalRead(COM_CORTINA_GIRANDO_B_ABA) == LOW && noPanic()) {
        digitalWrite(ACAO_CORTINA_ABA2, HIGH);
        delay(TEMPO_LOOP_MILLIS);
    }
    digitalWrite(ACAO_CORTINA_ABA2, LOW);
}

//---

void servoDA(Servo s) {
    s.write(80);
}

void servoDB(Servo s) {
    s.write(100);
}

void servoP(Servo s) {
    s.write(90);
}

//---

//void cortina_abrindo() {
//    Serial.println("cortina_abrindo");
//
//    // direcao A do servo
//    while (digitalRead(COM_CORTINA_ABRINDO) == LOW && noPanic() && digitalRead(SEN_CORTINA_INICIO) != LOW) {
//        digitalWrite(ACAO_CORTINA_S2_R1, HIGH);
//        delay(TEMPO_LOOP_MILLIS);
//    }
//    digitalWrite(ACAO_CORTINA_S2_R1, LOW);
//}
//void cortina_abrindo_on() {
//    servoDA(servoComprimento);
//}
//void cortina_abrindo_off() {
//    servoP(servoComprimento);
//}

void cortina_abrir() {
    Serial.println("cortina_abrir");

    // Primeiro abre as abas para deslocamento
    cortina_abrir_aba();

    // direcao A do servo
    while (digitalRead(SEN_CORTINA_INICIO) != LOW && noPanic()) {
        //        digitalWrite(ACAO_CORTINA_S2_R1, HIGH);
        servoDB(servoComprimento);
        delay(TEMPO_LOOP_MILLIS);
    }
    servoP(servoComprimento);
    //    digitalWrite(ACAO_CORTINA_S2_R1, LOW);
}

//void cortina_fechando() {
//    Serial.println("cortina_fechando");
//
//    // direcao B do servo
//    while (digitalRead(COM_CORTINA_FECHANDO) == LOW && noPanic() && digitalRead(SEN_CORTINA_FIM) != LOW) {
//        digitalWrite(ACAO_CORTINA_S2_R2, HIGH);
//        delay(TEMPO_LOOP_MILLIS);
//    }
//    digitalWrite(ACAO_CORTINA_S2_R2, LOW);
//}

void cortina_fechar() {
    Serial.println("cortina_fechar");

    // Primeiro abre as abas para deslocamento
    cortina_abrir_aba();

    // direcao B do servo
    while (digitalRead(SEN_CORTINA_FIM) != LOW && noPanic()) {
        //        digitalWrite(ACAO_CORTINA_S2_R2, HIGH);
        servoDA(servoComprimento);
        delay(TEMPO_LOOP_MILLIS);
    }
    //    digitalWrite(ACAO_CORTINA_S2_R2, LOW);
    servoP(servoComprimento);

    // Por fim, fecha as abas
    cortina_fechar_aba();
}

void cortina_semi_abrir() {
    Serial.println("cortina_semi_abrir");

    if (digitalRead(SEN_CORTINA_INICIO) == LOW) {
        while (digitalRead(SEN_CORTINA_MEIO) != LOW && noPanic()) {
            servoDA(servoComprimento);
            delay(TEMPO_LOOP_MILLIS);
        }
        servoP(servoComprimento);
    } else if (digitalRead(SEN_CORTINA_FIM) == LOW) {
        while (digitalRead(SEN_CORTINA_MEIO) != LOW && noPanic()) {
            servoDB(servoComprimento);
            delay(TEMPO_LOOP_MILLIS);
        }
        servoP(servoComprimento);
    } else {

        // neste caso a cortina esta parada no limbo. Abre tudo pra depois ir pro meio
        Serial.println("primeiro abre pra depois mandar parar no meio");
        cortina_abrir();
        cortina_semi_abrir();
//        while (digitalRead(SEN_CORTINA_MEIO) != LOW && noPanic()) {
//            digitalWrite(ACAO_CORTINA_S2_R2, HIGH);
//            delay(TEMPO_LOOP_MILLIS);
//        }
//        digitalWrite(ACAO_CORTINA_S2_R2, LOW);
    }
}

//void cortina_com_abrir_fechar() {
//    Serial.println("cortina_com_abrir_fechar");
//
//    if (digitalRead(SEN_CORTINA_FIM) == LOW) {
//        cortina_abrir_aba();
//        cortina_abrir();
//    } else {
//        cortina_fechar();
//        cortina_fechar_aba();
//    }
//}


//---

void blackout_abrindo() {
    Serial.print("CR_BLACKOUT_MAIS");
}

void blackout_fechando() {
    Serial.print("CR_BLACKOUT_MENOS");
}

void blackout_abrir() {
    Serial.print("CR_BLACKOUT_ABRIR");
}

void blackout_semi_abrir() {
    Serial.print("CR_BLACKOUT_MEIO");
}

void blackout_fechar() {
    Serial.print("CR_BLACKOUT_FECHAR");
}

