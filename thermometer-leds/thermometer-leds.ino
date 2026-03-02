#define coldTmp 15
#define hotTmp 30
int sensorPin = A0;
int redPin = 2;
int orangePin = 3;
int bluePin = 4;
int myDelay = 500;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(orangePin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // get the voltage reading from the temperature sensor
  int sensorVal = analogRead(sensorPin);  

  // convert that reading to voltage
  float vout = sensorVal * 5.0 / 1024.0;

  // print out the temperature
  // converting from 10 mv per degree with 500 mV offset
  float temperatureC = (vout - 0.5) * 100 ;
  Serial.print(temperatureC); Serial.print(" degrees C | ");

  // convert to Fahrenheit
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print(temperatureF); Serial.println(" degrees F");
  
  // turn on a led
  if (temperatureC < coldTmp) {
    digitalWrite(bluePin, HIGH);
    digitalWrite(orangePin, LOW);
    digitalWrite(redPin, LOW);
  }
  else if (temperatureC >= coldTmp && temperatureC < hotTmp) {
    digitalWrite(orangePin, HIGH);
    digitalWrite(bluePin, LOW);
    digitalWrite(redPin, LOW);
  }
  else {
    digitalWrite(redPin, HIGH);
    digitalWrite(orangePin, LOW);
    digitalWrite(bluePin, LOW);
  }

  delay(myDelay);
}