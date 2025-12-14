#include "my_display.h"
#include "esp_camera.h"
#include "my_key.h"


TFT_eSPI tft = TFT_eSPI();

void display_init() {
  tft.init();
  tft.setRotation(1);
  tft.invertDisplay(1);
  tft.fillScreen(TFT_BLACK);
}

void display_camera(uint8_t* buf){
  tft.startWrite();
  tft.pushImage(0, 0, 320, 240, (uint16_t *)buf);
  tft.endWrite();
}
