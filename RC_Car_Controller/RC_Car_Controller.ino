#include<MotorControl.h>

MotorControl motor1(2,3,0,'H');
MotorControl motor2(4,5,0,'H');

int value;
int x = 0;
char junk;
String inputString="";

void setup() {
Serial.begin(9600);

}

void loop() {
  if(Serial.available()){
    while(Serial.available())
    {
    char inChar = (char)Serial.read();
    inputString += inChar;
    }
    Serial.println(inputString);
    while(Serial.available()> 0)
    { junk = Serial.read(); }
    if(inputString == "a"){
      motor1.speed(220);
      motor2.speed(220);
      delay(200);
    }
     else if(inputString == "b"){
      motor1.speed(-220);
      motor2.speed(-220);
      delay(200);
    }
     else if(inputString == "c"){
      motor1.speed(220);
      motor2.speed(-220);
      delay(200);
    }
     else if(inputString == "d"){
      motor1.speed(-220);
      motor2.speed(220);
      delay(200);
    }
     else if(inputString == "s"){
      motor1.speed(0);
      motor2.speed(0);
    }
    inputString = "";
  }
  motor1.speed(0);
  motor2.speed(0);
}
