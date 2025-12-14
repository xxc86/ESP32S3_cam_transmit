#include "my_dht11.h"
#include "my_display.h"

DHT dht(DHTPIN, DHTTYPE);

void dht11_init() {
    dht.begin();
}

void dht11_show()
{
    // 读取温度和湿度
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    
    // 检查读取是否成功
    if (isnan(humidity) || isnan(temperature)) {
        tft.fillScreen(TFT_BLACK);
        tft.setTextSize(2);
        tft.setTextColor(TFT_RED);
        tft.drawString("DHT11 Read Error!", 10, 100);
        return;
    }
    
    // 显示温湿度数据
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    
    // 显示温度
    tft.drawString("Temperature:", 10, 50);
    tft.setTextSize(3);
    tft.setTextColor(TFT_CYAN);
    tft.drawString(String(temperature, 1) + " C", 10, 90);
    
    // 显示湿度
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("Humidity:", 10, 150);
    tft.setTextSize(3);
    tft.setTextColor(TFT_GREEN);
    tft.drawString(String(humidity, 1) + " %", 10, 190);
}