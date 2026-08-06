/*
 * Version 3.2
 * This project is specially design from scatch
 * for simple sign language translator as requested. 
 * Author for this code is Yeo
 * Project Researcher for this code will be (017-3727353)for research (non-commercial) purpose
*/
#include <SoftwareSerial.h> 
SoftwareSerial MyBlue(2, 3); // Bluetooth RX and TX 

const int f1 = A0; //pin A0 to read analog input
const int f2 = A1;
const int f3 = A3;
const int p1 = A5;
const int p2 = A7;
int flex1; //save analog flex
int flex2;
int flex3;
String temp;  
int fsr1;
int fsr2;
int sensitvity = 0; // can be adjusted in order to match the pre-set default
 
void setup(){
  pinMode(f1, INPUT);
  pinMode(f2, INPUT);
  pinMode(f3, INPUT);
  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  Serial.begin(9600); //Begin serial communication
  MyBlue.begin(9600); //For bluetooth
}

void translate(String words)
{
  if(words!=temp)
  {
    MyBlue.print(words);
    temp=words;
    delay(2000); //after 2 seconds, clear the temp
    temp="";
  }
}

void serialprint(){
  flex1 = analogRead(f1)+ sensitvity;  //Read and save analog value from Flex sensor
  flex2 = analogRead(f2) + sensitvity;
  flex3 = analogRead(f3) + sensitvity;
  fsr1 = analogRead(p1) + sensitvity; //Read and save analog value from FSR sensor
  fsr2 = analogRead(p2) + sensitvity;
  
  Serial.print("F1:  "); //Print flex sensor value
  Serial.print(flex1);
  Serial.print("  ");
  Serial.print("F2:  ");
  Serial.print(flex2);
  Serial.print("  ");
  Serial.print("F3:  ");
  Serial.print(flex3);
  Serial.print("  ");
  Serial.print("P1:  ");
  Serial.print(fsr1);
  Serial.print("  ");
  Serial.print("P2:  ");
  Serial.print(fsr2);
  Serial.print("\n");
}


void loop(){
  serialprint();
  
  if((flex1 > 298 && flex1 < 340) && (flex2 < 175 && flex2 > 130) && (flex3 < 206 && flex3 > 100) && (fsr1 < 400) && (fsr2 < 400)){
    translate("Help");
    Serial.println("Help");
  }
  if((flex1 > 278 && flex1 < 318) && (flex2 > 168 && flex2 < 208) && (flex3 > 140 && flex3 < 189) && (fsr1 < 400) && (fsr2 > 400)){
    translate("Medicine");
    Serial.println("Medicine");
  }
  if((flex1 > 278 && flex1 < 318) && (flex2 > 170 && flex2 < 210) && (flex3 > 186 && flex3 < 226) && (fsr1 < 400) && (fsr2 > 400)){
    translate("Doctor");
    Serial.println("Doctor");
  }
  if((flex1 > 238 && flex1 < 278) && (flex2 > 120 && flex2 < 160) && (flex3 > 104 && flex3 < 144) && (fsr1 > 400) && (fsr2 < 400)){
    translate("Bathroom");
    Serial.println("Bathroom");
  }
  if((flex1 > 207 && flex1 < 247) && (flex2 > 111 && flex2 < 151) && (flex3 > 88 && flex3 < 128) && (fsr1 < 400) && (fsr2 > 400)){
    translate("Emergency");
    Serial.println("Emergency");
  }
  if((flex1 > 278 && flex1 < 318) && (flex2 > 143 && flex2 < 183) && (flex3 > 109 && flex3 < 149) && (fsr1 > 400) && (fsr2 > 400)){
    translate("Eat");
    Serial.println("Eat");
  }
  if((flex1 > 278 && flex1 < 318) && (flex2 > 122 && flex2 < 162) && (flex3 > 123 && flex3 < 163) && (fsr1 < 400) && (fsr2 > 400)){
    translate("Dizzy");
    Serial.println("Dizzy");
  }
  if((flex1 > 98 && flex1 < 238) && (flex2 > 170 && flex2 < 210) && (flex3 > 186 && flex3 < 226) && (fsr1 > 400) && (fsr2 < 400)){
    translate("Water");
    Serial.println("Water");
  }
  if((flex1 > 278 && flex1 < 318) && (flex2 > 105 && flex2 < 145) && (flex3 > 83 && flex3 < 123) && (fsr1 < 400) && (fsr2 < 400)){
    translate("Hungry");
    Serial.println("Hungry");
  }
  delay(100);
}
