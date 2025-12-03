#include "sd-manager.h"
#include <SD.h>
#include <PubSubClient.h>

#define SD_CS D2
#define FILE_BUFFER "/buffer.txt"

extern bool mqtt_publish(const char *topic, const String &msg);
extern bool veirifica_wifi();

bool sd_setup() {
    Serial.println("[SD] Inicializando SD...");

    if (!SD.begin(SD_CS)) {
        Serial.println("[SD] Falha ao inicializar SD (SD.begin)");
        return false;
    }

    Serial.println("[SD] SD OK!");

    return true;
}


void sd_save(const String &json) {
    File f = SD.open(FILE_BUFFER, FILE_WRITE);
    if (!f) {
        Serial.println("[SD] ERRO ao abrir buffer!");
        return;
    }
    f.println(json);
    f.close();
    Serial.println("[SD] Salvo no buffer!");
}

bool sd_has_data() {
    return SD.exists(FILE_BUFFER) && SD.open(FILE_BUFFER).size() > 0;
}

void sd_resend_all() {
    if (!sd_has_data()) return;

    Serial.println("[SD] Reenviando dados armazenados...");

    File f = SD.open(FILE_BUFFER, FILE_READ);
    if (!f) {
        Serial.println("[SD] Erro ao abrir buffer!");
        return;
    }

    while (f.available()) {

        String line = f.readStringUntil('\n');
        line.trim();

        if (line.length() == 0) continue;

        if (mqtt_publish("sensores/recuperados", line)) {
            Serial.println("[SD] Reenviado: " + line);
        } else {
            Serial.println("[SD] Falhou ao reenviar, para aqui");
            f.close();
            return;
        }
        delay(1000);
    }

    f.close();
    SD.remove(FILE_BUFFER);
    Serial.println("[SD] Buffer limpo!");
}
