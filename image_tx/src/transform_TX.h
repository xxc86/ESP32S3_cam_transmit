#ifndef _TRANSFROM_TX_H_
#define _TRANSFROM_TX_H_

#define STA_SSID "ESP32_AP_DEMO"
#define STA_PASS "12345678"

#define AP_IP   "192.168.4.1"
#define UDP_PORT 5000
#define LOCAL_PORT 4000

void udp_init();
void udp_send();

#endif 