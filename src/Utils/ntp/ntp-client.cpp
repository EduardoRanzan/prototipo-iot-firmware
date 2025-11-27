#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -10800, 60000); 

void time_setup() {
    timeClient.begin();
    timeClient.update();
}

unsigned long get_timestamp() {
    timeClient.update();
    return timeClient.getEpochTime() * 1000ULL;
}
