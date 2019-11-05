//Board: Wemos D1 R2 & mini
//Uploadspeed:115200

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PixelPin D2

int NumPixel = 300;
int ROWS = 19;
int COLS = 16;

byte EffectLengthMax=20;
char* effect;
char* effectList[] = {"Fade","Cyclon","Twinkle","TwinkleRandom","Sparkle","ColorWipe","RainbowCycle","TheaterChase","TheaterChaseRainbow","Fire","MeteorRain","Rain","Plasma"};
int NumberEffects = 13;
int NumberEffectSelected = 9;
int NumberEffectSelectedNew = 9;
bool ChangeEffect = 0;

int colorDefault[] = {0, 128, 255};
char* colorList[] ={"red","green","blue"};
int NumberColors = 3;
int colorListRGB[][3] = {{255,0,0},
                            {0,255,0},
                            {0,0,255}};
int ChangeColor = 0;

int NumbersSelected[][2] = {9,0};;
int NumbersSelectedNew[][2] = {9,0};

int SelectedEffect;
int SelectedColor;



int port = 5333;
WiFiServer server(port);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NumPixel, PixelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  delay(1000);

  WifiSetup();
  
  strip.begin();
  strip.setBrightness(10);
  strip.show();

  Serial.println("finished setup");
}

WiFiClient client;

void loop() {
  ChangeEffect = readDataFromClient();
  if (ChangeEffect){
    setAll(0,0,0);
    ChangeEffect = 0;
    ChangeColor = 0;
  }
  SelectedColor = NumbersSelected[0][1];
  SelectedEffect = NumbersSelected[0][0];
  EffectSelection();
}
