#include <Arduino.h>
#include "network/wifi-manager.h"
#include "network/mqtt-client.h"
#include "sensors/sensors.h"


void setup() {
    Serial.begin(115200);
    wifi_setup();
    mqtt_setup();
}

void loop() {
    wifi_loop(); 
    mqtt_loop();

    if (veirifica_wifi()) {
        Serial.print("Wifi ok, inserindo teste");
        const int temperatura = get_temperatura();
        const int umidade = get_umidade();
    
        mqtt_publish("", String(temperatura));
        mqtt_publish("", String(umidade));
    } else {
        Serial.print("Wifi caiu");
        delay(5000);    
    }
}   
