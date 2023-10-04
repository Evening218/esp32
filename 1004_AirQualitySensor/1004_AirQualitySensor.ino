void setup() {
  // put your setup code here, to run once:
  pinMode(36, INPUT);
  pinMode(15, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(0, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(36);
  Serial.println(value);
  if (value >= 2000) {
    digitalWrite(15, 255);
    digitalWrite(2, 0);
    digitalWrite(0, 255);
  } else if (value >= 1500) {
    digitalWrite(15, 255);
    digitalWrite(2, 0);
    digitalWrite(0, 0);
  } else if (value >= 1000) {
    digitalWrite(15, 255);
    digitalWrite(2, 255);
    digitalWrite(0, 0);
  } else {
    digitalWrite(15, 0);
    digitalWrite(2, 255);
    digitalWrite(0, 0);
  }
  delay(100);
}