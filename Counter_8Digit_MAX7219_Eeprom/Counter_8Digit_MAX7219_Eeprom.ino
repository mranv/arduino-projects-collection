#include <EEPROM.h>

#define bt_up     A0
#define bt_down   A1
#define bt_reset  A2

#define buzzer 13

#define MAX7219_Clock 2
#define MAX7219_Chip_Select  3
#define MAX7219_Data_IN 4

long d1=0, d2=0, d3=0, d4=0, d5=0, d6=0, d7=0, d8=0;

int flag1=0, flag2=0, timer=0;

void setup() { // put your setup code here, to run once 

pinMode(bt_up,    INPUT_PULLUP);
pinMode(bt_down,  INPUT_PULLUP);
pinMode(bt_reset, INPUT_PULLUP);

pinMode(buzzer, OUTPUT);

pinMode(MAX7219_Data_IN, OUTPUT);
pinMode(MAX7219_Chip_Select, OUTPUT);
pinMode(MAX7219_Clock, OUTPUT);
digitalWrite(MAX7219_Clock, HIGH);

delay(200);

//Setup of MAX7219 chip
shift(0x0f, 0x00); //display test register - test mode off
shift(0x0c, 0x01); //shutdown register - normal operation
shift(0x0b, 0x07); //scan limit register - display digits 0 thru 7
shift(0x0a, 0x0f); //intensity register - max brightness
shift(0x09, 0xff); //decode mode register - CodeB decode all digits

if(EEPROM.read(0)==0){
}else{WriteEeprom(); EEPROM.write(0,0);}
ReadEeprom();

}

void loop() {

if(digitalRead (bt_up) == 0){ 
if(flag1==0){ flag1=1;
d1=d1+1;
if(d1>9){d1=0; d2=d2+1;}  
if(d2>9){d2=0; d3=d3+1;} 
if(d3>9){d3=0; d4=d4+1;} 
if(d4>9){d4=0; d5=d5+1;} 
if(d5>9){d5=0; d6=d6+1;} 
if(d6>9){d6=0; d7=d7+1;} 
if(d7>9){d7=0; d8=d8+1;} 
if(d8>9){d8=0;} 
WriteEeprom(); 
 }
}else{flag1=0;}

if(digitalRead (bt_down) == 0){ 
if(flag2==0){ flag2=1;
d1=d1-1;
if(d1<0){d1=9; d2=d2-1;}  
if(d2<0){d2=9; d3=d3-1;} 
if(d3<0){d3=9; d4=d4-1;} 
if(d4<0){d4=9; d5=d5-1;} 
if(d5<0){d5=9; d6=d6-1;} 
if(d6<0){d6=9; d7=d7-1;} 
if(d7<0){d7=9; d8=d8-1;} 
if(d8<0){d8=9;}   
WriteEeprom(); 
 }  
}else{flag2=0;}

if(digitalRead (bt_reset) == 0){ 
digitalWrite(buzzer, HIGH);
if(timer<200){timer=timer+1;}
if(timer==200){
d1=0, d2=0, d3=0, d4=0, d5=0, d6=0, d7=0, d8=0;
WriteEeprom();
}   
}else{digitalWrite(buzzer, LOW); timer=0;}
  
shift(0x01, d1);  //digit 0 (rightmost digit) data
shift(0x02, d2);
shift(0x03, d3);
shift(0x04, d4);
shift(0x05, d5);
shift(0x06, d6);
shift(0x07, d7);
shift(0x08, d8); //digit 7 (leftmost digit) data
delay(10);
}

void ReadEeprom() {
d1=EEPROM.read(1);
d2=EEPROM.read(2);
d3=EEPROM.read(3);
d4=EEPROM.read(4);
d5=EEPROM.read(5);
d6=EEPROM.read(6);
d7=EEPROM.read(7);
d8=EEPROM.read(8); 
}

void WriteEeprom() {  
EEPROM.write(1, d1);
EEPROM.write(2, d2);
EEPROM.write(3, d3);
EEPROM.write(4, d4);
EEPROM.write(5, d5);
EEPROM.write(6, d6);
EEPROM.write(7, d7);
EEPROM.write(8, d8);
}

void shift(byte send_to_address, byte send_this_data){
  digitalWrite(MAX7219_Chip_Select, LOW);
  shiftOut(MAX7219_Data_IN, MAX7219_Clock, MSBFIRST, send_to_address);
  shiftOut(MAX7219_Data_IN, MAX7219_Clock, MSBFIRST, send_this_data);
  digitalWrite(MAX7219_Chip_Select, HIGH);
}
