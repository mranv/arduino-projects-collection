#include <Keypad.h>

#define ROWS 4
#define COLS 4

// Keypad
char keys[ROWS][COLS] = { {'1','2','3','A'},
  						  {'4','5','6','B'},
  						  {'7','8','9','C'},
  						  {'*','0','#','D'} };
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Shit register
const int latchPin = 10;
const int clockPin = 11;
const int dataPin = 12;

void setup() {
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  randomSeed(analogRead(0));
  Serial.begin(9600);
}

void displayBinNumber(byte a) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, a);
  digitalWrite(latchPin, HIGH);
}

int getAnswer() {
  int answer = 0;
  while (1) {
    char key = keypad.getKey();
    if (key != NO_KEY) {
      Serial.print("You entered: ");
      Serial.println(key);
      if (key == '#') {
        break;
      }
      answer *= 10;
      answer += (String(key)).toInt();
    }
  }
  return answer;
}

bool checkAnswer(int number, int answer) {
  if (answer == number) {
    return 1;
  }
  return 0;
}

void loop() {
  // Generate random number
  int number = random(0, 256);
  // Display the binary number on the LEDs
  displayBinNumber(number);
  // Read a number from the keypad
  Serial.println("Enter a number in the keypad (0-255) and press #.");
  int answer = getAnswer();
  Serial.print("Your answer: ");
  Serial.println(answer);
  // Check the answer
  bool result = checkAnswer(answer, number);
  // Diplay the result
  if (result) {
    Serial.println("That's correct!");
  }
  else {
    Serial.print("Wrong answer! The number is: ");
    Serial.println(number);
  }
  delay(100);
}