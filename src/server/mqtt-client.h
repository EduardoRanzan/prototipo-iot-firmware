#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <PubSubClient.h>

extern PubSubClient client;   // <- AQUI É O PONTO CRÍTICO

void mqtt_setup();
void mqtt_loop();
bool mqtt_publish(const char *topico, const String &msg);

#endif
