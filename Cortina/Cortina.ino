#include <Arduino.h>
#include <IRremote.h>  

#include "defines.h"
#include "ServoPonteH.h"
#include "Servo360.h"

//#include "Log.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//-------

//Servos
Servo360 servoComprimento(ACAO_CORTINA_COMPRIMENTO);
Servo360 servoBlackout(ACAO_CORTINA_BLACKOUT);
ServoPonteH servoAba(ACAO_CORTINA_ABA1, ACAO_CORTINA_ABA2);

// Display LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Ultimo print millis
unsigned long isPrintMillis = 0;







//Servo servomotor;


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

    //    pinMode(ACAO_CORTINA_ABA1, OUTPUT);
    //    pinMode(ACAO_CORTINA_ABA2, OUTPUT);
    //    digitalWrite(ACAO_CORTINA_ABA1, LOW);
    //    digitalWrite(ACAO_CORTINA_ABA2, LOW);

    // Inicializa o receptor IR  
    IrReceiver.begin(SEN_IR, ENABLE_LED_FEEDBACK);

    // Display LCD
    lcd.begin();
    lcd.backlight();

    Serial.println("Setup realizado");


    //    servomotor.attach(5);
    // Associa o pino 7 ao objeto servomotor
    //    servomotor.write(0); // Inicia servomotor na posiï¿½ï¿½o zero
}

void loop() {
    //
    //    Serial.println("0");
    //    servomotor.attach(5);
    //    delay(500);
    //    servomotor.write(0);
    ////    servomotor.writeMicroseconds(1000);
    //    servomotor.detach();
    //    delay(3000);
    //
    ////    Serial.println("90");
    ////    servomotor.attach(5);
    ////    delay(500);
    ////    servomotor.write(90);
    //////    servomotor.writeMicroseconds(1500);
    ////    servomotor.detach();
    ////    delay(3000);
    //    
    //    
    //    Serial.println("180");
    //    servomotor.attach(5);
    //    delay(500);
    //    servomotor.write(180);
    ////    servomotor.writeMicroseconds(2000);
    //    servomotor.detach();
    //    delay(8000);
    //    ////    servoBlackout.goA();
    //    ////    servoBlackout.stop();
    //
    //



    // Verificacao de comando manual via Serial
    if (Serial.available() > 0) {
        realizaAcaoManual(Serial.readString());
    }

    // acoes do IR
    if (IrReceiver.decode()) {

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
                if (!if_cortina_aberta()) {
                    int pos_original = cortina_aba_para_valor(90);
                    cortina_abrir();
                    cortina_aba_para_valor(pos_original);
                }
                break;
            case CR_CORTINA_MEIO:
                Serial.println("CR_CORTINA_MEIO");
                if (!if_cortina_semi_aberta()) {
                    int pos_original = cortina_aba_para_valor(90);
                    cortina_semi_abrir();
                    cortina_aba_para_valor(pos_original);
                }
                break;
            case CR_CORTINA_FECHAR:
                Serial.println("CR_CORTINA_FECHAR");
                if (!if_cortina_fechada()) {
                    int pos_original = cortina_aba_para_valor(90);
                    cortina_fechar();
                    cortina_aba_para_valor(pos_original);
                }
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

    printSensores();
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



    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(analogRead(SEN_CORTINA_POTENCIOMETRO_ABAS));
    lcd.print("=");
    lcd.print(le_potenciometro_aba());
    lcd.print((char) 223);
    lcd.setCursor(0, 1);
    lcd.print(analogRead(SEN_CORTINA_POTENCIOMETRO_ABAS_CONFIG_MIN));
    lcd.print("~");
    lcd.print(analogRead(SEN_CORTINA_POTENCIOMETRO_ABAS_CONFIG_MAX));
    lcd.setCursor(12, 0);
    lcd.print(sensoresBlackout());
    //    lcd.print("c");
    //    lcd.print(lh(digitalRead(SEN_CORTINA_INICIO)));
    //    lcd.print(lh(digitalRead(SEN_CORTINA_MEIO)));
    //    lcd.print(lh(digitalRead(SEN_CORTINA_FIM)));
    lcd.setCursor(12, 1);
    lcd.print(sensoresCortina());
    //    lcd.print("b");
    //    lcd.print(lh(digitalRead(SEN_BLACKOUT_INICIO)));
    //    lcd.print(lh(digitalRead(SEN_BLACKOUT_MEIO)));
    //    lcd.print(lh(digitalRead(SEN_BLACKOUT_FIM)));





    //    Serial.println();
    //    Serial.println("---");
    Serial.println("----------------------------------------");

    Serial.print(" Valor lido do controle remoto: ");
    Serial.println(IrReceiver.decodedIRData.command);
    //    Serial.println("-");
    Serial.print(" ABA leitura...: ");
    Serial.print(analogRead(SEN_CORTINA_POTENCIOMETRO_ABAS));
    Serial.print(" (");
    Serial.print(le_potenciometro_aba());
    Serial.println(")");

    Serial.print(" ABA config....: ");
    Serial.print(analogRead(SEN_CORTINA_POTENCIOMETRO_ABAS_CONFIG_MIN));
    Serial.print(" ~ ");
    Serial.println(analogRead(SEN_CORTINA_POTENCIOMETRO_ABAS_CONFIG_MAX));

    //    Serial.println("-");
    Serial.println(" SENSORES......: " + sensores());
    //    Serial.print(" SEN_CORTINA...: ");
    //    Serial.print(sensoresCortina());
    //    //    Serial.print(lh(digitalRead(SEN_CORTINA_INICIO)));
    //    //    //    Serial.print(" / ");
    //    //    //    Serial.print(" SEN_CORTINA_MEIO..: ");
    //    //    Serial.print(lh(digitalRead(SEN_CORTINA_MEIO)));
    //    //    //    Serial.print(" / ");
    //    //    //    Serial.print(" SEN_CORTINA_FIM...: ");
    //    //    Serial.print(lh(digitalRead(SEN_CORTINA_FIM)));
    //    Serial.println("");
    //    Serial.print(" SEN_BLACKOUT..: ");
    //    Serial.print(sensoresBlackout());
    //    //    Serial.print(lh(digitalRead(SEN_BLACKOUT_INICIO)));
    //    //    //    Serial.print(" / ");
    //    //    //    Serial.print(" SEN_BLACKOUT_MEIO..: ");
    //    //    Serial.print(lh(digitalRead(SEN_BLACKOUT_MEIO)));
    //    //    //    Serial.print(" / ");
    //    //    //    Serial.print(" SEN_BLACKOUT_FIM...: ");
    //    //    Serial.print(lh(digitalRead(SEN_BLACKOUT_FIM)));
    Serial.println("");

    Serial.println("----------------------------------------");
    //    Serial.println("---");
    Serial.println();
}

String sensores() {
    String temp = "";
    temp.concat(sensoresBlackout());
    temp.concat(" ");
    temp.concat(sensoresCortina());
    temp.concat(" a");
    temp.concat(le_potenciometro_aba());
    temp.concat((char) 223);
    return temp;
}

String sensoresBlackout() {
    String temp = "b";
    temp.concat(lh(digitalRead(SEN_BLACKOUT_INICIO)));
    temp.concat(lh(digitalRead(SEN_BLACKOUT_MEIO)));
    temp.concat(lh(digitalRead(SEN_BLACKOUT_FIM)));
    return temp;

    //    return "b" . lh(digitalRead(SEN_BLACKOUT_INICIO)) . lh(digitalRead(SEN_BLACKOUT_MEIO)) . lh(digitalRead(SEN_BLACKOUT_FIM));
}

String sensoresCortina() {
    String temp = "c";
    temp.concat(lh(digitalRead(SEN_CORTINA_INICIO)));
    temp.concat(lh(digitalRead(SEN_CORTINA_MEIO)));
    temp.concat(lh(digitalRead(SEN_CORTINA_FIM)));
    return temp;
    //    return "c" . lh(digitalRead(SEN_CORTINA_INICIO)) . lh(digitalRead(SEN_CORTINA_MEIO)) . lh(digitalRead(SEN_CORTINA_FIM));
}

String lh(int a) {
    return (a) ? "H" : "L";
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
    int pot, pot_original;
    pot = pot_original = le_potenciometro_aba();

    Serial.print(" Movimentacao da aba: ");
    Serial.print(pot);
    Serial.print(" >> ");
    Serial.print(valor);

    //--- Situacoes que a movimentacao nao pode acontecer

    // So pode girar com cortina fechada para esse valor (0 ou 180)
    if ((valor == 0 || valor == 180) && digitalRead(SEN_CORTINA_FIM) != LOW) {
        Serial.println(" CANCELADO O COMANDO (A)");
        return;
    }

    // So pode girar com cortina semiaberta/fechada para esse valor (45 ou 135)
    if ((valor == 45 || valor == 135) && digitalRead(SEN_CORTINA_FIM) != LOW && digitalRead(SEN_CORTINA_MEIO) != LOW) {
        Serial.println(" CANCELADO O COMANDO (B)");
        return;
    }

    // Se já estiver na posicao solicitada (dentro da faixa de seguranca), retorna sem fazer nada
    if (pot >= (valor - FAIXA_SEGURANCA_VALOR_ANALOGIC_VERIFICACAO) && pot <= (valor + FAIXA_SEGURANCA_VALOR_ANALOGIC_VERIFICACAO)) {
        Serial.println(" CANCELADO O COMANDO (C)");
        return;
    }

    Serial.println(" CONFIRMADO O COMANDO ");

    //---

    // Essa condicao impede que ambos os lacos sejam executados
    if (pot > valor) {

        // direcao A do servo  
        while (pot > valor) {
            String msg = "ABA: goA -> ";
            msg.concat(valor);
            msgDisplay(msg);

            servoAba.goA();
            delay(TEMPO_LOOP_MILLIS);
            pot = le_potenciometro_aba();
        }
    } else {

        // direcao B do servo
        while (pot < valor) {
            String msg = "ABA: goB -> ";
            msg.concat(valor);
            msgDisplay(msg);

            servoAba.goB();
            delay(TEMPO_LOOP_MILLIS);
            pot = le_potenciometro_aba();
        }
    }

    // Finaliza a acao do servo independente da direcao que tenha sido tomada
    servoAba.stop();

    return pot_original;
}

//---

bool if_cortina_aberta() {
    return (digitalRead(SEN_CORTINA_INICIO) == LOW);
}

bool if_cortina_fechada() {
    return (digitalRead(SEN_CORTINA_FIM) == LOW);
}

bool if_cortina_semi_aberta() {
    return (digitalRead(SEN_CORTINA_MEIO) == LOW);
}

void cortina_abrir() {
    // direcao A do servo
    while (digitalRead(SEN_CORTINA_INICIO) != LOW) {
        msgDisplay("Crt abrindo: goA");

        servoComprimento.goA();
        delay(TEMPO_LOOP_MILLIS);
    }
    servoComprimento.stop();
}

void cortina_fechar() {
    // direcao B do servo
    while (digitalRead(SEN_CORTINA_FIM) != LOW) {
        msgDisplay("Crt fechand: goB");

        servoComprimento.goB();
        delay(TEMPO_LOOP_MILLIS);
    }
    servoComprimento.stop();
}

void cortina_semi_abrir() {
    if (digitalRead(SEN_CORTINA_INICIO) == LOW) {
        while (digitalRead(SEN_CORTINA_MEIO) != LOW) {
            msgDisplay("Crt semAbri: goB");

            servoComprimento.goB();
            delay(TEMPO_LOOP_MILLIS);
        }
        servoComprimento.stop();
    } else if (digitalRead(SEN_CORTINA_FIM) == LOW) {
        while (digitalRead(SEN_CORTINA_MEIO) != LOW) {
            msgDisplay("Crt semAbri: goA");

            servoComprimento.goA();
            delay(TEMPO_LOOP_MILLIS);
        }
        servoComprimento.stop();
    } else {
        // neste caso a cortina esta parada no limbo. Abre tudo pra depois ir pro meio
        // direcao A do servo (abre ate o inicio ou meio, o que acontecer primeiro)
        while (digitalRead(SEN_CORTINA_INICIO) != LOW && digitalRead(SEN_CORTINA_MEIO) != LOW) {
            msgDisplay("Crt semAbri: goA");

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
        msgDisplay("Blk abrindo: goB");

        servoBlackout.goB();
        delay(TEMPO_LOOP_MILLIS);
    }
    servoBlackout.stop();
}

void blackout_fechar() {
    while (digitalRead(SEN_BLACKOUT_FIM) != LOW) {
        msgDisplay("Blk fechand: goB");

        servoBlackout.goA();
        delay(TEMPO_LOOP_MILLIS);
    }
    servoBlackout.stop();
}

void blackout_semi_abrir() {
    if (digitalRead(SEN_BLACKOUT_INICIO) == LOW) {
        while (digitalRead(SEN_BLACKOUT_MEIO) != LOW) {
            msgDisplay("Blk semAbri: goA");

            servoBlackout.goA();
            delay(TEMPO_LOOP_MILLIS);
        }
        servoBlackout.stop();
    } else if (digitalRead(SEN_BLACKOUT_FIM) == LOW) {
        while (digitalRead(SEN_BLACKOUT_MEIO) != LOW) {
            msgDisplay("Blk semAbri: goB");

            servoBlackout.goB();
            delay(TEMPO_LOOP_MILLIS);
        }
        servoBlackout.stop();
    } else {
        // neste caso a cortina esta parada no limbo. Abre tudo pra depois ir pro meio
        // (abre ate o inicio ou meio, o que acontecer primeiro)
        while (digitalRead(SEN_BLACKOUT_INICIO) != LOW && digitalRead(SEN_BLACKOUT_MEIO) != LOW) {
            msgDisplay("Blk semAbri: goB");

            servoBlackout.goB();
            delay(TEMPO_LOOP_MILLIS);
        }
        servoBlackout.stop();

        // Caso tenha precisado ir ate o inicio, agora vai pra metade
        if (digitalRead(SEN_BLACKOUT_INICIO) == LOW)
            blackout_semi_abrir();
    }
}

//---

String getValueStringSerial(String data, char separator, int index) {
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void msgDisplay(String linha1) {
    msgDisplay(linha1, sensores());
}

void msgDisplay(String linha1, String linha2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(linha1);
    lcd.setCursor(0, 1);
    lcd.print(linha2);
}

void realizaAcaoManual(String entradaViaSerial) {

    char motor = getValueStringSerial(entradaViaSerial, ' ', 0).charAt(0);
    char direcao = getValueStringSerial(entradaViaSerial, ' ', 1).charAt(0);
    int milis = getValueStringSerial(entradaViaSerial, ' ', 2).toInt();

    // Verificacao de entrada
    if (motor != 'c' && motor != 'g' && motor != 'b') {
        Serial.println("Motor invalido - Comando valido: [c/g/b] [+/-] [int milis]");
        return;
    }
    if (direcao != '+' && direcao != '-') {
        Serial.println("Direcao invalido - Comando valido: [c/g/b] [+/-] [int milis > 0]");
        return;
    }
    if (milis <= 0) {
        milis = 1000; //tempo padrao com parametro vazio
        //        Serial.println("Tempo invalido - Comando valido: [c/g/b] [+/-] [int milis > 0]");
        //        return;
    }

    if (motor == 'c') {
        if (direcao == '+') {
            servoComprimento.goA();
            Serial.print("servoComprimento.goA() ");
        } else {
            servoComprimento.goB();
            Serial.print("servoComprimento.goB() ");
        }
        delay(milis);
        servoComprimento.stop();

    } else if (motor == 'g') {
        if (direcao == '+') {
            servoAba.goA();
            Serial.print("servoAba.goA() ");
        } else {
            servoAba.goB();
            Serial.print("servoAba.goB ");
        }
        delay(milis);
        servoAba.stop();

    } else if (motor == 'b') {
        if (direcao == '+') {
            servoBlackout.goA();
            Serial.print("servoBlackout.goA() ");
        } else {
            servoBlackout.goB();
            Serial.print("servoBlackout.goB() ");
        }
        delay(milis);
        servoBlackout.stop();
    }

    Serial.print(milis);
    Serial.println(" milisegundos.");
    Serial.println();

}