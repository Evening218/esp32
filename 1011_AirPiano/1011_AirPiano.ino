#include <ESP32Servo.h>
int Trig = 12;
int Echo = 14;
int buzzer = 17;
int music[]={0, 262, 294, 330, 349, 392, 440, 493, 523};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //測量距離
  digitalWrite(Trig, LOW);//關閉超音波
  delayMicroseconds(5);//暫停5微秒
  digitalWrite(Trig, HIGH);//發出超音波
  delayMicroseconds(10);//暫停10微秒
  digitalWrite(Trig, LOW);//關閉超音波
  float Echotime = pulseIn(Echo, HIGH);//音波傳回時間
  float CMDist = (Echotime/2)/29.4;//用傳回時間計算距離
  Serial.println(CMDist);
  delay(50);
  //發出警報
  if(CMDist < 10){
    tone(buzzer, music[1], 500);
  }
  else if(CMDist < 20){
    tone(buzzer, music[2], 500);
  }
  else if(CMDist < 30){
    tone(buzzer, music[3], 500);
  }
  else if(CMDist < 40){
    tone(buzzer, music[4], 500);
  }
  else if(CMDist < 50){
    tone(buzzer, music[5], 500);
  }
  else if(CMDist < 60){
    tone(buzzer, music[6], 500);
  }
  else if(CMDist < 70){
    tone(buzzer, music[7], 500);
  }
  else if(CMDist < 80){
    tone(buzzer, music[8], 500);
  }
  delay(500);
}
