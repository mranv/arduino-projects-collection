//TMP36 Temperature Sensor
int sensorPin = 0;
int myDelay = 1000;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // get the voltage reading from the temperature sensor
  int sensorVal = analogRead(sensorPin);  

  // convert that reading to voltage
  float vout = sensorVal * 5.0 / 1024.0;

  // print out the voltage
  Serial.print(vout); 
  Serial.println(" volts");

  // print out the temperature
  // converting from 10 mv per degree with 500 mV offset
  float temperatureC = (vout - 0.5) * 100 ;
  Serial.print(temperatureC); Serial.println(" degrees C");

  // convert to Fahrenheit
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print(temperatureF); Serial.println(" degrees F");

  delay(myDelay);
}