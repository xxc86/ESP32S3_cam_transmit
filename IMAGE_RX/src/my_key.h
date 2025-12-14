#ifndef _MY_key_H__
#define _MY_key_H__

#include <Arduino.h>

#define boot_pin        0

typedef enum {
  cam=0,
  temp,
  max_state
}Show_state;

extern Show_state show_state;

void Key_Init();
int Key_Scan();
void update_state();

#endif
