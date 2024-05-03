#define sensorPin A0
#define dataPin 8
#define latchPin 10
#define clockPin 11
#define DELAY 100
unsigned long previousTime = 0;

// the binary numbers of 0-9
int numbers[10] = { 0B00000001,		//0
                    0B01001111,		//1
                    0B00010010,		//2
                    0B00000110,		//3
                    0B01001100,		//4
                    0B00100100,		//5
                    0B00100000,		//6
                    0B00001111,		//7
                    0B00000000,		//8
                    0B00000100 };	//9
int off = 0B11111111;
int minus = 0B11111101;

void setup() {
  Serial.begin(9600);
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  digitalWrite(latchPin, LOW);
  for (int i = 0; i < 3; i++) {
    shiftOut(dataPin, clockPin, MSBFIRST, off);
  }
  digitalWrite(latchPin, HIGH);
  
}

void displayTemperature(float temperature) {
  if (temperature >= 0) {
    int temp = (int)(temperature * 10);
    if (temp < 100) {
      int digit3 = temp % 10;
      int digit2 = temp / 10;
      digit3 = (numbers[digit3] << 1) + 1;
      digit2 = numbers[digit2] << 1;
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, digit3);
      shiftOut(dataPin, clockPin, MSBFIRST, digit2);
      shiftOut(dataPin, clockPin, MSBFIRST, off);
      digitalWrite(latchPin, HIGH);
    }
    else if (temp >= 100 && temp < 1000) {
      int digit3 = temp % 10;
      temp /= 10;
      int digit2 = temp % 10;
      int digit1 = temp / 10;
      digit3 = (numbers[digit3] << 1) + 1;
      digit2 = numbers[digit2] << 1;
      digit1 = (numbers[digit1] << 1) + 1;
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, digit3);
      shiftOut(dataPin, clockPin, MSBFIRST, digit2);
      shiftOut(dataPin, clockPin, MSBFIRST, digit1);
      digitalWrite(latchPin, HIGH);
    }
    else {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, 0B00001001);
      shiftOut(dataPin, clockPin, MSBFIRST, 0B00001000);
      shiftOut(dataPin, clockPin, MSBFIRST, 0B00001001);
      digitalWrite(latchPin, HIGH);
    }      
  }
  else {
    if (temperature > -10) {
      int temp = abs(temperature * 10);
      int digit3 = temp % 10;
      int digit2 = temp / 10;
      digit3 = (numbers[digit3] << 1) + 1;
      digit2 = numbers[digit2] << 1;
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, digit3);
      shiftOut(dataPin, clockPin, MSBFIRST, digit2);
      shiftOut(dataPin, clockPin, MSBFIRST, minus);
      digitalWrite(latchPin, HIGH);
    }
    else {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, 0B00001001);
      shiftOut(dataPin, clockPin, MSBFIRST, 0B00001000);
      shiftOut(dataPin, clockPin, MSBFIRST, minus);
      digitalWrite(latchPin, HIGH);
    }
  }
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= DELAY || previousTime == 0) {
    // save the last time you blinked the LED
    previousTime = currentTime;
    // get the voltage reading from the temperature sensor
    int sensorVal = analogRead(sensorPin);  

    // convert that reading to voltage
    float vout = sensorVal * 5.0 / 1024.0;

    // print out the temperature
    // converting from 10 mv per degree with 500 mV offset
    float temperatureC = (vout - 0.5) * 100 ;
    Serial.print(temperatureC);
    Serial.println(" degrees C");

    // display the temperature
    displayTemperature(round(temperatureC * 10.0) / 10.0);
  } 
}