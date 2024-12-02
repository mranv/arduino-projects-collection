int xPin = A0;
int yPin = A1;
int keyPin = 8;

void setup() {
  pinMode(keyPin, INPUT_PULLUP);
  digitalWrite(keyPin, HIGH);
  Serial.begin(9600);
}

void loop() {
  Serial.print("X = ");
  Serial.print(analogRead(xPin));
  Serial.print(" | Y = ");
  Serial.print(analogRead(yPin));
  Serial.print(" | Z = ");
  Serial.println(digitalRead(keyPin));
}