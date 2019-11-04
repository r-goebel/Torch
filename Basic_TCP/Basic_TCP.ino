#include <ESP8266WiFi.h>;
 
#define ledPin D4

byte EffectLengthMax=20;

char* effect;
char* effectList[] = { "Fade", "Cyclon", "Twinkle", "TwinkleRandom", "Sparkle", "ColorWipe", "RainbowCycle", "TheaterChase", "TheaterChaseRainbow", "Fire", "MeteorRain", "Rain", "Plasma"};
int NumberEffects = 13;
byte NumberEffectSelected;

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
  NumberEffectSelected = readDataFromClient(NumberEffectSelected);
 
  digitalWrite(ledPin, LOW);
  delay(500);
}
