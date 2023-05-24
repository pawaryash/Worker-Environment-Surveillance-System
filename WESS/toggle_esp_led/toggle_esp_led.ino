#define BLYNK_TEMPLATE_ID "TMPLv7qrcXqD"
#define BLYNK_TEMPLATE_NAME "Sensors"
#define BLYNK_AUTH_TOKEN "xDsdqmdmnQhtB8DFL8ohYW2_ieiMj36G"

#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Cicada";
char pass[] = "6dnpnanv";

char auth[] = BLYNK_AUTH_TOKEN;

int LEDState=0;
int LEDPin=18;
int buttonPin=19;
int buttonNew;
int buttonOld=1;
int dt=100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LEDPin, OUTPUT);
  pinMode(buttonPin, INPUT);

}

void loop() {
  Blynk.run();
  buttonNew=digitalRead(buttonPin);
  if(buttonOld==0 && buttonNew==1){
  if (LEDState==0){
    digitalWrite(LEDPin,HIGH);
    Blynk.virtualWrite(V0,HIGH);
    Blynk.virtualWrite(V1,"SOS TRIGGERED!");
    
    LEDState=1;
  }
  else{
    digitalWrite(LEDPin, LOW);
    LEDState=0;
    Blynk.virtualWrite(V0,LOW);
    LEDState=0;
  }
}
buttonOld=buttonNew;
delay(dt);
}
