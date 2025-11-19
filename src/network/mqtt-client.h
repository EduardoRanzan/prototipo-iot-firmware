#pragma once
void mqtt_setup();
void mqtt_loop();
void mqtt_publish(const char *Topico, const String &msg);