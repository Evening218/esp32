void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(17, INPUT);
  pinMode(16, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int v = digitalRead(17);
  Serial.println(v);
  if(v==1){
    digitalWrite(16, HIGH);
    delay(100);
    digitalWrite(16, LOW);
  }
  delay(500);
}
