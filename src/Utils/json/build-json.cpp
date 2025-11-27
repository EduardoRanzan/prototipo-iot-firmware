#include <ArduinoJson.h>
#include "../ntp/ntp-client.h"

String build_json(float valor) {
    StaticJsonDocument<128> doc;

    doc["value"] = valor;
    doc["ts"] = get_timestamp();

    String output;
    serializeJson(doc, output);
    return output;
}
