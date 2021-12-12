#include <Arduino.h>

//Include necessary libraries
//#include <ESP8266WiFi.h>
#include <Homie.h>
#include <Effects.h>
#include <ArduinoOTA.h>

//Definition of Neopixelstrip-Variables:
#define PixelPin D2
int NumPixel = 300;
int NumRows = 19;
int NumCols = 16;
Effects strip = Effects(NumPixel, PixelPin, NEO_GRB + NEO_KHZ800);

//Definition of HomieNode
HomieNode EffectNode("EffectNode", "EffectNode", "Effect");
HomieNode ColorNode("ColorNode", "ColorNode", "Color");
HomieNode PowerNode("PowerNode","powerNode","Power");
HomieNode RestartNode("RestartNode", "RestartNode","Restart");

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

bool powerOn = true;
bool restartOn = true;

//Definition of Switch
#define PinSwitch D6
int intervalSwitch = 500; //interval in which no new Switch is allowed
int lastSwitch;

//++++++++++++++++++++++++++++++++++++
//Homie-Loop Functions
//++++++++++++++++++++++++++++++++++++
bool effectHandler(const HomieRange& range, const String& effect){
  //effect in Liste raussuchen
  for (int i=0; i<NumberEffects; i++) {
    if (effect == effectList[i]) {
      SelectedNew[0] = i;
      break;
    }
    else {
      SelectedNew[0] = 0;
    }
  }
  EffectChange = 1;
  EffectNode.setProperty("effect").send(effect);

  return true;
}

bool colorHandler(const HomieRange& range, const String& color){
  //color in Liste raussuchen
  for (int i=0; i<NumberColors; i++) {
    if (color == colorList[i]) {
      SelectedNew[1] = i;
      break;
    }
    else {
      SelectedNew[1] = 0;
    }
  }
  EffectChange = 1;
  ColorNode.setProperty("color").send(color);

  return true;
}


bool powerHandler(const HomieRange& range, const String& value){
  if (value == "false"){
    powerOn = false;
    strip.clear();
    strip.show();
  } else {
    powerOn = true;
    EffectChange = 1;
  }
  Serial.println("PowerOn: " + String(powerOn));
  PowerNode.setProperty("poweron").send(value);

  return true;
}

//++++++++++++++++++++++++++++++++++++
//OTA Functions
//++++++++++++++++++++++++++++++++++++
void OTASetup(){
  //Setup off OTA, must be called during setup
  //Equals Basic OTA example
  ArduinoOTA.onStart([]() {
  String type;
  if (ArduinoOTA.getCommand() == U_FLASH) {
    type = "sketch";
  } else { // U_FS
    type = "filesystem";
  }

  // NOTE: if updating FS this would be the place to unmount FS using FS.end()
  Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
}

//++++++++++++++++++++++++++++++++++++
//Helperfunctions
//++++++++++++++++++++++++++++++++++++
void SelectEffect (){
  if (Selected[0] == 0){
    strip.FadeInOut(colorListRGB[Selected[1]],10); 
    
  } else if (Selected[0] == 1){
    strip.Cylon(colorListRGB[Selected[1]], 4, 10);
    
  } else if (Selected[0] == 2){ //Twinkle
    strip.Twinkle(colorListRGB[Selected[1]],10,250);
       
  }else if (Selected[0] == 3){ //TwinkleRandom
    strip.Twinkle(colorListRGB[Selected[1]],10,250,1);
    
  }else if (Selected[0] == 4){ //Sparkle
    strip.Sparkle(colorListRGB[Selected[1]],0);
    
  }else if (Selected[0] == 5){ //SparkleRandom
    strip.Sparkle(colorListRGB[Selected[1]],0,1);
    
  }else if (Selected[0] == 6){ //ColorWipe
    strip.colorWipe(colorListRGB[Selected[1]],50);
    
  } else if (Selected[0] == 7){ //RainbowCycle
    strip.rainbowCycle(10);
    
  } else if (Selected[0] == 8){ //TheaterChase
    strip.theaterChase(colorListRGB[Selected[1]]);
    
  } else if (Selected[0] == 9){ //TheaterChaseRainbow
    strip.theaterChase(colorListRGB[Selected[1]],1);
    
  } else if (Selected[0] == 10){ //Fire
    strip.fireSpiral(NumCols);
    
  } else if (Selected[0] == 11){ //Ice Fire
    strip.fireSpiral(NumCols,1,100,175);
      
  } else if (Selected[0] == 12){ //Meteor Rain
    strip.meteorRainSpiral(colorListRGB[Selected[1]],NumCols);
  
  } else if (Selected[0] == 13){ //Rain without wind
    strip.rainSpiral(colorListRGB[Selected[1]],0,NumCols);
  
  }else if (Selected[0] == 14){ //Marble
    strip.rollingMarble(10);
  
  }else if (Selected[0] == 15){ //Heart Beat
    strip.heartBeat(colorListRGB[Selected[1]]);
  
  }
}

bool SwitchState;

bool CheckSwitch(){
  //Check switch state
  SwitchState = digitalRead(PinSwitch);
    
  //if Sensor value exceeds limit
  if(SwitchState == HIGH){
    //Change Effect randonly
    SelectedNew[0] = random(NumberEffects-1);
    SelectedNew[1] = random(NumberColors-1);
    EffectChange = 1;
    EffectNode.setProperty("effect").send(effectList[SelectedNew[0]]);
    ColorNode.setProperty("color").send(colorList[SelectedNew[1]]);
  }
    
  else{
    EffectChange = 0;
  }

  return EffectChange;
}

//++++++++++++++++++++++++++++++++++++
//Main Functions
//++++++++++++++++++++++++++++++++++++

void setup() {
  //Homie
  Homie_setFirmware("Torch", "1.0.0"); // The underscore is not a typo! See Magic bytes
  //Homie.setLoopFunction(loopHandler);
  //Node.advertise("PropertyID").setName("PropertyName").setDatatype("datatype").setUnit("unit");
  EffectNode.advertise("effect").setName("Effect").setDatatype("String").settable(effectHandler);
  ColorNode.advertise("color").setName("Color").setDatatype("String").settable(colorHandler);
  PowerNode.advertise("poweron").setName("PowerOn").setDatatype("String").settable(powerHandler);
  RestartNode.advertise("restart").setName("Restart").setDatatype("String");

  Homie.setup();

  OTASetup();
  ArduinoOTA.begin();
  
  Serial.begin(115200);

  delay(1000);

  //initialization of strip
  strip.begin();
  strip.setBrightness(20); //maximum 20 is possible, 25 should work as well, not sure
  strip.show();
}

void loop() {
  //Read input via Homie/Dashboard
  Homie.loop();
  ArduinoOTA.handle();
  
  //get last state after restart
  if (restartOn == true && Homie.isConfigured() && Homie.isConnected()){
    RestartNode.setProperty("restart").send("true"); // send restart notice to node red
    restartOn = false;
    Serial.println("restart initialized");
  }
  

  //if no input was recived from homie, check switch
  if (EffectChange == 0 && millis()-lastSwitch > intervalSwitch){
    EffectChange = CheckSwitch();

       if (EffectChange == 1){
        lastSwitch = millis();
        powerOn = true;
       }
  }

  if (powerOn == true){
    //new effect selected: replace effect and color in "Selected", initialize new effect if needed, reset "EffectChange"
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
}
