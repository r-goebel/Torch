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
#define PRO_PIN  D6  //Pin für den Taster zur Programmwahl

#define NUMPIXELS      300

int program=0;

NeoPatterns strip = NeoPatterns(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800, &StripComplete);
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, Pixel_PIN, NEO_GRB + NEO_KHZ800);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
                            NEO_MATRIX_TOP  + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB            + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  pinMode(PRO_PIN,INPUT_PULLUP);
  
  strip.begin(); // This initializes the NeoPixel library.
  matrix.begin();
  strip.setBrightness(10);
  matrix.setBrightness(10);
  strip.RandomFade(); //Default effect
  strip.show();
  matrix.show();
}


void loop() {  
  strip.Update();
  //if (digitalRead(PRO_PIN)==LOW){ //Prüfe, ob Taster zur Programm wahl gedrückt wurde/gedrückt ist
    //program = program + 1;  //wenn ja, ein programm weiter
    //selectProgram(program); //und dann programm einschalten
  //} 
  //if (program ==3){
    //program == 0;
  //}//wenn nein, einfach weiter
}

void selectProgram(int program) {
  if (program == 1){
    strip.RainbowCycle(3);
  }
  else if (program == 2){
    strip.TheaterChase(strip.Color(255, 0, 0), strip.Color(0, 0, 255), 100); //blau,rot (Zufallsfarben?)
  }
  else if (program ==3){
    strip.ColorWipe(strip.Color(255, 0, 0), 100); //rot, pixel werden nach einander eingeschaltet (Zufallsfarbe?)
  }
  else if (program == 4){
    strip.Scanner(strip.Color(255, 0, 0), 20, true); //dreier Schlange rennt durch
  }
  else if (program ==5){
    strip.Fade(strip.Color(255, 0, 0), strip.Color(0, 0, 255), 200, 100); //blau,rot
  }
  else if (program == 6){
    strip.RandomFadeSingle();
  }
  else if (program ==7){
    strip.Smooth(16, 80, 50, 40);
  }
  else if (program ==8){
    strip.Plasma(); //läuft nur auf den ersten ca 64 pixeln
  }
  else {
    strip.RandomFade();
  }
}

void StripComplete() {
  if (false)
  {
    strip.IconComplete();
  }
  return;
}
