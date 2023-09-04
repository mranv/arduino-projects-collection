#define potentiometer  A0
int read_ADC, delay_time;

int total_leds = 17; // enter the number of LEDs you want to use here
int leds[] = {A1, A2, A3, A4, A5, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

void setup() {// put your setup code here, to run once 
Serial.begin(9600);// initialize serial communication at 9600 bits per second:

pinMode(potentiometer, INPUT);

for(int i=0; i<total_leds; i++) { 
pinMode(leds[i], OUTPUT); // declare LEDs as output
}

delay(500); // Waiting for a while
}

void loop() {
  
Serial.println("Effect 1");
for(int i=0; i<3; i++) effect_1();

Serial.println("Effect 2");
for(int i=0; i<3; i++) effect_2();

Serial.println("Effect 3");
for(int i=0; i<20; i++) effect_3();

Serial.println("Effect 4");
for(int i=0; i<3; i++) effect_4();

Serial.println("Effect 5");
for(int i=0; i<3; i++) effect_5();

Serial.println("Effect 6");
for(int i=0; i<3; i++) effect_6();

Serial.println("Effect 7");
for(int i=0; i<3; i++) effect_7();

Serial.println("Effect 8");
for(int i=0; i<3; i++) effect_8();

Serial.println("Effect 9");
for(int i=0; i<10; i++) effect_9();

Serial.println("Effect 10");
for(int i=0; i<10; i++) effect_10();

Serial.println("Effect 11");
for(int i=0; i<5; i++) effect_11();

Serial.println("Effect 12");
for(int i=0; i<5; i++) effect_12();
  
ledsOff();
get_delay();
}

//TURN ON ALL LEDs
void ledsOn() {
for(int i=0; i<total_leds; i++) {
digitalWrite(leds[i], HIGH);
 }
}

//TURN OFF ALL LEDs
void ledsOff() {
for(int i=0; i<total_leds; i++) {
digitalWrite(leds[i], LOW);
 }
}

//LEFT TO RIGH FILL UNFILL - RIGHT TO LEFT FILL UNFIL   
void effect_1() {
int i=0;
for(i=0; i<=total_leds; i++){
digitalWrite(leds[i], HIGH);
get_delay();
}

for(i=0; i<=total_leds; i++){
digitalWrite(leds[i], LOW);
get_delay();
}
  
for(i=total_leds; i>=0; i--){
digitalWrite(leds[i], HIGH);
get_delay();
}

for(i=total_leds; i>=0; i--){
digitalWrite(leds[i], LOW);
get_delay();
}
}

//SPRING
void effect_2() {
int i=0;
for(i=0; i<=total_leds-1; i++){
digitalWrite(leds[i],HIGH);
get_delay();
}
  
for(i=total_leds; i>=0; i--){
digitalWrite(leds[i],LOW);
get_delay();
}
  
for(i=total_leds; i>=0; i--){
digitalWrite(leds[i],HIGH);
get_delay();
}
  
for(i=0; i<=total_leds; i++){
digitalWrite(leds[i],LOW);
get_delay();
 }
}

//RUN ODD LEDs
void effect_3() {
for(int i=0; i<total_leds; i=i+2) {
digitalWrite(leds[i], HIGH);
digitalWrite(leds[i + 1], LOW);
}

get_delay();

for(int i=0; i<total_leds; i=i+2) {
digitalWrite(leds[i], LOW);
digitalWrite(leds[i + 1], HIGH);
}

get_delay();
}

//RUN EVEN ODD LEDs
void effect_4() {
for(int i=0; i<=total_leds; i++){
digitalWrite(leds[i], HIGH);
get_delay();
i=i+1;
}
  
for(int i=0; i<=total_leds; i++){
digitalWrite(leds[i], LOW);
get_delay();
}

for(int j=total_leds +1; j>=0; j--){
digitalWrite(leds[j], HIGH);
get_delay();
j=j-1;
}
  
for(int j=total_leds; j>=0; j--){
digitalWrite(leds[j], LOW);
get_delay();
 }
}


//FROM LEFT AND RIGHT TO CENTER - AND VICE VERSA
void effect_5() {
  int i=0;
for(i=0; i<=total_leds/2 ; i++){
digitalWrite(leds[i],HIGH);
digitalWrite(leds[total_leds-i],HIGH);
get_delay();
}

for(i=0; i<=total_leds/2 ; i++){
digitalWrite(leds[i],LOW);
digitalWrite(leds[total_leds-i],LOW);
get_delay();
}

get_delay();

for(i=0; i<=total_leds/2 ; i++){
digitalWrite(leds[i],HIGH);
digitalWrite(leds[total_leds-i],HIGH);
get_delay();
}
for(i=total_leds/2; i>=0 ; i--){
digitalWrite(leds[i],LOW);
digitalWrite(leds[total_leds-i],LOW);
get_delay();
 }
}

//NIGHT RIDER LEFT TO RIGHT (ONE LED)
void effect_6() {
for(int i=0; i<total_leds; i++) {
digitalWrite(leds[i], HIGH);
get_delay();
digitalWrite(leds[i], LOW);
 }
}

//NIGHT RIDER RIGHT TO LEFT (ONE LED)
void effect_7() {
for(int i=total_leds; i>0; i--){
digitalWrite(leds[i-1], HIGH);
get_delay();
digitalWrite(leds[i-1], LOW);
 }
}

//NIGHT RIDER BACK AND FORTH (ONE LED)
void effect_8() {
for(int i=0;i<=total_leds;i++){
digitalWrite(leds[i],HIGH);
get_delay();
digitalWrite(leds[i],LOW);
}
for(int i=total_leds-2;i>=0;i--){
digitalWrite(leds[i],HIGH);
get_delay();
digitalWrite(leds[i],LOW);
 }
}

//INSIDE TO CENTER
void effect_9() {
for(int i=0; i<total_leds/2; i++){
digitalWrite(leds[i], HIGH);
digitalWrite(leds[total_leds - 1 - i], HIGH);
get_delay();
digitalWrite(leds[i], LOW);
digitalWrite(leds[total_leds - 1 - i], LOW);
 }
}

//OUTSIDE FROM CENTER
void effect_10() {
for(int i=(total_leds/2)-1; i>=0; i--){
digitalWrite(leds[i], HIGH);
digitalWrite(leds[total_leds -1 -i], HIGH);
get_delay();
digitalWrite(leds[i], LOW);
digitalWrite(leds[total_leds -1 -i], LOW);
 }
}

//RUN 2 LEDs FROM LEFT TO RIGHT
void effect_11() {
for(int i=0; i < total_leds + 3; i++) {
if(i<=total_leds){digitalWrite(leds[i], HIGH);}
if(i>1){digitalWrite(leds[i - 2], LOW);}
get_delay();
 }
}

//RUN 2 LEDS BACK AND FORTH
void effect_12() {
for(int i=2; i<total_leds; i++) {

if(i==2){
digitalWrite(leds[0], HIGH);
//digitalWrite(leds[1], HIGH);
}

digitalWrite(leds[i], HIGH);
digitalWrite(leds[i - 2], LOW);
get_delay();
}

for(int i=total_leds-3; i>-1; i--) {
digitalWrite(leds[i], HIGH);
digitalWrite(leds[i + 2], LOW);
get_delay();
 }
}

void get_delay(){
read_ADC = analogRead(potentiometer);
delay_time = read_ADC/2.046; //max value ADC 1013/2.046 = 500
if(delay_time<10)delay_time=10;
delay(delay_time);
}
