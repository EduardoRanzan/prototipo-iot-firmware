#include <ESP8266WiFi.h>
#include "../include/config.h"

unsigned long lastWifiAttempt = 0;

void wifi_setup() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Conectando ao WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi conectado!");
}


void wifi_loop() {
    if (WiFi.status() == WL_CONNECTED) return;

    unsigned long agora = millis();
    if (agora - lastWifiAttempt >= 5000) {
        Serial.println("WiFi desconectado, tentando reconectar...");
        WiFi.reconnect();
        lastWifiAttempt = agora;
    }
}


bool veirifica_wifi() {
    return WiFi.status() == WL_CONNECTED;
}
