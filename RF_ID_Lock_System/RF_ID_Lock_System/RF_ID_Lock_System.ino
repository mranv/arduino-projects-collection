#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable
#define SS_PIN          10         // Configurable
#define RELAY_PIN       2
#define RED_LED         3
#define GREEN_LED       4
#define ACCESS_DELAY    3000       //3 seconds
#define ALLOWED_TAG_UID     "FC723231"  //Put your tag uid here

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() 
{
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
  
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  digitalWrite(RELAY_PIN, HIGH);   //Switch off relay initially. Relay is LOW level triggered relay so we need to write HIGH.
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);    
}

void loop() 
{
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if ( ! mfrc522.PICC_IsNewCardPresent()) 
	{
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) 
	{
		return;
	}

  //Convert hex uid into string
  String tagUID;
  char tempStr[3];  
  for (int i = 0; i < mfrc522.uid.size; i++)
  {
    sprintf(tempStr, "%02x", mfrc522.uid.uidByte[i]);
    tagUID += tempStr;
  }
  tagUID.toUpperCase();

  if ( tagUID == ALLOWED_TAG_UID)
  {
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(GREEN_LED, HIGH);
    delay(ACCESS_DELAY);
    digitalWrite(GREEN_LED, LOW); 
    digitalWrite(RELAY_PIN, HIGH); 
  }
  else
  {
    //Blink Red LED
    digitalWrite(RED_LED, HIGH);
    delay(200);
    digitalWrite(RED_LED, LOW); 
    delay(200);    
    digitalWrite(RED_LED, HIGH);
    delay(200);
    digitalWrite(RED_LED, LOW); 
  }
  
  mfrc522.PICC_HaltA(); // Stop reading    
}
