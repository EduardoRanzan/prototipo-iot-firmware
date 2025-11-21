#include <Arduino.h>
#include "server/wifi-manager.h"
#include "server/mqtt-client.h"
#include "sensors/sensors.h"

void setup() {
    Serial.begin(115200);
    wifi_setup();
    mqtt_setup();
}

void loop() {
    wifi_loop();
    mqtt_loop();

    delay(5000);
    float temperatura = get_temperatura();
    float umidade = get_umidade();
    mqtt_publish("sensores/temperatura", String(temperatura));
    mqtt_publish("sensores/umidade", String(umidade));
}
