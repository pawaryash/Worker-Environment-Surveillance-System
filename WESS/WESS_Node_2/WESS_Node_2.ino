/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read data from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * Example sketch/program showing how to read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 * 
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the ID/UID, type and any data blocks it can read. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 * 
 * If your reader supports it, this sketch/program will read all the PICCs presented (that is: multiple tag reading).
 * So if you stack two or more PICCs on top of each other and present them to the reader, it will first output all
 * details of the first and then the next PICC. Note that this may take some time as all data blocks are dumped, so
 * keep the PICCs at reading distance until complete.
 * 
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#define BLYNK_TEMPLATE_ID "TMPL8zJeC-ZW"
#define BLYNK_TEMPLATE_NAME "WESS Node 2"
#define BLYNK_AUTH_TOKEN "-ue5qt9BHR_HbZT-nC3gHA0AsQfvJk7U"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <iostream>
#include <string>
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Cicada";
char pass[] = "6dnpnanv";


#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         22          // Configurable, see typical pin layout above
#define SS_PIN          5         // Configurable, see typical pin layout above


String uidString;

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
void dump_byte_array(byte *buffer, byte bufferSize) {

    int counter = 0;
    uidString = "";
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        if(counter <= bufferSize){
            uidString += buffer[i];  
            counter++;          
          }
        Serial.print(buffer[i], HEX);    
    }    
}

void setup() {
  Serial.begin(115200);   // Initialize serial communications with the PC
  Blynk.begin(auth, ssid, pass);

  SPI.begin();            // Init SPI bus
  mfrc522.PCD_Init();    // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {

  // Initialize the user card detail variable    
  String userName;
  // Look for new cards
  Blynk.run();
  Blynk.virtualWrite(V7,"ONLINE");
    
  // Check if there is new card
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  
  //Serial.println(F(""));
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);

  // Assign username by card id
  if(uidString == "12810210233"){
    userName = "Nitin";
    Blynk.virtualWrite(V4,1);
    Blynk.virtualWrite(V3,0);    
  }
  else if(uidString == "10813451127"){
    userName = "Pankaj"; 
    Blynk.virtualWrite(V4,1);   
    Blynk.virtualWrite(V3,0);
  }
  else if(uidString == "22623524225"){
    userName = "Mukesh";   
    Blynk.virtualWrite(V4,1); 
    Blynk.virtualWrite(V3,0);
  }
  else if(uidString == "3324922529"){
    userName = "Atul";    
    Blynk.virtualWrite(V4,1); 
    Blynk.virtualWrite(V3,0);
  }
  else{
    userName="Unauthorized";  
    Blynk.virtualWrite(V3,1); 
    Blynk.virtualWrite(V4,0);  
  }

  // Update dashboard
  Blynk.virtualWrite(V6,uidString);
  Blynk.virtualWrite(V5,userName);
}
