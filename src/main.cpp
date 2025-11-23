#include <Arduino.h>
#include "server/wifi-manager.h"
#include "server/mqtt-client.h"
#include "sensors/sensors.h"
#include "../include/config.h"

void setup() {
    Serial.begin(115200);
    wifi_setup();
    mqtt_setup();
    sensors_setup();
}

void loop() {
    wifi_loop();
    mqtt_loop();

    delay(CRON_TIME_COLECT);

    float temperatura = get_temperatura();
    if (!isnan(temperatura)) {
        mqtt_publish("sensores/temperatura", String(temperatura));
    }

    float umidade = get_umidade();

    if (!isnan(umidade)) {
        mqtt_publish("sensores/umidade", String(umidade));
    }
}
