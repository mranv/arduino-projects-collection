int GreenLED=10;
int YellowLED=11;
int RedLED=12;

void setup()
{
  pinMode(GreenLED, OUTPUT);
  pinMode(YellowLED, OUTPUT);
  pinMode(RedLED, OUTPUT);
  
  digitalWrite(GreenLED, LOW);
  digitalWrite(YellowLED, LOW);
  digitalWrite(RedLED, LOW);
  
  Serial.begin(9600);
}

void loop()
{
  // Yield mode
  digitalWrite(GreenLED, LOW);
  digitalWrite(YellowLED, HIGH);
  digitalWrite(RedLED, LOW);
  Serial.println("Light mode: Yield");
  delay(1000);
  
  // Go mode
  digitalWrite(GreenLED, HIGH);
  digitalWrite(YellowLED, LOW);
  digitalWrite(RedLED, LOW);
  Serial.println("Light mode: Go");
  delay(2000);
  
  // Stop mode
  digitalWrite(GreenLED, LOW);
  digitalWrite(YellowLED, LOW);
  digitalWrite(RedLED, HIGH);
  Serial.println("Light mode: Stop");
  delay(2000);
}