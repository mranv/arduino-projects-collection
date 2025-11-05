const int dataPin = 8;
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
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
}

void loop() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, numbers[i]);
    digitalWrite(latchPin, HIGH);

    delay(1500);
  }

}
