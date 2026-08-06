/*
 * Version 1.2
 * This flex sensor testing coding is specially design from scatch
 * for simple sign language translator as requested. 
 * Author for this code is Yeo
 * Owner for this code will be (017-3727353)
*/

const int flexPin = A0; //pin A0 to read analog input
const int flexPin2 = A1;
int flex1; //save analog flex
int flex2;
String words;
 
void setup(){
  pinMode(flexPin, INPUT);
  pinMode(flexPin2, INPUT);
  Serial.begin(9600);       //Begin serial communication
}

void loop(){
  flex1 = analogRead(flexPin);         //Read and save analog value from potentiometer
  flex2 = analogRead(flexPin2);
  Serial.print("Flex 1:\t");               //Print flex sensor value
  Serial.print(flex1);
  Serial.print("\t");
  Serial.print("Flex 2:\t");
  Serial.print(flex2); 
  Serial.print("\n");
  words = translate(flex1,flex2);
  Serial.println(words);
  delay(100);
}

String translate(int v1, int v2){
  if(v1 > 240 && v2 < 120)
  {
    return("Medicine");
  }
  else
  {
    return("");
  }
}
