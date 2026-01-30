#include <LiquidCrystal.h> 
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); 

#define sensor_pin A0

int Temperature=0, Humidity=0;

// the 8 arrays that form each segment of the custom numbers
byte bar1[8]={B11100,B11110,B11110,B11110,B11110,B11110,B11110,B11100};
byte bar2[8]={B00111,B01111,B01111,B01111,B01111,B01111,B01111,B00111};
byte bar3[8]={B11111,B11111,B00000,B00000,B00000,B00000,B11111,B11111};
byte bar4[8]={B11110,B11100,B00000,B00000,B00000,B00000,B11000,B11100};
byte bar5[8]={B01111,B00111,B00000,B00000,B00000,B00000,B00011,B00111};
byte bar6[8]={B00000,B00000,B00000,B00000,B00000,B00000,B11111,B11111};
byte bar7[8]={B00000,B00000,B00000,B00000,B00000,B00000,B00111,B01111};
byte bar8[8]={B11111,B11111,B00000,B00000,B00000,B00000,B00000,B00000};

void setup() {

lcd.begin(16,2);  
lcd.setCursor(0,0);
lcd.print(" WELCOME To  My ");
lcd.setCursor(0,1);
lcd.print("YouTube  Channel");
delay(2000);
lcd.clear(); 

lcd.createChar(1,bar1);
lcd.createChar(2,bar2);
lcd.createChar(3,bar3);
lcd.createChar(4,bar4);
lcd.createChar(5,bar5);
lcd.createChar(6,bar6);
lcd.createChar(7,bar7);
lcd.createChar(8,bar8);
}

void loop(){
getData();      /*communicate with sensor & get data*/
//-----------------------------------------------------------
Temperature = getTemperature(); /*temp in Celcius*/
Humidity = getHumidity();    /*humidity in percentage*/

if(Humidity>99)Humidity=99;

printNumber((Temperature/10)%10, 0);
printNumber(Temperature%10, 3);

lcd.setCursor(6,0);
lcd.print("C");

printNumber((Humidity/10)%10, 9);
printNumber(Humidity%10, 12);
lcd.setCursor(15,0);
lcd.print("%");

delay(1000);
}

byte RH_high, RH_low, temp_high, temp_low, checksum;
unsigned int hum, temp;

float getTemperature(){
  return(float(temp)/10.0);
}
//========================================================================
float getHumidity(){
  return(float(hum)/10.0);
}

void getData(){
  /*start signal*/
  
    
  pinMode(sensor_pin, OUTPUT);             /*set data pin for o/p*/
  digitalWrite(sensor_pin, LOW);           /*first send low pulse*/
  delay(20);           /*for 1ms*/
  digitalWrite(sensor_pin, HIGH);          /*then send high pulse*/
  delayMicroseconds(40);             /*for 40us*/
  //-------------------------------------------------------------------
  /*response signal*/
  pinMode(sensor_pin, INPUT);              /*set data pin for i/p*/
  while(digitalRead(sensor_pin));          /*wait for DHT22 low pulse*/
  while(!digitalRead(sensor_pin));         /*wait for DHT22 high pulse*/
  while(digitalRead(sensor_pin));          /*wait for DHT22 low pulse*/
  //-------------------------------------------------------------------
  /*read sensor data*/
  RH_high = read_DHT22_byte();       /*read high byte humidity*/
  RH_low = read_DHT22_byte();        /*read low byte humidity*/
  temp_high = read_DHT22_byte();     /*read high byte temp*/
  temp_low = read_DHT22_byte();      /*read low byte temp*/
  checksum = read_DHT22_byte();      /*read checksum*/
  //------------------------------------------------------------------
  hum  = (RH_high << 8) | RH_low;    /*get 16-bit value of humidity*/
  temp = (temp_high << 8) | temp_low;/*get 16-bit value of temp*/
}

byte read_DHT22_byte(){
  byte dataByte;
  for(byte i=0; i<8; i++){
    while(!digitalRead(sensor_pin));       /*detect data bit (high pulse)*/
    delayMicroseconds(50);
    //--------------------------------------------------------------------
    if(digitalRead(sensor_pin)) dataByte = (dataByte<<1)|(0x01);
    else dataByte = (dataByte<<1);   /*store 1 or 0 in dataByte*/
    //--------------------------------------------------------------------
    while(digitalRead(sensor_pin));        /*wait for DHT22 low pulse*/
  }
  return dataByte;
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

void custom0(int col){ // uses segments to build the number 0
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(8); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom1(int col){
  lcd.setCursor(col,0);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
  lcd.setCursor(col,1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom2(int col){
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(6);
}

void custom3(int col){
  lcd.setCursor(col,0);
  lcd.write(5);
  lcd.write(3);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1); 
}

void custom4(int col){
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom5(int col){
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(7);
  lcd.write(6);
  lcd.write(1);
}

void custom6(int col){
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(3);
  lcd.write(4);
  lcd.setCursor(col, 1);
  lcd.write(2);
  lcd.write(6);
  lcd.write(1);
}

void custom7(int col){
  lcd.setCursor(col,0);
  lcd.write(2);
  lcd.write(8);
  lcd.write(1);
  lcd.setCursor(col, 1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(1);
}

void custom8(int col){
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(2);  
  lcd.write(6);  
  lcd.write(1);
}

void custom9(int col){
  lcd.setCursor(col, 0); 
  lcd.write(2);  
  lcd.write(3); 
  lcd.write(1);
  lcd.setCursor(col, 1); 
  lcd.write(7);  
  lcd.write(6);  
  lcd.write(1);
}
