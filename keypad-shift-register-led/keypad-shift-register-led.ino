#include <Keypad.h>

#define ROWS 4
#define COLS 4

char keys[ROWS][COLS] = { {'1','2','3','A'},
  						  {'4','5','6','B'},
  						  {'7','8','9','C'},
  						  {'*','0','#','D'} };
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Shift register
const int dataPin = 12;
const int latchPin = 10;
const int clockPin = 11;


// the binary numbers of 0-9
int numbers[10] = { 0B00000011,		//0
                    0B10011111,		//1
                    0B00100101,		//2
                    0B00001101,		//3
                    0B10011001,		//4
                    0B01001001,		//5
                    0B01000001,		//6
                    0B00011111,		//7
                    0B00000001,		//8
                    0B00001001 };	//9


void setup() {
  Serial.begin(9600);
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  
  int off = 0B11111111;
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, off);
  digitalWrite(latchPin, HIGH);
  delay(500);
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    Serial.println(key);
    int i = (String(key)).toInt();
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, numbers[i]);
    digitalWrite(latchPin, HIGH);
    delay(500);
  }

}