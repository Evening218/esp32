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
    digitalWrite(15, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(16, HIGH);
    delay(100);
    digitalWrite(16, LOW);
  }
  if(v==0){
    digitalWrite(2, HIGH);
    digitalWrite(15, LOW);
  }
  delay(500);
}
