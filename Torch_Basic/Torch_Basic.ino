//Board: Wemos D1 R2 & mini
//Uploadspeed:115200

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PixelPin D2

int NumPixel = 300;
int ROWS = 19;
int COLS = 16;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NumPixel, PixelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  strip.begin();
  strip.setBrightness(10);
  strip.show();

}

void loop() {
  // put your main code here, to run repeatedly:
  //FadeInOut(255, 0, 0); // red
  //CylonBounce(255, 0, 0, 4, 10, 50);
  //Twinkle(255,0,0,10,100,false);
  //TwinkleRandom(20,100,false);
  //Sparkle(255,255,255,0);
  //colorWipe(0,255,0,50);
  //rainbowCycle(20);
  //theaterChase(255,0,0,50);
  //theaterChaseRainbow(50);
  Fire(); 
  //meteorRain(255,255,255,4,64,true,30); 
  //Rain(false);
  //Plasma();
}

void setAll(byte red, byte green, byte blue){
  for (int i = 0; i<=NumPixel; i++){
    strip.setPixelColor(i,red,green,blue);
  }
}
