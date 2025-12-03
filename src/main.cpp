#include <Arduino.h>
#include "server/wifi-manager.h"
#include "server/mqtt-client.h"
#include "sensors/sensors.h"
#include "../include/config.h"
#include "Utils/json/build-json.h"
#include "sd/sd-manager.h"


void setup() {
    Serial.begin(115200);
    delay(2000);

    wifi_setup();
    mqtt_setup();
    sensors_setup();
    sd_setup();
}


void loop() {
    wifi_loop();
    mqtt_loop();

    if (client.connected()) {
        sd_resend_all();
    }

    delay(CRON_TIME_COLECT);

    float temperatura = get_temperatura();
    float umidade = get_umidade();

    if (!isnan(temperatura)) {

        String json = build_json(temperatura);

        if (!mqtt_publish("sensores/temperatura", json)) {
            sd_save(json);
        }
    }

    if (!isnan(umidade)) {

        String json = build_json(umidade);

        if (!mqtt_publish("sensores/umidade", json)) {
            sd_save(json);
        }
    }
}

