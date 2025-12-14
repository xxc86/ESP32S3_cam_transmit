#include <WiFi.h>
#include <WiFiUdp.h>
#include <arduino.h>
#include "my_camera.h"
#include "transform_tx.h"


#define IMG_WIDTH    320
#define IMG_HEIGHT   240
#define PIX_SIZE     2               // RGB565
#define IMG_SIZE     (IMG_WIDTH * IMG_HEIGHT * PIX_SIZE)

#define PAYLOAD_SIZE 1024            // UDP 友好尺寸
#define MAGIC_WORD   0xAA55

typedef struct {
    uint16_t magic;        // 0xAA55
    uint16_t frame_id;     // 帧编号
    uint16_t packet_id;    // 当前包编号
    uint16_t packet_total; // 一帧总包数
} __attribute__((packed)) frame_hdr_t;
WiFiUDP udp;

void udp_init()
{
/* 1. 连接 AP */
  WiFi.mode(WIFI_STA);
  WiFi.begin(STA_SSID, STA_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to AP");
  Serial.print("STA IP: ");
  Serial.println(WiFi.localIP());

  /* 2. 启动 UDP */
  udp.begin(LOCAL_PORT);

} 

void udp_send()
{
    static uint16_t frame_id = 0;
    
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi disconnected, skip frame");
        delay(100);
        return;
    }

    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
        Serial.println("Camera capture failed");
        return;
    }

    uint8_t *img = fb->buf;
    size_t len = fb->len;   // IMG_SIZE

    uint16_t packet_total = (len + PAYLOAD_SIZE - 1) / PAYLOAD_SIZE;

    for (uint16_t pid = 0; pid < packet_total; pid++) {

        frame_hdr_t hdr;
        hdr.magic        = MAGIC_WORD;
        hdr.frame_id     = frame_id;
        hdr.packet_id    = pid;
        hdr.packet_total = packet_total;

        size_t payload_len = min( (size_t)PAYLOAD_SIZE,len - (size_t)pid * PAYLOAD_SIZE);

        udp.beginPacket(AP_IP, UDP_PORT);
        udp.write((uint8_t *)&hdr, sizeof(hdr));
        udp.write(img + pid * PAYLOAD_SIZE, payload_len);
        udp.endPacket();

        delayMicroseconds(200);
    }

    Serial.printf("Frame %d sent (%d packets)\n",
                  frame_id, packet_total);

    frame_id++;
    esp_camera_fb_return(fb);

}