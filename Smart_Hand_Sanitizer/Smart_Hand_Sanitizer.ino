#include <Servo.h> //includes the servo library
Servo myservo1;

#define echopin 2 // echo pin
#define trigpin 3 // Trigger pin

long ultra_time;
long dis_cm;
int set_cm = 16;

int Stop =5;

void setup(){ // put your setup code here, to run once

Serial.begin(9600);// initialize serial communication at 9600 bits per second:

myservo1.attach(4);
myservo1.write(90);

pinMode (trigpin, OUTPUT); // declare ultrasonic sensor Trigger pin as Output
pinMode (echopin, INPUT);  // declare ultrasonic sensor Echo pin as input

delay(1000); // Waiting for a while
}

void loop(){ 
//*************************
ultra_read();
//*************************

Serial.print("Dis :");Serial.println(dis_cm); 

if(dis_cm<set_cm && Stop==0){ Stop = 5;
myservo1.write(20);
delay(500); 
myservo1.write(90);
delay(200); 
myservo1.write(20);
delay(1000); 
myservo1.write(90);
}

if(dis_cm>set_cm){
if(Stop>0){Stop = Stop-1;}
myservo1.write(90);
}

delay(100); 
}

//**********************ultra_read****************************
void ultra_read(){
digitalWrite(trigpin, LOW);
delayMicroseconds(2);
digitalWrite(trigpin, HIGH);
delayMicroseconds(10);
ultra_time = pulseIn (echopin, HIGH);
dis_cm =  ultra_time / 29 / 2; 
}
