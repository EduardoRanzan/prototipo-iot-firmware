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
    return timeClient.getEpochTime();
}
