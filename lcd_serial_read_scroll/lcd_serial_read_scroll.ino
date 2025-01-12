#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter your name");
  lcd.setCursor(0,1);
  lcd.print("up to 39 chars");
  delay(1500);
  Serial.println("Enter your name:");
}

void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  
  // Get total number of characters
  int nOfSerial = Serial.available();
  // Check if the number of characters > 39
  int delChars = 0;
  if (nOfSerial > 39) {
    // Save the number of characters that will not be displayed
    delChars = nOfSerial - 40;
  }
  
  // Display the message
  for (int i = nOfSerial; i > delChars; i--) {
    lcd.write(Serial.read());
    delay(50);
  }
  
  delay(200);
  // Scroll to display all the characters
  // if the number of characters > 16
  if (nOfSerial > 16) {
    for (int i = 0; i < nOfSerial - 16 - delChars; i++) {
      lcd.scrollDisplayLeft();
	  delay(300);
    }
  }
  
  // Clear serial buffer
  if (delChars) {
    while(Serial.available()) {
      Serial.read();
    }
  }
  
  delay(1000);
}