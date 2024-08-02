#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int sensorPin = A0; // choose the input pin (for Fire sensor)  
int buzzer = 13; // choose the pin for the Buzzer
int G_led = 8; // choose the pin for the Green LED
int R_led = 9; // choose the pin for the Red Led

int read_value; // variable for reading the sensorpin status

void setup(){ 
pinMode(sensorPin, INPUT); // declare sensor as input

pinMode(buzzer,OUTPUT); // declare Buzzer as output 
pinMode(R_led,OUTPUT); // declare Red LED as output
pinMode(G_led,OUTPUT); // declare Green LED as output

lcd.begin(16, 2);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("   WELCOME To   ");
lcd.setCursor(0,1);
lcd.print("  Fire Detector ");
delay(2000);
lcd.clear();
}

void loop(){
read_value = digitalRead(sensorPin); // Digital input value

if(read_value==1){ // check if the Fire variable is High
lcd.setCursor(0, 0);
lcd.print("   Not  Flame   ");   
lcd.setCursor(0, 1);
lcd.print(".....Normal.....");   
digitalWrite(buzzer, LOW); // Turn LED off.  
digitalWrite(R_led, LOW);  // Turn LED off.
digitalWrite(G_led, HIGH); // Turn LED on.

}
else{ // check if the Fire variable is Low
lcd.setCursor(0, 0);
lcd.print("Fire is Detected");  
lcd.setCursor(0, 1);
lcd.print("Alert....!!!    ");
    
digitalWrite(buzzer, HIGH); // Turn LED on.  
digitalWrite(R_led, HIGH);  // Turn LED on.
digitalWrite(G_led, LOW);   // Turn LED off.
delay(1000);
}
delay(100);
}
