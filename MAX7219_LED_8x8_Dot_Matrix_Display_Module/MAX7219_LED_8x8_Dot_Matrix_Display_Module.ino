#include "LedControl.h"

#define CLK 8
#define CS  9
#define DIN 10

LedControl Display=LedControl(DIN,CLK,CS,0);

byte smile[8]=   {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};
byte neutral[8]= {0x3C,0x42,0xA5,0x81,0xBD,0x81,0x42,0x3C};
byte sad[8]=     {0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C};

void setup(){
 Display.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
 Display.setIntensity(0,15);      // Set the brightness to maximum value
 Display.clearDisplay(0);         // and clear the display
}
void loop(){     
    printByte(smile);
    delay(1000);
    printByte(neutral);
    delay(1000);
    printByte(sad);    
    delay(1000);
    Display.clearDisplay(0);  
    delay(1000);
}

void printByte(byte character []){
  for(int i=0; i<8; i++){
    Display.setRow(0,i,character[i]);
  }
}
