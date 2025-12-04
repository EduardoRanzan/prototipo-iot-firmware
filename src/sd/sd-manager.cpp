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


void sd_save(const String &tipo, const String &json) {
    File f = SD.open(FILE_BUFFER, FILE_WRITE);
    if (!f) {
        Serial.println("[SD] ERRO ao abrir buffer!");
        return;
    }

    f.print(tipo);
    f.print(";");
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

        int sep = line.indexOf(';');
        if (sep == -1) {
            Serial.println("[SD] Linha inválida, ignorando...");
            continue;
        }

        String tipo = line.substring(0, sep);
        String json = line.substring(sep + 1);

        String topico;
        if (tipo == "temperatura")   topico = "sensores/temperatura";
        else if (tipo == "umidade")  topico = "sensores/umidade";
        else {
            Serial.println("[SD] Tipo desconhecido, ignorando...");
            continue;
        }

        if (mqtt_publish(topico.c_str(), json)) {
            Serial.println("[SD] Reenviado: " + json);
        } else {
            Serial.println("[SD] Falhou ao reenviar, mantendo buffer.");
            f.close();
            return; // para aqui para não perder dados
        }

        delay(1000);
    }

    f.close();
    SD.remove(FILE_BUFFER);
    Serial.println("[SD] Buffer limpo!");
}
