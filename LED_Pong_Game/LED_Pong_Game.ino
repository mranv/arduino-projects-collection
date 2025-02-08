#define clockPin A3  //Pin connected to 11 pin SH_CP of 74HC595
#define latchPin A4  //Pin connected to 12 pin ST_CP of 74HC595
#define dataPin  A5  //Pin connected to 14 pin DS of 74HC595

static const byte display[] = {
//edcbafg
B10000001, // 0
B11100111, // 1
B10010010, // 2
B11000010, // 3
B11100100, // 4
B11001000, // 5
B10001000, // 6
B11100011, // 7
B10000000, // 8
B11000000, // 9
B10100000, // A
B10001100, // b
B11111111  //Off
}; // BLANK

int LED[] = {13, 12, 11, 10, 9, 8, 7, 6, 5};
#define button1 3  // the number of the pushbutton pin
#define button2 4  // the number of the pushbutton pin

const byte PIN_CHAOS = A0; // Unconnected analog pin used to initialize RNG

unsigned long previousMillis = 0UL;
unsigned long interval = 500UL;
unsigned long storeInterval = 500UL;
int score1 = 0;
int score2 = 0;
int soundA = 800;
int soundB = 1000;
int bounce = 0;

int startDir[] = { -1, 1 };
int dir = 1;
int pos = 4;
int A = 0;
int B = 0;

void (*resetFunc)(void) = 0;

// the setup function runs once when you press reset or power the board
void setup() {
Serial.begin(9600);// initialize digital pin LED_BUILTIN as an output.

randomSeed(analogRead(PIN_CHAOS));
  
for(int i=0; i<=8; i=i+dir){
pinMode(LED[i], OUTPUT);
}

pinMode(button1, INPUT_PULLUP);
pinMode(button2, INPUT_PULLUP);

pinMode(latchPin, OUTPUT);
pinMode(clockPin, OUTPUT);
pinMode(dataPin, OUTPUT);

Show(11, 10); 
delay(1000);

dir = random(-1, 2);
if (dir == 0) dir = 1;

Show(score1, score2);
}

void loop(){ // the loop function runs over and over again forever
unsigned long currentMillis = millis();
int buttonState1 = digitalRead(button1);
int buttonState2 = digitalRead(button2);

Serial.print(buttonState1);
Serial.print(",");
Serial.print(buttonState2);
Serial.print(",");
Serial.print(dir);
Serial.print(",");
Serial.print(pos);
Serial.print(",");
Serial.print(score1);
Serial.print(",");
Serial.print(score2);
Serial.print(",");
Serial.println(interval);

  //change direction when pushed blue button
if(buttonState1==0 and pos>4 and A==1){
dir=-1;
A=0;

if(bounce==1){
interval = storeInterval;
bounce = 0;
}
if(interval>40)interval=interval-5;

//speed bounce
if(pos==7) {bounce=1;
storeInterval = interval;
interval = 60;
 }
}

//change direction when pushed red button
if(buttonState2==0 and pos<4 and B==1){
dir=1;
B=0;
if(bounce==1){
interval = storeInterval;
bounce = 0;
}
//reset speed after bounce

if(interval>40)interval=interval-5;
if(pos==1){bounce = 1;
storeInterval = interval;
interval = 60;
 }
}

//reset the push button
if(buttonState1==1)A=1;
if(buttonState2==1)B=1;

if(currentMillis-previousMillis>interval) {
 if(dir==1) tone(2, soundB, 50);
 if(dir==-1)tone(2, soundA, 50);
 buttonState1 = digitalRead(button1);
 buttonState2 = digitalRead(button2);

    /* The Arduino executes this code once every second
 	*  (interval = 1000 (ms) = 1 second).
 	*/

 // Don't forget to update the previousMillis value
 digitalWrite(LED[pos], LOW);
 if(pos>-1 and pos<9) pos=pos+dir;
  if(pos==0){  //score
   interval = storeInterval;
// flash the led for the goal
for(int i=0; i<=5; i++){
digitalWrite(LED[pos], HIGH);
delay(50);
tone(2, soundA, 50);
digitalWrite(LED[pos], LOW);
delay(50);
tone(2, soundA, 50);
 }

// show the score
for(int i=8; i>=8-score2; i--) {
digitalWrite(LED[i], HIGH);
delay(50);
}
delay(1000);  //wait one second

//clear the score
for(int i=8-score2; i<=8; i++){
digitalWrite(LED[i], LOW);
delay(50);
}

// show the led will come again
digitalWrite(LED[pos], HIGH);
//change direction and increase score by one
dir = 1;
score2 = score2+1;
Show(score1, score2);
delay(1000);
}

if(pos==8){
interval = storeInterval;  //reset the speed after a fast bounce
// flash the score for player 1
for(int i=0; i<=5; i++){
digitalWrite(LED[pos], HIGH);
delay(50);
tone(2, soundB, 50);
digitalWrite(LED[pos], LOW);
delay(50);
tone(2, soundB, 50);
}

//show the score
for(int i=0; i<=score1; i++){
digitalWrite(LED[i], HIGH);
delay(50);
}
delay(1000);  //wait a second

//clear the score
for(int i=score1; i>=0; i--){
digitalWrite(LED[i], LOW);
delay(50);
}
digitalWrite(LED[pos], HIGH);
dir = -1;
score1 = score1 + 1;
Show(score1, score2);
delay(1000);
}

//end of game reached 9 points
if(score1==9 or score2==9){
digitalWrite(LED[pos], LOW);
for(int i=0; i<=5; i++){
if(score1==9){
Show(score1, score2);
digitalWrite(LED[0], HIGH);
delay(500);
Show(12, 12);
digitalWrite(LED[0], LOW);
delay(200);
}

if(score2 == 9){
Show(score1, score2);
digitalWrite(LED[8], HIGH);
delay(500);
Show(12, 12);
digitalWrite(LED[8], LOW);
delay(200);
}

tone(2, 800, 100);
tone(2, 900, 100);
delay(200);
noTone(2);
}

resetFunc();
}
digitalWrite(LED[pos], HIGH);
previousMillis = currentMillis;
 }
}

void Show(int value1, int value2){
digitalWrite(latchPin, 0);
shiftOut(dataPin, clockPin,MSBFIRST, display[value1]);
shiftOut(dataPin, clockPin,MSBFIRST, display[value2]);
digitalWrite(latchPin, 1); 
  
}
