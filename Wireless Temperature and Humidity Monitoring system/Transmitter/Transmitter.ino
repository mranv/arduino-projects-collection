#include "DHT-22.h"
#include <SoftwareSerial.h>
SoftwareSerial BT_Serial(8, 9); // RX, TX

#define DHT22_PIN A0 // what pin on the arduino is the DHT22 data line connected to
DHT22 dht(DHT22_PIN);

int temp, hum;

void setup() {
 Serial.begin(9600);
 BT_Serial.begin(9600);
 dht.begin();
 delay(2000);
}

void loop(){

dht.readHumidity();
dht.readTemperature();

hum = dht.humidity;  
temp = dht.temperature_C;   

BT_Serial.write("A");
BT_Serial.write(hum);
BT_Serial.write(temp);
delay(500);
}
