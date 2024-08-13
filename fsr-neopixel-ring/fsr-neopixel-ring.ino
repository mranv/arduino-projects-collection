// Example code to control a Neopixel ring with 16 LEDs
// using a force sensing resistor (FSR)

#include <Adafruit_NeoPixel.h>

#define FSRPIN 0
#define PIN 6
#define NUMPIXELS 16

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pixels.begin();
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'
  // Read the FSR pin and store the output as fsrreading: 
  int fsrReading = analogRead(FSRPIN);
  // Print the fsrreading in the serial monitor:
  Serial.print("reading: ");
  Serial.println(fsrReading);
  // The maximum value is 914, so I set the max to 900
  int fsrVal = constrain(fsrReading, 0, 900);
  // Find the number of LEDs to turn on
  int leds = round(map(fsrVal, 0, 900, 0, NUMPIXELS));
  for(int i = 0; i < leds; i++) {
    pixels.setPixelColor(i, pixels.Color(180, 100, 50));
    pixels.show();   // Send the updated pixel colors
  }
  delay(50);
}