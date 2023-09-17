#include <LiquidCrystal.h> //Libraries
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Arduino pins to lcd

#define sensor_pin A0 

#define G_led 8 
#define R_led 9 

#define buzzer 13

float adcValue=0, val=0, mgL=0;

void setup(){// put your setup code here, to run once 

pinMode(sensor_pin, INPUT);

pinMode(R_led,OUTPUT); // declare Red LED as output
pinMode(G_led,OUTPUT); // declare Green LED as output
pinMode(buzzer,OUTPUT); // declare Buzzer as output 

lcd.begin(16, 2); // Configura lcd numero columnas y filas
lcd.clear();
lcd.setCursor (0,0);
lcd.print("   Welcome To   ");
lcd.setCursor (0,1);
lcd.print("Alcohol Detector"); 
delay(2000);
lcd.clear();
}

void loop(){
  
adcValue=0;
for(int i=0;i<10;i++){
adcValue+= analogRead(sensor_pin);
delay(10);
}

val = (adcValue/10) * (5.0/1024.0);
mgL = 0.67 * val;

lcd.setCursor(0, 0);
lcd.print(" BAC: ");
lcd.print(mgL,3);
lcd.print("mg/L   ");

lcd.setCursor(0, 1);
if(mgL>0.8){
lcd.print("      Drunk     ");  

digitalWrite(buzzer, HIGH); 
digitalWrite(G_led, LOW); // Turn LED off.   
digitalWrite(R_led, HIGH);  // Turn LED on.
delay(300);
}else{
lcd.print("     Normal    ");
  
digitalWrite(G_led, HIGH); // Turn LED on.  
digitalWrite(R_led, LOW);  // Turn LED off.
}
 
digitalWrite(buzzer, LOW);
delay(100);
}
