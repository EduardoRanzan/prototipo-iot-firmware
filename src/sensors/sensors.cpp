#include "sensors.h"
#include <DHT.h>

#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void sensors_setup() {
    dht.begin();
}

float get_temperatura() {
    float vlrTemperatura = dht.readTemperature();

    if (isnan(vlrTemperatura)) {
        Serial.println("[SENSORS] Erro ao ler temperatura!");
        return NAN;
    }

    Serial.printf("[SENSORS] Valor temperatura: %.2f\n", vlrTemperatura);
    return vlrTemperatura;
}

float get_umidade() {
    float vlrUmidade = dht.readHumidity();

    if (isnan(vlrUmidade)) {
        Serial.println("[SENSORS] Erro ao ler umidade!");
        return NAN;
    }

    Serial.printf("[SENSORS] Valor umidade: %.2f\n", vlrUmidade);
    return vlrUmidade;
}

