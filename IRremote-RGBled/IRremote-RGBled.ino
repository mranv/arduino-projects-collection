// Control a RGB LED using IR Remote
#include <IRremote.hpp>
#define IRPIN 7
#define REDPIN 6
#define BLUEPIN 10
#define GREENPIN 9

int colors[10][3] = {{242, 20, 60},
					 {255, 140, 0},
					 {255, 215, 0},
                     {154, 205, 50},
                     {34, 139, 34},
					 {32, 178, 170},
  					 {135, 206, 250},
                     {0, 0, 128},
                     {138, 43, 226},
                     {238, 130, 238}};
void setup() {
  // Start the receiver
  IrReceiver.begin(IRPIN, ENABLE_LED_FEEDBACK);
  Serial.begin(9600);
  // RGB LED
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
}

int translateIR(long IRvalue) {
  switch(IRvalue) {
    case 0xF30CBF00: return 0;
    case 0xEF10BF00: return 1;
    case 0xEE11BF00: return 2;
    case 0xED12BF00: return 3;
    case 0xEB14BF00: return 4;
    case 0xEA15BF00: return 5;
    case 0xE916BF00: return 6;
    case 0xE718BF00: return 7;
    case 0xE619BF00: return 8;
    case 0xE51ABF00: return 9;
    default: return -1;
  }
}

void RGBColor(int value) {
  analogWrite(REDPIN, colors[value][0]);
  analogWrite(GREENPIN, colors[value][1]);
  analogWrite(BLUEPIN, colors[value][2]);
}

void loop() {
  if (IrReceiver.decode()) {
    int number = translateIR(IrReceiver.decodedIRData.decodedRawData);
    Serial.print("Number pressed: ");
    Serial.println(number);
    RGBColor(number);
    IrReceiver.resume(); // Enable receiving of the next value
  }
}