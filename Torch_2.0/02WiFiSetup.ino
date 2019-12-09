
//WiFi settings are defined in seperate file according to:
//const char* ssid = "<>";
//const char* password =  "<>";

int connectionInterval = 120000;
int startSetup;

void WifiSetup(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  startSetup = millis();
  
  while (WiFi.status() != WL_CONNECTED && millis()- startSetup <= connectionInterval) {
    delay(500);
    Serial.println("Connecting..");
  }

  if (WiFi.status() == WL_CONNECTED){
    Serial.print("Connected to WiFi.");
   
    server.begin();
    Serial.print("Connect to IP: ");
    Serial.print(WiFi.localIP());
    Serial.print(" on port ");
    Serial.println(port);
  }
  else{
    Serial.println("Not connected to Wifi");
  }
}
