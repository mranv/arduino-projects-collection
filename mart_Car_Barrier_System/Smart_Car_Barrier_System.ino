#include <Servo.h> 
Servo myservo; 

#define G_led 2 // choose the pin for the Green Led
#define R_led 3 // choose the pin for the Red Led

#define echopin 4 // echo pin
#define trigpin 5 // Trigger pin

int cm; // Duration used to calculate distance
int degree=0, flag=0;
int set_time=2000;
long rememTime;

void setup(){ // put your setup code here, to run once 
Serial.begin(9600);// initialize serial communication at 9600 bits per second:

myservo.attach(8); // declare Servo Motor as output
myservo.write(degree);  

pinMode(R_led,OUTPUT); // declare Red LED as output
pinMode(G_led,OUTPUT); // declare Green LED as output

pinMode(trigpin, OUTPUT); // declare ultrasonic sensor Echo pin as input
pinMode(echopin, INPUT);  // declare ultrasonic sensor Trigger pin as Output 

delay(500);
}
 
void loop(){  
// Write a pulse to the HC-SR04 Trigger Pin
digitalWrite(trigpin, LOW);
delayMicroseconds(2);
digitalWrite(trigpin, HIGH);
delayMicroseconds(10);

// Measure the response from the HC-SR04 Echo Pin
long ultra_time = pulseIn (echopin, HIGH);
  // Determine distance from duration
  // Use 343 metres per second as speed of sound
cm =  ultra_time / 29 / 2; 

Serial.print("cm:");Serial.println(cm);

if(cm<10)rememTime = millis(); // set start time

if((millis()- rememTime) > set_time){ 
digitalWrite(G_led, LOW); // LED Turn Off.  
digitalWrite(R_led, HIGH); // LED Turn On
if(flag==1){ flag=0;
for(degree=90; degree>0; degree-=1){ 
myservo.write(degree);   
delay(3); 
  }    
 }
}else{
digitalWrite(G_led, HIGH); // LED Turn On   
digitalWrite(R_led, LOW); // LED Turn Off 
if(flag==0){ flag=1;
for(degree=0; degree<90; degree+=1){ 
myservo.write(degree);   
delay(3);     
  }    
 }
}

delay(100); 
}
