#include "ThingSpeak.h"
#include <WiFi.h>
WiFiClient  client;
const char* ssid = "Royal";  // Enter SSID here
const char* password = "8431868663";  //Enter Password here
// WiFiClient  client;
int turbidity=5;
int turbidity_val=10;
unsigned long myChannelNumber = 2524550;
const char * myWriteAPIKey = "5ESB90ZXDP29OKOE";
String myStatus = "";
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
   ThingSpeak.begin(client);

}

void loop() {
  // put your main code here, to run repeatedly:
  //int turbidity_val = analogRead(turbidity);
  Serial.println(turbidity_val);
  ThingSpeak.setField(1, turbidity_val);
   ThingSpeak.setStatus(myStatus);
    
     int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
 if(x == 200){
    Serial.println("Channel update successful.");
 }
 else{
   Serial.println("Problem updating channel. HTTP error code " + String(x));
 }
  }


