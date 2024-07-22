#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "base64.h"

// Setup WiFi network
const char* ssid = "*********";
const char* password = "**********";

// read sensor
const int sensorPin = A0;
int speakerPin = D5;
int state = 0;

// Twilio Parameter
String account_sid = "*********************************";
String auth_token = "********************************";
String from = "*************";
String to = "***********";
String body = "Ada penyusup masuk kerumah mu!";

void setup() {
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
  
  pinMode(sensorPin, INPUT);
  pinMode(speakerPin, OUTPUT);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to WiFi");
}
 
void loop() {
  state = analogRead(sensorPin);

  if (state < 500) {
    if (WiFi.status() == WL_CONNECTED) { // Check the current connection status
      WiFiClient client;
      HTTPClient http;
     
      String link = "http://rifqi123.pythonanywhere.com/sendwa?account_sid=" + account_sid + "&auth_token=" + auth_token + "&to_wa=" + to + "&from_wa=" + from + "&body_message=" + body;
        
      http.begin(client, link); // Updated to use WiFiClient
      int httpCode = http.GET();
      Serial.println(httpCode);
        
      if (httpCode > 0) { // Check for the returning code
        String payload = http.getString();
        Serial.println(link);
        Serial.println(httpCode);
        Serial.println(payload);
      } else {
        Serial.println("Error on HTTP request");
      }
      http.end();
    }
    digitalWrite(speakerPin, HIGH);
    delay(3000);
    digitalWrite(speakerPin, LOW);
    delay(1000);
  }
  delay(200);
}
