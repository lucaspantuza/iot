void menuDJ()
{

    telaMenuLinha(" Selecione cor");

    while (digitalRead(BOTAO_SELECAO_ESQ) == HIGH && digitalRead(BOTAO_SELECAO_DIR) == HIGH)
    {
        if (digitalRead(BOTAO_AZUL) == HIGH)
        {
            tone(BUZZER_PIN, 392);
            digitalWrite(LED_AZUL, HIGH);
            delay(100);
            digitalWrite(LED_AZUL, LOW);
        }
        if (digitalRead(BOTAO_AMARELO) == HIGH)
        {
            tone(BUZZER_PIN, 440);
            digitalWrite(LED_AMARELO, HIGH);
            delay(100);
            digitalWrite(LED_AMARELO, LOW);
        }
        if (digitalRead(BOTAO_VERDE) == HIGH)
        {
            tone(BUZZER_PIN, 468);
            digitalWrite(LED_VERDE, HIGH);
            delay(100);
            digitalWrite(LED_VERDE, LOW);
        }
        if (digitalRead(BOTAO_VERMELHO) == HIGH)
        {
            tone(BUZZER_PIN, 663);
            digitalWrite(LED_VERMELHO, HIGH);
            delay(100);
            digitalWrite(LED_VERMELHO, LOW);
        }
        noTone(BUZZER_PIN);
        delay(100);

        // TODO notas 178, 781
    }
}