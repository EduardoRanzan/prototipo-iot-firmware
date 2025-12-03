#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "../include/config.h"

unsigned long lastMqttAttempt = 0;
WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
    while (!client.connected()) {
        Serial.print("Conectando ao Broker... \n");
        if (client.connect("dispositivo_01")) {
            Serial.println("conectado!");
        } else {
            Serial.print("Falha na Conexão com o Broker");
            Serial.println(client.state());
            delay(2000);
        }
    }
}

void mqtt_setup() {
    client.setServer(MQTT_HOST, MQTT_PORT);
    Serial.println("[MQTT] configurado");
}


void mqtt_loop() {
    if (client.connected()) {
        client.loop();
        return;
    }

    unsigned long agora = millis();
    if (agora - lastMqttAttempt >= 5000) {
        Serial.println("[MQTT] Tentando reconectar ao MQTT... ");
        if (client.connect("dispositivo_01")) {
            Serial.println("[MQTT] conectado!");
        } else {
            Serial.print("[MQTT] falhou: ");
            Serial.println(client.state());
        }
        lastMqttAttempt = agora;
    }
}


bool mqtt_publish(const char *Topico, const String &msg) {
    if (!client.connected()) return false;

    bool ok = client.publish(Topico, msg.c_str());
    
    if (ok) {
        Serial.printf("[MQTT] Publicado: %s | %s\n", Topico, msg.c_str());
    } else {
        Serial.println("[MQTT] Falha ao publicar!");
    }

    return ok;
}



