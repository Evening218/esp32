#include <WiFi.h>
#include <HTTPClient.h>  //瀏覽器
#include <ArduinoJson.h>
#include "U8g2lib.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
char ssid[] = "XperiaZN";                                                                              //請修改為您連線的網路名稱
char password[] = "amje1216";                                                                          //請修改為您連線的網路密碼
char url[] = "http://data.moenv.gov.tw/api/v2/aqx_p_02?api_key=e8dd42e6-9b8b-43f8-991e-b3dee723a52d";  //PM2.5的網址

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(4, OUTPUT);   //red
  pinMode(2, OUTPUT);   //green
  pinMode(15, OUTPUT);  //blue

  u8g2.begin();                                //初始化
  u8g2.enableUTF8Print();                      //啟用 UTF8字集
  u8g2.setFont(u8g2_font_unifont_t_chinese1);  //設定使用中文字形
  u8g2.setDrawColor(1);                        //設定顏色，我們是單色只有1
  u8g2.setFontPosTop();                        //座標從上開始
  u8g2.setFontDirection(0);
  Serial.print("開始連線到無線網路SSID:");
  Serial.println(ssid);
  //1.設定WiFi模式
  WiFi.mode(WIFI_STA);
  //2.啟動WiFi連線
  WiFi.begin(ssid, password);
  //3.檢查連線狀態
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("連線完成");
}

void loop() {
  //4.啟動網頁連線
  Serial.println("啟動網頁連線");
  HTTPClient http;            //宣告一個瀏覽器=打開一個瀏覽器
  http.begin(url);            //瀏覽url網址=在瀏覽器輸入網址
  int httpCode = http.GET();  //取得狀態碼
  Serial.print("httpCode=");
  Serial.println(httpCode);
  //5.檢查網頁連線是否正常 HTTP_CODE_OK=200
  if (httpCode == HTTP_CODE_OK) {
    //6.取得網頁內容
    String payload = http.getString();
    //Serial.print("payload=");
    //7.將資料顯示在螢幕上
    //Serial.println(payload);
    //JSON格式解析
    DynamicJsonDocument AQIJson(payload.length() * 2);  //宣告一個JSON文件，名稱為AQIJson
    deserializeJson(AQIJson, payload);                  //解析網頁內容payload為JSON格式，存放在AQIJson內
    for (int i = 0; i <= AQIJson["records"].size(); i++) {
      // 瀏覽records內的所有紀錄，直到找到site=="中壢"
      if (AQIJson["records"][i]["site"] == "中壢") {
        String AQI = AQIJson["records"][i]["pm25"];
        Serial.println("中壢PM2.5=" + AQI);


        u8g2.clear();                          //顯示前清除螢幕
        u8g2.setCursor(0, 10);                 //移動游標
        u8g2.print(String("中壢").c_str());    //寫入文字
        u8g2.setCursor(0, 30);                 //移動游標
        u8g2.print(String("PM2.5=").c_str());  //寫入文字
        u8g2.print(String(AQI).c_str());
        u8g2.sendBuffer();//送到螢幕顯示

        if (String(AQI).toInt() > 0) {
          analogWrite(4, 0);
          analogWrite(2, 255);
          analogWrite(15, 0);
        } else if (String(AQI).toInt() > 50) {
          analogWrite(4, 255);
          analogWrite(2, 255);
          analogWrite(15, 0);
        } else if (String(AQI).toInt() > 100) {
          analogWrite(4, 255);
          analogWrite(2, 126);
          analogWrite(15, 0);
        } else if (String(AQI).toInt() > 150) {
          analogWrite(4, 255);
          analogWrite(2, 0);
          analogWrite(15, 0);
        } else if (String(AQI).toInt() > 200) {
          analogWrite(4, 160);
          analogWrite(2, 32);
          analogWrite(15, 240);
        } else if (String(AQI).toInt() > 300) {
          analogWrite(4, 126);
          analogWrite(2, 0);
          analogWrite(15, 35);
        }
      }
    }
  }
  //8.關閉網頁連線
  http.end();  //關閉瀏覽器
  delay(10000);
}