// digital pin 12 has a pushbutton attached to it
int pushButton = 12;
int LED = 3;
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input
  pinMode(pushButton, INPUT);
  // make LED's pin an output
  pinMode(LED, OUTPUT);
}

void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  if (buttonState == HIGH) {
    digitalWrite(LED, HIGH);
    Serial.print("Pushbutton is pressed, the value is: ");
    Serial.println(buttonState);
  }
  else {
    digitalWrite(LED, LOW);
  }
  delay(1);        // delay in between reads for stability
}