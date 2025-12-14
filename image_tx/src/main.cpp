#include <Arduino.h>
#include "my_camera.h"
#include "transform_Tx.h"

void setup()
{
  Serial.begin(9600);


  psramFound();
  if(ESP_OK == my_camera_init())
  {
    Serial.println("camera_Init OK");
  }
  udp_init();
}

void loop()
{
  udp_send();
  // delay(1000);
}
