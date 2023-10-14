#define echo 8    //Echo pin
#define trigger 9 //Trigger pin

#define buzzer 7 // choose the pin for the Buzzer Alert

#define R_led 4 // choose the pin for the Red Led
#define Y_led 3 // choose the pin for the Yellow Led
#define G_led 2 // choose the pin for the Green Led

int distance_cm;
int flag=0;

void setup() { // put your setup code here, to run once 
Serial.begin(9600);

pinMode(echo, INPUT);// declare ultrasonic sensor Echo pin as input
pinMode(trigger, OUTPUT); // declare ultrasonic sensor Trigger pin as Output 

pinMode(buzzer,OUTPUT); // declare Buzzer as output

pinMode(R_led,OUTPUT); // declare Red LED as output
pinMode(Y_led,OUTPUT); // declare Yellow LED as output
pinMode(G_led,OUTPUT); // declare Green LED as output

delay(100); 
} 
 
 
void loop() { 

distance_cm = Ultrasonic_read();  

     if(distance_cm<4){ //Alert Situation
flag = !flag;
digitalWrite(R_led, HIGH);// LED Turn On   
digitalWrite(Y_led, LOW); // LED Turn Off 
digitalWrite(G_led, LOW); // LED Turn Off   
}

else if(distance_cm>=4 && distance_cm<12){ //Ok Parking
flag=0; 
digitalWrite(R_led, LOW); // LED Turn Off   
digitalWrite(Y_led, HIGH);// LED Turn On 
digitalWrite(G_led, LOW); // LED Turn Off 
}

else if(distance_cm>=12 && distance_cm<25){ //Go further now
flag=0; 
digitalWrite(R_led, LOW); // LED Turn Off   
digitalWrite(Y_led, LOW); // LED Turn Off 
digitalWrite(G_led, HIGH);// LED Turn On 
 }
else{ //if there is no vehicle
flag=0; 
digitalWrite(R_led, LOW); // LED Turn Off   
digitalWrite(Y_led, LOW); // LED Turn Off 
digitalWrite(G_led, LOW); // LED Turn Off 
}

digitalWrite(buzzer, flag);
Serial.print("cm: "); Serial.println(distance_cm);   
delay(150);
}

//Ultrasonic_read
int Ultrasonic_read(){
digitalWrite(trigger, LOW); 
delayMicroseconds(2); 
digitalWrite(trigger, HIGH); 
delayMicroseconds(10); 
long time = pulseIn(echo, HIGH); 
return distance_cm = time / 28.5 / 2;
}
