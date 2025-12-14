#ifndef _TRANSFROM_RX_H_
#define _TRANSFROM_RX_H_

#include <WiFi.h>
#include <WiFiUdp.h>
#include <arduino.h>

#define AP_SSID "ESP32_AP_DEMO"
#define AP_PASS "12345678"

#define AP_IP   "192.168.4.1"
#define UDP_PORT 5000
#define LOCAL_PORT 4000

#define IMG_WIDTH   320
#define IMG_HEIGHT  240

void udp_init();
void udp_receive_image();
void on_image_received(uint8_t *jpeg_buf, size_t jpeg_len);
void udp_receive_and_display_rgb565();

#endif 