#include <ESP8266WiFi.h>;
 
#define ledPin D4
#define ProgramStringLengthMax 20

char programm;

int port = 5333;
WiFiServer server(port);
 
void setup() {
 
  Serial.begin(115200);
  
  pinMode(ledPin,OUTPUT);
    
  delay(1000);

  WifiSetup();
  
  digitalWrite(ledPin, HIGH);
}

WiFiClient client;

void loop(void) {
       
  digitalWrite(ledPin, HIGH);
  delay(500);

  programm = readDataFromClient();
 
  digitalWrite(ledPin, LOW);
  delay(500);
}
