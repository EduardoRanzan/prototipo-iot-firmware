#ifndef SD_MANAGER_H
#define SD_MANAGER_H

#include <Arduino.h>

bool sd_setup();
void sd_save(const String &json);
void sd_resend_all();
bool sd_has_data();

#endif
