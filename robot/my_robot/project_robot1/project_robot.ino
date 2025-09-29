#include <SoftwareSerial.h>
#include "dht.h"

#define echopin  A0 // echo pin
#define trigpin A1 // Trigger pin

SoftwareSerial BT(2, 3);

#define dht_pin A5 // Pin sensor is connected to
dht DHT;

int motor2Pin1 = 6; // pin 6 on L293D IC
int motor2Pin2 = 7; // pin 7 on L293D IC
int motor2EnablePin = 10; // pin 10 on L293D IC

int motor1Pin1 = 4; // pin 4 on L293D IC
int motor1Pin2 = 5; // pin 5 on L293D IC
int motor1EnablePin = 9; // pin 9 on L293D IC


int state;
int Speed = 130; 

int temp;
int hum;

int timer = 0;

int distanceFwd;
long duration;

int chk = 0;
int set = 35;

void setup() {
    pinMode (trigpin, OUTPUT);
    pinMode (echopin, INPUT );
   
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(motor1EnablePin, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(motor2EnablePin, OUTPUT);
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
    BT.begin(9600); // Setting the baud rate of Software Serial Library  
    delay(500); 
}

void loop() {
    //if some date is sent, reads it and saves in state
    if(BT.available() > 0){     
      state = BT.read(); 
      Serial.println(state);
      if(state > 10){
         Speed = state;}      
}
           
   
   distanceFwd = data();  
         
   analogWrite(motor1EnablePin, Speed);
   analogWrite(motor2EnablePin, Speed);
   
   if((distanceFwd<set) && (chk==1)){chk = 2; Stop();}
    if(distanceFwd>set){chk = 0;}
    
   // if the state is '1' the DC motor will go forward
   if ((state == 1) && (chk==0)){chk = 1; forword();Serial.println("Go Forward!");}

   // if the state is '2' the motor will Reverse
   else if (state == 2){backword();Serial.println("Reverse!");}
    
   // if the state is '3' the motor will turn left
   else if (state == 3){turnLeft();Serial.println("Turn LEFT");}
    
   // if the state is '4' the motor will turn right
   else if (state == 4){turnRight();Serial.println("Turn RIGHT");}
    
   // if the state is '5' the motor will Stop
   else if (state == 5) {Stop();Serial.println("STOP!");}    

timer = timer+1;

if(distanceFwd>200){distanceFwd=200;} 

if(timer>400){
 DHT.read11(dht_pin);
 hum = DHT.humidity;
 temp = DHT.temperature;
     
 BT.print(temp);        //send distance to MIT App
 BT.print(";");
 BT.print(hum);         //send distance to MIT App
 BT.print(";");
 BT.print(distanceFwd); //send distance to MIT App 
 BT.println(";");    
 timer=0; 
}

delay(1); 
}

void forword(){
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
}

void backword(){
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH); 
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
}

void turnRight(){
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH); 
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
}

void turnLeft(){
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
}

void Stop(){
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
}

long data()
{
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  duration=pulseIn (echopin,HIGH);
  return duration / 29 / 2; 
}
