#include<LiquidCrystal.h> 
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define sensor_pin A0 
int read_ADC;
int ntu;
 
void setup(){// put your setup code here, to run once 
pinMode(sensor_pin, INPUT);

lcd.begin(16, 2); // Configura lcd numero columnas y filas
lcd.clear();
lcd.setCursor (0,0);
lcd.print("   Welcome To   ");
lcd.setCursor (0,1);
lcd.print("Turbidity Sensor"); 
delay(2000);
lcd.clear();
}
 
void loop(){
  
read_ADC = analogRead(sensor_pin);
if(read_ADC>208)read_ADC=208;

ntu = map(read_ADC, 0, 208, 300, 0); 
 
lcd.setCursor(0,0);
lcd.print("Turbidity: ");
lcd.print(ntu);
lcd.print("  ");

lcd.setCursor(0,1);//set cursor (colum by row) indexing from 0
if(ntu<10)            lcd.print("Water Very Clean");
if(ntu>=10 && ntu<30) lcd.print("Water Norm Clean");
if(ntu>=30)           lcd.print("Water Very Dirty");

delay(200);
}
