#include "defines.h"

void ledPisca(int vezes) {
    //Serial.print("Led piscando (");
    //Serial.print(vezes);
    //Serial.println(")");
    bool inicial = (digitalRead(LED) == HIGH);
    for (int i = 0; i < vezes; i++) {
        digitalWrite(LED, 1);
        delay(50);
        digitalWrite(LED, 0);
        delay(50);
    }
    digitalWrite(LED, inicial);
}