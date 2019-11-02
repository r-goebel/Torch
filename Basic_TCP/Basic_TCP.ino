#include <ESP8266WiFi.h>;
 
#define ledPin D4
#define bufferSize 10
 
const char* ssid = "<>";
const char* password =  "<>";

int port = 5333;

char programm='initial';


long clientMessage = 0;
 
WiFiServer server(port);
 
void setup() {
 
  Serial.begin(115200);
  
  pinMode(ledPin,OUTPUT);
    
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting..");
  }
 
  Serial.print("Connected to WiFi. IP:");
  Serial.println(WiFi.localIP());
 
  server.begin();
  Serial.print("Connect to IP:");
  Serial.print(WiFi.localIP());
  Serial.print("on port");
  Serial.println(port);
  
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

// Checks for user input, and saves to programm array
char readDataFromClient() {
              
  byte i = 0;
  char incomingMessage[bufferSize];
  
  if (!client.connected()){ // try to connect to a new client
    clientMessage = 0;
    client = server.available();
  } else {                  // read data from the connected client
    if (clientMessage == 0){            
      client.print("Welcome.");
      clientMessage = 1;
    }
    if (clientMessage == 1){
      client.print("Please select Programm:");
      clientMessage = 2;
    }
    if (client.available() > 0) {    
        while (client.available() > 0 && i < bufferSize) {
          delay(10);     
          incomingMessage[i] = client.read();
          i++;
        }           
        if (incomingMessage == "Fire"){
          programm = 'Fire';
        }else{
          programm = 'Else';
        }
        client.println("Succesfully selected programm.");
        delay(10);
        clientMessage = 1;
    }
  }
    return programm;
}
