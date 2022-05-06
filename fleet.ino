#include <Keypad.h>
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
int data;
char keys[n_rows][n_cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
 
byte colPins[n_rows] = {D3, D2, D1, D0};
byte rowPins[n_cols] = {D7, D6, D5, D4};
 
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, n_rows, n_cols); 
const byte n_rows = 4;
const byte n_cols = 4;
char ssid[] = "POCO X2";
char pass[] = "23456789";  
WiFiClient  client;
unsigned long myChannelNumber =1428089; // Channel ID here
const int FieldNumber = 1;
const char * myWriteAPIKey = "SQYXFCUJW88QHLZ4"; 
 
void setup(){
   pinMode(A0,INPUT);  
  Serial.begin(115200);
   WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  
}
 
void loop(){
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
  char myKey = myKeypad.getKey();
 
  if (myKey != NULL){
    Serial.print("Key pressed: ");
    data = myKey;
    Serial.println(myKey);
  }
   ThingSpeak.writeField(myChannelNumber,7,data,myWriteAPIKey);
  
}
