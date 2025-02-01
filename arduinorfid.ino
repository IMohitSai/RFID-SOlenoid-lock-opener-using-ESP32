#include <SPI.h>
#include <MFRC522.h>

// Define RFID pins (as per Arduino)
#define RST_PIN 9   // Reset pin for RC522
#define SS_PIN 10   // Slave Select pin for RC522

// Define the relay control pin
#define RELAY_PIN 7 // Pin connected to relay module IN pin

// Define relay states
#define SOLENOID_UNLOCK LOW  // LOW to unlock solenoid (active LOW relay)
#define SOLENOID_LOCK HIGH   // HIGH to lock solenoid

// Create an MFRC522 instance
MFRC522 rfid(SS_PIN, RST_PIN);

// List of authorized UIDs
byte authorizedUIDs[][4] = {
  {0x39, 0x94, 0x91, 0x65},
  {0x39, 0x81, 0x91, 0x65},
  {0x23, 0xAB, 0x90, 0xE4},
  {0xF9, 0x5D, 0x38, 0x63}
};
const int numAuthorizedUIDs = sizeof(authorizedUIDs) / sizeof(authorizedUIDs[0]);

void setup() {
  // Configure relay pin as output
  pinMode(RELAY_PIN, OUTPUT);

  // Set relay to locked state (HIGH) at startup
  digitalWrite(RELAY_PIN, SOLENOID_LOCK); // Ensure relay is initially locked

  // Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println("Starting system initialization...");

  // Initialize SPI bus
  SPI.begin();

  // Initialize RFID module
  rfid.PCD_Init();

  // Check if RFID module is detected
  if (!rfid.PCD_PerformSelfTest()) {
    Serial.println("RFID module not detected! Check connections.");
    while (true); // Halt the system
  }

  Serial.println("System Initialized");
  Serial.println("Solenoid is LOCKED");
  Serial.println("Waiting for authorized RFID card...");
}

void loop() {
  // Check for new RFID cards
  if (!rfid.PICC_IsNewCardPresent()) {
    delay(50);
    return;
  }

  // Read the card serial
  if (!rfid.PICC_ReadCardSerial()) {
    Serial.println("Failed to read card. Try again.");
    delay(50);
    return;
  }

  // Print the UID of the detected card
  Serial.print("Card detected - UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Check if the card is authorized
  if (isAuthorized(rfid.uid.uidByte, rfid.uid.size)) {
    Serial.println("Access Granted!");
    unlockSolenoid();
  } else {
    Serial.println("Access Denied - Invalid Card");
  }

  // Halt communication with the card
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

// Function to check if the UID is authorized
bool isAuthorized(byte *uid, byte size) {
  for (int i = 0; i < numAuthorizedUIDs; i++) {
    bool match = true;
    for (int j = 0; j < size; j++) {
      if (authorizedUIDs[i][j] != uid[j]) {
        match = false;
        break;
      }
    }
    if (match) return true;
  }
  return false;
}

// Function to unlock the solenoid
void unlockSolenoid() {
  Serial.println("Unlocking solenoid...");
  digitalWrite(RELAY_PIN, SOLENOID_UNLOCK); // Set LOW to unlock solenoid
  Serial.println("Solenoid UNLOCKED");

  delay(3000); // Keep solenoid unlocked for 3 seconds

  Serial.println("Relocking solenoid...");
  digitalWrite(RELAY_PIN, SOLENOID_LOCK); // Set HIGH to lock solenoid
  Serial.println("Solenoid LOCKED");
}
