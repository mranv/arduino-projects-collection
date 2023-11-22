void setup()
{
 Serial.begin(9600);
 pinMode(7,OUTPUT) ;
}

void loop()
{
  int c = analogRead(A0) ;
  Serial.println(c) ;
  if(c<500)
  {
    digitalWrite(7,LOW) ; 
  }
  else
  {
    digitalWrite(7,HIGH) ; 
  }
}
