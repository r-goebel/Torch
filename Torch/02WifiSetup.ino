
//WiFi settings are defined in seperate file according to:
//const char* ssid = "<>";
//const char* password =  "<>";


void WifiSetup(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting..");
  }
 
  Serial.print("Connected to WiFi.");
 
  server.begin();
  Serial.print("Connect to IP: ");
  Serial.print(WiFi.localIP());
  Serial.print(" on port ");
  Serial.println(port);
}
