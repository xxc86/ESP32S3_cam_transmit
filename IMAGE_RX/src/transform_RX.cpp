#include "transform_rx.h"
#include "my_display.h"

#define IMG_SIZE    (IMG_WIDTH * IMG_HEIGHT * 2)

typedef struct {
    uint16_t magic;        // 0xAA55
    uint16_t frame_id;     // 帧编号
    uint16_t packet_id;    // 当前包编号
    uint16_t packet_total; // 一帧总包数
} __attribute__((packed)) frame_hdr_t;

uint8_t  rgb_buf[IMG_SIZE];
bool     packet_ok[256];

#define PAYLOAD_SIZE 1024            // UDP 友好尺寸
#define MAGIC_WORD   0xAA55

uint16_t current_frame = 0xFFFF;
uint16_t expected_packets = 0;
uint16_t received_packets = 0;

WiFiUDP udp;

void udp_init()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASS);

  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP()); 

  /* 2. 启动 UDP 监听 */
  udp.begin(UDP_PORT);
  Serial.println("UDP Server started");
}

void udp_receive_and_display_rgb565()
{
    int packetSize = udp.parsePacket();
    if (packetSize <= 0) return;

    frame_hdr_t hdr;
    udp.read((uint8_t *)&hdr, sizeof(hdr));

    if (hdr.magic != MAGIC_WORD) return;
    if (hdr.packet_id >= 256) return;

    // ---------- 新帧 ----------
    if (hdr.frame_id != current_frame) {
        current_frame = hdr.frame_id;
        expected_packets = hdr.packet_total;
        received_packets = 0;
        memset(packet_ok, 0, sizeof(packet_ok));
    }

    // ---------- 读取 payload ----------
    size_t payload_len =
        packetSize - sizeof(frame_hdr_t);

    size_t offset = hdr.packet_id * PAYLOAD_SIZE;
    if (offset + payload_len > IMG_SIZE) return;

    udp.read(rgb_buf + offset, payload_len);

    if (!packet_ok[hdr.packet_id]) {
        packet_ok[hdr.packet_id] = true;
        received_packets++;
    }

    // ---------- 是否收齐 ----------
    if (received_packets == expected_packets) {

        tft.startWrite();
        tft.pushImage(0, 0,
                      IMG_WIDTH, IMG_HEIGHT,
                      (uint16_t *)rgb_buf);
        tft.endWrite();

        Serial.printf("Frame %d displayed\n", current_frame);
        current_frame = 0xFFFF; // 等下一帧
    }
}