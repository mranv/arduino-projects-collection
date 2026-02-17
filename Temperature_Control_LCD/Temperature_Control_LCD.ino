#include <EEPROM.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define ThermistorPin A0 // for Arduino microcontroller

#define bt_set  A3
#define bt_up   A4
#define bt_down A5

#define fan 9
#define buzzer 13

long ADC_Value;
float R1 = 10000; // value of R1 on board
float logR2, R2, T;

//steinhart-hart coeficients for thermistor
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;  

float setL_temp = 30.5; 
float setH_temp = 39.5; 
float temp=0;

int duty_cycle;  
int Set=0, flag=0, flash=0;

void setup() {// put your setup code here, to run once: 

pinMode(ThermistorPin, INPUT);
  
pinMode(bt_set,  INPUT_PULLUP);
pinMode(bt_up,   INPUT_PULLUP);
pinMode(bt_down, INPUT_PULLUP);

pinMode(fan, OUTPUT);
pinMode(buzzer, OUTPUT);

lcd.begin(16, 2); // Configura lcd numero columnas y filas
lcd.clear();
lcd.setCursor (0,0);
lcd.print("   Welcome To   ");
lcd.setCursor (0,1);
lcd.print("  Temp Control  ");

if(EEPROM.read(0)==0){}
else{
EEPROM.put(10, setL_temp);
EEPROM.put(15, setH_temp);
EEPROM.write(0, 0);
}
EEPROM.get(10, setL_temp);
EEPROM.get(15, setH_temp);

delay(2000); //wait 1000 mS for next measure
lcd.clear();
}

void loop(){

ADC_Value=0;
for(int i=0; i<100; i++) {
ADC_Value = ADC_Value+analogRead(ThermistorPin);
delay(1);
}

ADC_Value=ADC_Value/100;
R2 = R1 * (1023.0 / (float)ADC_Value - 1.0); //calculate resistance on thermistor
logR2 = log(R2);
temp = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // temperature in Kelvin
temp = temp - 273.15; //convert Kelvin to Celcius

int value1 = temp*10;
int value2 = setL_temp*10;
int value3 = setH_temp*10;
 
duty_cycle = map(value1, value2, value3, 0, 100);  
if(duty_cycle>100)duty_cycle=100;
if(duty_cycle<0)duty_cycle=0;

if(temp<setL_temp){digitalWrite(fan, 0);}
              else{analogWrite(fan, (duty_cycle*2)+55); }

if(temp>setH_temp){digitalWrite(buzzer, HIGH);  delay(100);}

if(digitalRead(bt_set)==0){
digitalWrite(buzzer, HIGH);  
 if(flag==0){ flag=1;
  Set=Set+1;
  if(Set>2){Set=0; flash=0;} 
delay(200);
 }
}else{flag=0;}

if(digitalRead(bt_up)==0){
digitalWrite(buzzer, HIGH); 
if(Set==1){setL_temp = setL_temp+.1;EEPROM.put(10, setL_temp);}
if(Set==2){setH_temp = setH_temp+.1;EEPROM.put(15, setH_temp);}  
delay(10);
}

if(digitalRead(bt_down)==0){
digitalWrite(buzzer, HIGH);   
if(Set==1){setL_temp = setL_temp-.1;EEPROM.put(10, setL_temp);}
if(Set==2){setH_temp = setH_temp-.1;EEPROM.put(15, setH_temp);}  
delay(10);
}

if(Set==0){

lcd.setCursor(0,0);
lcd.print("  Temp: ");
lcd.print(temp,1);
lcd.write(223); 
lcd.print("C   ");

lcd.setCursor(0,1);
lcd.print(" Fan Speed:");
if(duty_cycle<100)lcd.print(" ");
lcd.print(duty_cycle);
lcd.print("%   ");

}else{
lcd.setCursor(0,0);
lcd.print("  Setting Mode  ");

lcd.setCursor(0,1);
lcd.print("L:");
if(Set==1 && flash==1){lcd.print("    ");}
else{lcd.print(setL_temp,1);}
lcd.print("C  ");

lcd.setCursor(9,1);
lcd.print("H:");
if(Set==2 && flash==1){lcd.print("    ");}
else{lcd.print(setH_temp,1);}
lcd.print("C  ");
}

if(Set>0){flash=!flash;}
delay(1); //wait 1 mS for next measure
digitalWrite(buzzer, LOW); 
}
