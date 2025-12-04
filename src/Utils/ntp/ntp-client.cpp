#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000);

void time_setup() {
    timeClient.begin();
    while(!timeClient.update()) {
        timeClient.forceUpdate();
    }
}

unsigned long get_timestamp() {
    timeClient.update();
    Serial.printf("[NTP] time: %u\n", timeClient.getEpochTime());
    return timeClient.getEpochTime();
}
