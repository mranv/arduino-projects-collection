#include <LiquidCrystal.h> 
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); 

#include <SoftwareSerial.h>
SoftwareSerial BT_Serial(8, 9); // RX, TX

int temp, hum;

byte Data[3]={'0','0','0'};

void setup() {
Serial.begin(9600);
BT_Serial.begin(9600);
  
lcd.begin(16,2);  
lcd.setCursor(0,0);
lcd.print(" WELCOME To  My ");
lcd.setCursor(0,1);
lcd.print("YouTube  Channel");
delay(2000);
lcd.clear(); 
}

void loop(){

if(BT_Serial.available()>2){
   Data[0]=BT_Serial.read();                 
if(Data[0]=='A'){                      
   Data[1]=BT_Serial.read();  
   Data[2]=BT_Serial.read();    
}
hum = Data[1];
temp = Data[2];
Serial.print(hum);  Serial.print(" \t ");
Serial.println(temp); 
} 
    
lcd.setCursor(0,0);
lcd.print("Humidity:");
lcd.print(hum);
lcd.print("%  ");

lcd.setCursor(0,1); 
lcd.print("Temperature:"); 
lcd.print(temp); 
lcd.print((char)223); //degree symbol
lcd.print("C  ");

delay(100);
}
