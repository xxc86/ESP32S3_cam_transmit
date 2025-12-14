#ifndef _MY_DISPLAY_H__
#define _MY_DISPLAY_H__

#include "TFT_eSPI.h"


extern TFT_eSPI tft;

void display_init();
void display_camera(uint8_t* buf);
void display_result();

#endif