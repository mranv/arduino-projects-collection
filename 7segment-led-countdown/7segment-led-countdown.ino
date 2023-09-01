const int numbers[10][7] = { { 0,0,0,0,0,1,0 },    // 0
                             { 1,0,0,1,1,1,1 },    // 1
                             { 0,0,1,0,0,0,1 },    // 2
                             { 0,0,0,0,1,0,1 },    // 3
                             { 1,0,0,1,1,0,0 },    // 4
                             { 0,1,0,0,1,0,0 },    // 5
                             { 0,1,0,0,0,0,0 },    // 6
                             { 0,0,0,1,1,1,1 },    // 7
                             { 0,0,0,0,0,0,0 },    // 8
                             { 0,0,0,0,1,0,0 } };  // 9

void setup() {
  for (int i = 2; i < 9; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
}

void loop() {
  // Show a countdown 9 to 0
  for (int i = 9; i >= 0; i--) {
    writeNum(i);
    delay(1500);
  }
  
  // Turn off the LEDs
  for (int i = 2; i < 9; i++) {
    digitalWrite(i, HIGH);
  }
  delay(1500);
}

void writeNum(int num) {
  for (int i = 2; i < 9; i++) {
    digitalWrite(i, numbers[num][i-2]);
  }
}