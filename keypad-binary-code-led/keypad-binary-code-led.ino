#include <Keypad.h>

#define ROWS 4
#define COLS 4

char keys[ROWS][COLS] = { {'1','2','3','A'},
  						  {'4','5','6','B'},
  						  {'7','8','9','C'},
  						  {'*','0','#','D'} };
const int binNum[10][4] = {  { 0,0,0,0 },    // 0
                             { 0,0,0,1 },    // 1
                             { 0,0,1,0 },    // 2
                             { 0,0,1,1 },    // 3
                             { 0,1,0,0 },    // 4
                             { 0,1,0,1 },    // 5
                             { 0,1,1,0 },    // 6
                             { 0,1,1,1 },    // 7
                             { 1,0,0,0 },    // 8
                             { 1,0,0,1 } };  // 9

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  for (int i = 10; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
}
  
void loop() {
  int key = keypad.getKey();
  
  if (key) {
    key = key - 48;
    if (key < 0 || key > 9) {
      Serial.println("Press a number 0-9");
    }
    else {
      Serial.print("Key = ");
      Serial.println(key);
      writeLED(key);
      delay(500);
    }
  }
}

void writeLED(int key) {
  for (int i = 10; i < 14; i++) {
    digitalWrite(i, binNum[key][i-10]);
  }
}