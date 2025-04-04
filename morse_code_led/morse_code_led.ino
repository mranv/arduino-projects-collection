int ledPin = 12;
int dotDelay = 400;

char* letters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." };

char* numbers[] = {
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  char ch;
  if (Serial.available() > 0) {
    ch = Serial.read();
    if (ch >= 'a' && ch <= 'z') {
      flashChar(letters[ch - 'a']);
    }
    else if (ch >= 'A' && ch <= 'Z') {
      flashChar(letters[ch - 'A']);
    }
    else if (ch >= '0' && ch <= '9') {
      flashChar(numbers[ch - '0']);
    }
    else if (ch == ' ') {
      delay(dotDelay * 7);  // gap between words  
    }
  }
}

void flashChar(char* sequence) {
  int i = 0;
  while (sequence[i] != NULL) {
    flashDotDash(sequence[i]);
    i++;
  }
  delay(dotDelay * 3);    // gap between letters
}

void flashDotDash(char dotOrDash) {
  digitalWrite(ledPin, HIGH);
  if (dotOrDash == '.') {
    delay(dotDelay);           
  }
  else {
    delay(dotDelay * 3);           
  }
  digitalWrite(ledPin, LOW);    
  delay(dotDelay); // gap between flashes
}