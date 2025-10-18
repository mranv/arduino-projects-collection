// Security system with PIR sensor and Piezo buzzer
#include <Keypad.h>
const int PIR_PIN = 2;
const int BUZZER_PIN = 3;
const int LED_PIN = 4;
const int ROWS = 4;
const int COLS = 4;

char keys[ROWS][COLS] = { {'1','2','3','A'},
  						  {'4','5','6','B'},
  						  {'7','8','9','C'},
  						  {'*','0','#','D'} };
byte rowPins[ROWS] = {12, 11, 10, 9};
byte colPins[COLS] = {8, 7, 6, 5};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

bool locked = true;
int lockPassword = 1234;
int maxAttempts = 3;
bool ledOn = false;
bool buzzerOn = false;
int attempts;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), getMotion, CHANGE); 
}

int getPassword() {
  int password = 0;
  while (1) {
    char key = keypad.getKey();
  	if (key) {
      Serial.print("You entered: ");
      Serial.println(key);
      if (key == '#')
        break;
      if (key - 'A' >=0 && key - 'A' <=3)
        continue;
      password *= 10;
      password += (String(key)).toInt();
    }
  }
  if (password == lockPassword)
    return 1;
  return 0;
}

void getMotion() {
  ledOn = !ledOn;
  digitalWrite(LED_PIN, ledOn);
}

void unlock() {
  buzzerOn = false;
  digitalWrite(BUZZER_PIN, LOW);
  locked = false;
  Serial.println("The alarm was deactivated successfully!");
}

void lock() {
  char key = keypad.getKey();
  if (key == '*') {
    locked = true;
    Serial.println("The alarm was activated successfully!");
  }
}

void loop() {
  if (locked && ledOn && !buzzerOn) {
    buzzerOn = true;
    digitalWrite(BUZZER_PIN, HIGH);
    attempts = 1;
    Serial.println("Enter the password to unlock:");
    int state = getPassword();
    if (state)
      unlock();
  } else if (locked && buzzerOn) {
    attempts++;
    if (attempts > maxAttempts)
      Serial.println("Police are on the way!!!");
    Serial.println("Enter the password to unlock:");
    int state = getPassword();
    if (state)
      unlock();
  }
  if (!locked) {
    lock();
  }
}