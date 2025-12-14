#ifndef _MY_dht11_H__
#define _MY_dht11_H__

#include "DHT.h"

#define DHTPIN 1  // GPIO1 (DHT11 data pin)
#define DHTTYPE DHT11

extern DHT dht;

void dht11_init();
void dht11_show();

#endif