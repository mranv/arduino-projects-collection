#include <EEPROM.h>
#include <LiquidCrystal.h> //Libraries
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Arduino pins to lcd

#define sensor_pin  A0
#define reset_pin   A5

#define buzzer 13

int d5=1, d4=2, d3=3, d2=4, d1=5;
int flag=0, timer=0;

// the 8 arrays that form each segment of the custom numbers
byte bar1[8]={B11100,B11110,B11110,B11110,B11110,B11110,B11110,B11100};
byte bar2[8]={B00111,B01111,B01111,B01111,B01111,B01111,B01111,B00111};
byte bar3[8]={B11111,B11111,B00000,B00000,B00000,B00000,B11111,B11111};
byte bar4[8]={B11110,B11100,B00000,B00000,B00000,B00000,B11000,B11100};
byte bar5[8]={B01111,B00111,B00000,B00000,B00000,B00000,B00011,B00111};
byte bar6[8]={B00000,B00000,B00000,B00000,B00000,B00000,B11111,B11111};
byte bar7[8]={B00000,B00000,B00000,B00000,B00000,B00000,B00111,B01111};
byte bar8[8]={B11111,B11111,B00000,B00000,B00000,B00000,B00000,B00000};

void setup(){ // put your setup code here, to run once
  
pinMode(sensor_pin, INPUT_PULLUP);
pinMode(reset_pin,  INPUT_PULLUP);

pinMode(buzzer, OUTPUT);

lcd.createChar(1,bar1);
lcd.createChar(2,bar2);
lcd.createChar(3,bar3);
lcd.createChar(4,bar4);
lcd.createChar(5,bar5);
lcd.createChar(6,bar6);
lcd.createChar(7,bar7);
lcd.createChar(8,bar8);
  
lcd.begin(16, 2); // Configura lcd numero columnas y filas
lcd.clear();
lcd.setCursor (0,0);
lcd.print("   Welcome To   ");
lcd.setCursor (0,1);
lcd.print(" Object Counter ");
delay(2000);
lcd.clear();


if(EEPROM.read(0)==0){
}else{
WriteEeprom();
EEPROM.write(0,0); 
}

ReadEeprom();
}

void loop(){  

if(digitalRead (sensor_pin) == 1){ 
if(flag==0){flag=1;
d1=d1+1;
if(d1>9){d1=0; d2=d2+1;}  
if(d2>9){d2=0; d3=d3+1;} 
if(d3>9){d3=0; d4=d4+1;} 
if(d4>9){d4=0; d5=d5+1;} 
if(d5>9){d5=0;}
WriteEeprom(); 
 }
}else{flag=0;}


if(digitalRead (reset_pin) == 0){ 
digitalWrite(buzzer, HIGH);
if(timer<200){timer=timer+1;}
if(timer==200){
d1=0, d2=0, d3=0, d4=0, d5=0;  
WriteEeprom();
 }   
}else{digitalWrite(buzzer, LOW); timer=0;}

lcd.setCursor(0,0);
lcd.print(flag);

printNumber(d5, 1); 
printNumber(d4, 4); 
printNumber(d3, 7); 
printNumber(d2, 10);
printNumber(d1, 13);

delay(10);
}

void printNumber(int value, int col) {
  if (value == 0) {
    custom0(col);
  } if (value == 1) {
    custom1(col);
  } if (value == 2) {
    custom2(col);
  } if (value == 3) {
    custom3(col);
  } if (value == 4) {
    custom4(col);
  } if (value == 5) {
    custom5(col);
  } if (value == 6) {
    custom6(col);
  } if (value == 7) {
    custom7(col);
  } if (value == 8) {
    custom8(col);
  } if (value == 9) {
    custom9(col);
  }      
}  


void custom0(int col)
{ // uses segments to build the number 0
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(8); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom1(int col)
{
  lcd.setCursor(col,0);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
  lcd.setCursor(col,1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom2(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(6);
}

void custom3(int col)
{
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1); 
}

void custom4(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom5(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

void custom6(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom7(int col)
{
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom8(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom9(int col)
{
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(7);  
  lcd.write(6);  
  lcd.write(1);
}

void ReadEeprom(){
d1=EEPROM.read(1);
d2=EEPROM.read(2);
d3=EEPROM.read(3);
d4=EEPROM.read(4);
d5=EEPROM.read(5);
}

void WriteEeprom(){  
EEPROM.write(1, d1);
EEPROM.write(2, d2);
EEPROM.write(3, d3);
EEPROM.write(4, d4);
EEPROM.write(5, d5);
}
