///--DHT 11-///
//DHT GPIO 7

#include "DHT.h"
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

///


#define BLYNK_TEMPLATE_ID "TMPLv7qrcXqD"
#define BLYNK_TEMPLATE_NAME "Sensors"
#define BLYNK_AUTH_TOKEN "xDsdqmdmnQhtB8DFL8ohYW2_ieiMj36G"

#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Cicada";
char pass[] = "6dnpnanv";

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 18;  // the number of the pushbutton pin
const int ledPin = 19;    // the number of the LED pin

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  Serial.begin(115200);
  //pass auth token, network ssid, pwd to blynk.
  Blynk.begin(auth, ssid, pass);
  
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  //DHT
  dht.begin();
}

void loop() {
  
  Blynk.run();
  Blynk.virtualWrite(V2,"ONLINE");
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    Blynk.virtualWrite(V1,"SOS TRIGGERED");
    Blynk.virtualWrite(V0,HIGH);

 
    
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    Blynk.virtualWrite(V1,"SOS CLEARED");
    Blynk.virtualWrite(V0,LOW);
  }
  delay(500);
  //DHT READING
    
    //DHT Reading
    float h = dht.readHumidity();
     // Read temperature as Celsius (the default)
    float t = dht.readTemperature();

 
   // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Blynk.virtualWrite(V3,h);
  
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Blynk.virtualWrite(V2,t);

  Blynk.virtualWrite(V4,hic);
  
 
  Serial.print(hic);
  Serial.print(F("°C "));
  
  

  
  
}
