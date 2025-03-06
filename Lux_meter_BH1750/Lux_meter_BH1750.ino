#include<LiquidCrystal.h>
#include<Wire.h>

LiquidCrystal lcd (2, 3, 4, 5, 6, 7); 

int BH1750address = 0x23;
byte buff[2];

void setup(){
  Wire.begin();
  lcd.begin(16,2);
  lcd.print("  BH1750 Light  ");
  lcd.setCursor(0,1);
  lcd.print("Intensity Sensor");
  delay(2000);
  lcd.clear();
}
 
void loop(){
  int i;
  uint16_t value=0;
  BH1750_Init(BH1750address);
  delay(200);
 
  if(2==BH1750_Read(BH1750address)){
    value=((buff[0]<<8)|buff[1])/1.2;
    lcd.setCursor(0,0);
    lcd.print("Intensity in LUX");
    lcd.setCursor(6,1);
    lcd.print(value);
    lcd.print("   ");
  }
  delay(150);
}
 
int BH1750_Read(int address) {
  int i=0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while(Wire.available()) 
  {
    buff[i] = Wire.read();
    i++;
  }
  Wire.endTransmission();  
  return i;
}
 
void BH1750_Init(int address) {
  Wire.beginTransmission(address);
  Wire.write(0x10);
  Wire.endTransmission();
}
