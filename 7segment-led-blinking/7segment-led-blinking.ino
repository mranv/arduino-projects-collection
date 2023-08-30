void setup() {
  for (int i = 2; i < 9; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
}

void loop() {
  for (int i = 2; i < 9; i++) {
    digitalWrite(i, LOW);
    delay(1000);
    digitalWrite(i, HIGH);
    delay(1000);
  }
}