//Board: Wemos D1 R2 & mini
//Upload speed:115200

#include <Adafruit_NeoPixel.h>
#include "Adafruit_NeoMatrix.h"
#include <Adafruit_GFX.h>
#include "NeoPatterns.h"  //includes several Patterns, which can be used instead of codeing it 
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN      D2  //enspricht D2 auf Wemos ESP

#define NUMPIXELS      300


NeoPatterns strip = NeoPatterns(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800, &StripComplete);
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, Pixel_PIN, NEO_GRB + NEO_KHZ800);

//Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
//                            NEO_MATRIX_TOP  + NEO_MATRIX_RIGHT +
//                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
//                            NEO_GRB            + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  strip.begin(); // This initializes the NeoPixel library.
  //matrix.begin();
  strip.setBrightness(10);
  //matrix.setBrightness(10);
  strip.setPixelColor(15,45,45,45); //Default effect
  strip.show();
  //matrix.show();
   strip.RandomFade(3);
}


void loop() {  
  strip.Update();
}

void StripComplete() {
  if (false)
  {
    strip.IconComplete();
  }
  return;
}
