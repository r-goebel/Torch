//Board: Wemos D1 R2 & mini
//Uploadspeed:115200

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PixelPin D2

int NumPixel = 300;

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
  FadeInOut(255, 0, 0); // red
  FadeInOut(0, 255, 0); // green
  CylonBounce(255, 0, 0, 4, 10, 50);

}

//********************EFFECTS********************

//******Fade in and out

void FadeInOut(byte red, byte green, byte blue){
  float r, g, b;
     
  for(int k = 0; k < 256; k++) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    for (int i = 0; i<=NumPixel; i++){
      strip.setPixelColor(i,r,g,b);
    }
    strip.show();
    delay(1);
  }
     
  for(int j = 255; j >= 0; j=j-1) {
    r = (j/255.0)*red;
    g = (j/255.0)*green;
    b = (j/255.0)*blue;
    for (int i = 0; i<=NumPixel; i++){
      strip.setPixelColor(i,r,g,b);
    }
    strip.show();
    delay(1);
  }
}

//******Cyclon/Scanner
void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int k = 0; k < NumPixel-EyeSize-2; k++) {
    for (int i = 0; i<=NumPixel; i++){
      strip.setPixelColor(i,0,0,0);
    }
    strip.setPixelColor(k, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      strip.setPixelColor(k+j, red, green, blue);
    }
    strip.setPixelColor(k+EyeSize+1, red/10, green/10, blue/10);
    strip.show();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int k = NumPixel-EyeSize-2; k > 0; k--) {
    for (int i = 0; i<=NumPixel; i++){
      strip.setPixelColor(i,0,0,0);
    }
    strip.setPixelColor(k, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      strip.setPixelColor(k+j, red, green, blue);
    }
    strip.setPixelColor(k+EyeSize+1, red/10, green/10, blue/10);
    strip.show();
    delay(SpeedDelay);
  }
 
  delay(ReturnDelay);
}
