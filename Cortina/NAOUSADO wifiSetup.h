#ifndef WIFISETUP_H
#define WIFISETUP_H

#include "defines.h"
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"

void wifiSetup() {

    // Define o como STA
    WiFi.mode(WIFI_STA);

    // Conecta
    Serial.printf("[WIFI] Conectado ao %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // Espera
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();

    // Conectado
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

#endif

