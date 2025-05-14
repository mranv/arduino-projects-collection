#include <LiquidCrystal.h>   // include Arduino LCD library
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
 
#define CH0  12
#define CH1  11
#define CH2  10
#define CH3  9
#define CH4  8

// variables
byte ch_number;
uint32_t res;
const uint32_t res_table[5] = {100, 1000, 10000, 100000, 2000000};
char _buffer[11];
 
void setup() { 
pinMode(CH0, OUTPUT);
pinMode(CH1, OUTPUT);
pinMode(CH2, OUTPUT);
pinMode(CH3, OUTPUT);
pinMode(CH4, OUTPUT);

lcd.begin(16, 2);     // set up the LCD's number of columns and rows
lcd.setCursor(0, 0);  // move cursor to column 0, row 0 [position (0, 0)]
lcd.print("   Welcome To  ");
lcd.setCursor(0, 1);  // move cursor to column 0, row 1 [position (0, 1)]
lcd.print("   Ohm  Meter   ");
delay(2000);
lcd.clear();
 
ch_number = 4;
ch_select(ch_number);
}
 
// main loop
void loop() {

uint16_t volt_image = analogRead(A0) + 1;
 
if(volt_image >= 550 && ch_number < 4) {
ch_number++;
ch_select(ch_number);
delay(50);
return;
}

if(volt_image <= 90 && ch_number > 0) {
ch_number--;
ch_select(ch_number);
delay(50);
return;
}
 
if(volt_image < 900) {
float value = (float)volt_image*res/(1023 - volt_image);

     if(value < 1000.0)   sprintf(_buffer, "%03u.%1uOhm ", (uint16_t)value, (uint16_t)(value*10)%10);
else if(value < 10000.0)  sprintf(_buffer, "%1u.%03ukOhm", (uint16_t)(value/1000), (uint16_t)value%1000);
else if(value < 100000.0) sprintf(_buffer, "%02u.%02ukOhm", (uint16_t)(value/1000), (uint16_t)(value/10)%100);
else if(value < 1000000.0)sprintf(_buffer, "%03u.%1ukOhm", (uint16_t)(value/1000), (uint16_t)(value/100)%10);
else                      sprintf(_buffer, "%1u.%03uMOhm", (uint16_t)(value/1000000), (uint16_t)(value/1000)%1000);
}else sprintf(_buffer, "Over Load ");

lcd.setCursor(0, 0);  // move cursor to column 0, row 0 [position (0, 1)]
lcd.print("   Ohm  Meter   ");
 
lcd.setCursor(0, 1);  // move cursor to position (0, 1)
lcd.print("Value: ");
lcd.print(_buffer);
lcd.print("   ");
 
delay(500);   // wait some time
}
 
void ch_select(byte n) {
  switch(n) {
    case 0:
      digitalWrite(CH0, LOW);
      digitalWrite(CH1, HIGH);
      digitalWrite(CH2, HIGH);
      digitalWrite(CH3, HIGH);
      digitalWrite(CH4, HIGH);
      break;
    case 1:
      digitalWrite(CH0, HIGH);
      digitalWrite(CH1, LOW);
      digitalWrite(CH2, HIGH);
      digitalWrite(CH3, HIGH);
      digitalWrite(CH4, HIGH);
      break;
    case 2:
      digitalWrite(CH0, HIGH);
      digitalWrite(CH1, HIGH);
      digitalWrite(CH2, LOW);
      digitalWrite(CH3, HIGH);
      digitalWrite(CH4, HIGH);
      break;
    case 3:
      digitalWrite(CH0, HIGH);
      digitalWrite(CH1, HIGH);
      digitalWrite(CH2, HIGH);
      digitalWrite(CH3, LOW);
      digitalWrite(CH4, HIGH);
      break;
    case 4:
      digitalWrite(CH0, HIGH);
      digitalWrite(CH1, HIGH);
      digitalWrite(CH2, HIGH);
      digitalWrite(CH3, HIGH);
      digitalWrite(CH4, LOW);
  }
  res = res_table[n];
}
 
// end of code.
