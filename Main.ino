#include <SPI.h>
#include <MFRC522.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// Define the NFC reader pins and create an instance of the MFRC522 library
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Define the pins for the solenoid lock and LEDs
const int solenoidPin = 8;
const int greenLedPin = 2;
const int redLedPin = 3;
const int buzzerPin = 4;

// Define variables for storing the UID of the NFC tag and the database connection
String tagUID = "";
IPAddress server_addr(192,168,1,100);
char user[] = "username";
char password[] = "password";
char database[] = "database_name";

// Create an instance of the MySQL_Connection and MySQL_Cursor classes
WiFiClient client;
MySQL_Connection conn((Client *)&client);
MySQL_Cursor cursor(&conn);

void setup() {
  Serial.begin(9600);
  SPI.begin(); // Initialize the SPI bus
  mfrc522.PCD_Init(); // Initialize the MFRC522 RFID reader

  // Set the solenoid lock, LEDs, and buzzer pins as outputs
  pinMode(solenoidPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Connect to the database
  if (conn.connect(server_addr, 3306, user, password)) {
    Serial.println("Connected to database successfully!");
  } else {
    Serial.println("Connection failed.");
  }
}

void loop() {
  // Wait for an NFC tag to be detected
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Get the UID of the tag and convert it to a string
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      tagUID += String(mfrc522.uid.uidByte[i], HEX);
    }

    // Query the database to check if the user has access
    String query = "SELECT * FROM users WHERE nfc_uid='" + tagUID + "'";
    cursor.execute(query);
    MySQL_Row row = cursor.getRow();

    // If the user has access, unlock the door and display a success message
    if (row.length() > 0) {
      digitalWrite(solenoidPin, HIGH); // Unlock the door
      digitalWrite(greenLedPin, HIGH); // Turn on the green LED
      digitalWrite(redLedPin, LOW); // Turn off the red LED
      tone(buzzerPin, 1000, 500); // Play a success tone
      Serial.println("Access granted!");
    } else {
      // If the user does not have access, display a failure message
      digitalWrite(greenLedPin, LOW); // Turn off the green LED
      digitalWrite(redLedPin, HIGH); // Turn on the red LED
      Serial.println("Access denied!");
    }

    // Clear the tagUID variable for the next loop
    tagUID = "";

    // Wait a few seconds before resetting the NFC reader
    delay(3000);
    mfrc522.PICC_H
    // Wait a few seconds before resetting the NFC reader
    delay(3000);
    mfrc522.PICC_HaltA(); // Stop reading from the tag
    mfrc522.PCD_StopCrypto1(); // Stop encryption on the tag
  }
}
