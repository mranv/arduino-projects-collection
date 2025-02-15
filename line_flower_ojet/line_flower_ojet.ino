#define echopin 7 // echo pin
#define trigpin 6 // Trigger pin

const int danger= 30;

int S_A = 9;  //spade motor a
int M_A1 = 2; //motor a = +
int M_A2 = 3; //motor a = -
int M_B1 = 4; //motor b = -
int M_B2 = 5; //motor b = +
int S_B = 10;  //spade motor b

int L_S = A0; //sincer L
int S_S = A1; //sincer S
int R_S = A2; //sincer R

int in = A3; //sincer 

long duration;
int mood = 0;

int stop = 0;

void setup() 
{
pinMode (trigpin, OUTPUT);
pinMode (echopin, INPUT );
  
pinMode(M_B1, OUTPUT);
pinMode(M_B2, OUTPUT);
pinMode(M_A1, OUTPUT);
pinMode(M_A2, OUTPUT);
pinMode(S_B, OUTPUT);
pinMode(S_A, OUTPUT);
pinMode(L_S, INPUT);
pinMode(S_S, INPUT);
pinMode(R_S, INPUT);

pinMode(in, INPUT);

analogWrite(S_A, 250); 
analogWrite(S_B, 250); 
Serial.begin(9600);
delay(200);
}

void loop()
{

if((digitalRead(in) == LOW)&&(mood==0))
{
mood = 1;  
stop = 1;
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, HIGH); 
delay(1000);
}

if((digitalRead(in) == HIGH)&&(mood==1))
{
mood = 0;    
stop = 1;
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, HIGH); 
delay(1000);  
}

if(stop==1)
{
if ((digitalRead(L_S) == LOW)&&(digitalRead(S_S) == HIGH)&&(digitalRead(R_S) == LOW)) {
stop = 0;
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, LOW);  
line_flower();
}  
}


}

void line_flower(){

while(1)
 {  
int distanceFwd= ping(); 
Serial.println(distanceFwd);
if (distanceFwd>danger)
  { 
    
if ((digitalRead(L_S) == LOW)&&(digitalRead(S_S) == HIGH)&&(digitalRead(R_S) == LOW)) {
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW);  
}

if ((digitalRead(L_S) == HIGH)&&(digitalRead(S_S) == HIGH)&&(digitalRead(R_S) == LOW)) {
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, HIGH);  
}

if ((digitalRead(L_S) == HIGH)&&(digitalRead(S_S) == LOW)&&(digitalRead(R_S) == LOW)) {
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, HIGH);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, HIGH);  
}

if ((digitalRead(L_S) == LOW)&&(digitalRead(S_S) == HIGH)&&(digitalRead(R_S) == HIGH)) {
digitalWrite(M_A1, HIGH);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW);  
}

if ((digitalRead(L_S) == LOW)&&(digitalRead(S_S) == LOW)&&(digitalRead(R_S) == HIGH)) {
digitalWrite(M_A1, HIGH);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, HIGH);
digitalWrite(M_B2, LOW);  
}
  
if ((digitalRead(L_S) == HIGH)&&(digitalRead(S_S) == HIGH)&&(digitalRead(R_S) == HIGH)) {
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, LOW);  
break; 
}
}

if (distanceFwd<danger) {
digitalWrite(M_A1, LOW);
digitalWrite(M_A2, LOW);
digitalWrite(M_B1, LOW);
digitalWrite(M_B2, LOW);  
}
}
}


long ping(){
    digitalWrite(trigpin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin,HIGH);
    delayMicroseconds(10);
    duration=pulseIn (echopin,HIGH);
    return duration / 29 / 2; 
}
