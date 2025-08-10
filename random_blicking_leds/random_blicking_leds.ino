int i;
void setup() {
  //start serial connection
  Serial.begin(9600);
  // set pins 0-7 to OUTPUT
  for(i=2; i<10; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  randomSeed(analogRead(0));
}

void loop() {
  /*
  for(i=2; i<10; i++) {
    digitalWrite(i, HIGH);
    delay(250);
    digitalWrite(i, LOW);
  }*/
  
  int randNumber = random(2, 10);
  digitalWrite(randNumber, HIGH);
  delay(500);
  digitalWrite(randNumber, LOW);
}