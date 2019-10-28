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

//******
