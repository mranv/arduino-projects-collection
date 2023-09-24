#include <LiquidCrystal.h> //Libraries
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Arduino pins to lcd

#define sensor_pin A0 
int Force_value;

#define bt_silent  A5
int silent=0;

#define G_led 8 
#define R_led 9 

#define buzzer 13

void setup(){// put your setup code here, to run once 

pinMode(sensor_pin, INPUT);

pinMode(bt_silent, INPUT_PULLUP);

pinMode(R_led,OUTPUT); // declare Red LED as output
pinMode(G_led,OUTPUT); // declare Green LED as output
pinMode(buzzer,OUTPUT); // declare Buzzer as output 

lcd.begin(16, 2); // Configura lcd numero columnas y filas
lcd.clear();
lcd.setCursor (0,0);
lcd.print("   Welcome To   ");
lcd.setCursor (0,1);
lcd.print(" Force Detector "); 
delay(2000);
lcd.clear();
}

void loop(){

Force_value = analogRead(sensor_pin);

lcd.setCursor(0,0);
lcd.print("Force Sensor"); 
lcd.setCursor(0,1);
lcd.print("Value: ");
lcd.print(Force_value);
lcd.print("  ");

if(digitalRead (bt_silent) == 0){ 
silent = 0; 
delay(100);
} 

//Enter Force Value Range
if((Force_value < 550) || (Force_value > 650)){silent=1;} 

if(silent==1){
digitalWrite(buzzer, HIGH); 
digitalWrite(G_led, LOW); // Turn LED off.   
digitalWrite(R_led, HIGH);  // Turn LED on.
delay(300);
}else{
digitalWrite(G_led, HIGH); // Turn LED on.  
digitalWrite(R_led, LOW);  // Turn LED off.
}
 
digitalWrite(buzzer, LOW);
delay(100);
}
