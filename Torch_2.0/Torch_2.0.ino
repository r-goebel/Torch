//Board: Wemos D1 R2 & mini
//Uploadspeed:115200

//Include necessary libraries
#include <ESP8266WiFi.h>
#include <Effects.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

//Definition of Neopixelstrip-Variables:
#define PixelPin D2
int NumPixel = 300;
int NumRows = 19;
int NumCols = 16;
Effects strip = Effects(NumPixel, PixelPin, NEO_GRB + NEO_KHZ800);

//Definition of possible effects and colors
char* effectList[] = {"fade","cylon","twinkle", "twinkle random", "sparkle", "sparkle random", "color wipe", "rainbow cycle", "theater", "theater rainbow", "fire", "ice fire", "meteor rain", "rain", "marble", "heart beat"};
int ColorSelection[] = {1,1,1,0,1,0,1,0,1,0,0,0,1,1,0,1}; //1 if color selection for corresponding Effect possible
int NumberEffects = 16;
char* colorList[] ={"red","yellow","green","cyan","blue","magenta","white"};
int colorListRGB[7] = {strip.Color(255,0,0),  //red
                       strip.Color(255,255,0),//yellow
                       strip.Color(0,255,0),  //green
                       strip.Color(0,255,255),//cyan
                       strip.Color(0,0,255),  //blue
                       strip.Color(255,0,255),//magenta
                       strip.Color(255,255,255)};//white
                       
int NumberColors = 7; 

//Definition of various variables
int colorDefault = 1;         //default color if nothing is selected by client
int Selected[] = {1,0};       //initial definition of selected effect and color
int SelectedNew[] = {random(0,NumberEffects),random(0,NumberColors)};    //initial definition of new selected effect and color   
bool EffectChange = 1;        //variable indication change in effect (0=no change, 1=change), initially one change necessary  
int EffectLengthMax = 20;     //Length of longes effect-name in effectList

//Definition of Wifi variables (ssid and password are defined in external file)
int port = 5333;
WiFiServer server(port);

//Definition of Switch
#define PinSwitch D6
int intervalSwitch = 500; //interval in which no new Switch is allowed
int lastSwitch;

void setup() {
  Serial.begin(115200);

  delay(1000);

  WifiSetup();
  
  //initialization of strip
  strip.begin();
  strip.setBrightness(20); //maximum 20 is possible, 25 should work as well, not sure
  strip.show();
}

WiFiClient client;

void loop() {
  //Read input of client if availabel
  EffectChange = ReadClient(EffectChange);


  //if no input was recived from client, check switch
  if (EffectChange == 0 && millis()-lastSwitch > intervalSwitch){
    EffectChange = CheckSwitch();

       if (EffectChange == 1){
        lastSwitch = millis();
       }
  }

  //client selected new effect: replace effect and color in "Selected", initialize new effect if needed, reset "EffectChange"
  if (EffectChange == 1){
    Serial.println("EffectChange noticed");
    Selected[0] = SelectedNew[0];
    Selected[1] = SelectedNew[1];
    EffectChange = 0;
    strip.clear();
    //Initialization
    SelectEffect();
  }
  //client did not select anything new or no client is availabel: just update effect
  else{
    strip.Update();
  }
}
