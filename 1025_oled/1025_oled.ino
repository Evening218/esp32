#include "Wire.h"//I2C協定
#include "U8g2lib.h" //請下載u8g2程式庫
#include <SimpleDHT.h>

//詳細說明：https://www.twblogs.net/a/5d0b252ebd9eee1ede0409b9
//OLED 螢幕解析度為128*64
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int pinDHT11 = 4;//(esp32不能接2和12腳位)
SimpleDHT11 dht11(pinDHT11);
int light = 36;

void setup()
{
  Serial.begin(115200);
  u8g2.begin();//初始化
  u8g2.enableUTF8Print();//啟用 UTF8字集
  u8g2.setFont(u8g2_font_unifont_t_chinese1);//設定使用中文字形
  u8g2.setDrawColor(1);//設定顏色，我們是單色只有1
  u8g2.setFontPosTop();//座標從上開始
  u8g2.setFontDirection(0);//0不旋轉、1->90、2->180、3->270
  pinMode(light, INPUT);
}
long i=0;
void loop()
{
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;//byte範圍0~255
  byte humidity = 0;
  light = analogRead(36);
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
  
  u8g2.clear();//顯示前清除螢幕
  u8g2.setCursor(0, 10);//移動游標
  u8g2.print(String("溫度：").c_str());//寫入文字
  u8g2.print(String(temperature).c_str());
  u8g2.print(String("c").c_str());

  u8g2.setCursor(0, 30);//移動游標
  u8g2.print(String("濕度：").c_str());//寫入文字
  u8g2.print(String(humidity).c_str());
  u8g2.print(String("%").c_str());

  u8g2.setCursor(0, 50);//移動游標
  u8g2.print(String("亮度：").c_str());//寫入文字
  u8g2.print(String((4095-int(light))*100/4095).c_str());
  u8g2.print(String("%").c_str());

  u8g2.sendBuffer();//送到螢幕顯示
  delay(1500);
}
