#include <Arduino.h>
#include "transform_RX.h"
#include "my_display.h"
#include "my_key.h"
#include "my_dht11.h"

unsigned long previousMillis = 0; //毫秒时间记录
const long interval = 1000;       //时间间隔

void setup()
{
  Serial.begin(9600);
  Key_Init();
  udp_init();
  display_init();
  dht11_init();
}

void loop()
{
  update_state();
  if(cam==show_state)
  udp_receive_and_display_rgb565();
  else if(temp==show_state)
  {
    unsigned long currentMillis = millis();         //读取当前时间
    if (currentMillis - previousMillis >= interval) //如果和前次时间大于等于时间间隔
    {
      previousMillis = currentMillis; //更新时间记录
      dht11_show();
    }
  }
}
