//Board: Wemos D1 R2 & mini
//Upload speed:115200

#include <Bounce2.h>
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
int pinvalue;
Bounce debouncer = Bounce();

NeoPatterns strip = NeoPatterns(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800, &StripComplete);
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, Pixel_PIN, NEO_GRB + NEO_KHZ800);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 16, PIN,
                            NEO_MATRIX_TOP  + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB            + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  pinMode(PRO_PIN,INPUT_PULLUP);
  debouncer.attach(PRO_PIN); //zum entprellen des Schalters
  debouncer.interval(10); // interval in ms
  
  strip.begin(); // This initializes the NeoPixel library.
  matrix.begin();
  strip.setBrightness(10);
  matrix.setBrightness(10);
  strip.RainbowCycle(5);//Default effect
  strip.show();
  matrix.show();
}


void loop() {  
  debouncer.update();
  strip.Update();
  if (pinvalue != debouncer.read()){ //prüfe ob Pin status sich geändert hat
    pinvalue = debouncer.read();     // wenn ja, gespeicherten Status überschreiben
    if (pinvalue == LOW){           //Prüfe, ob Pin Status LOw, also Taster gedrückt
      program = program + 1;        //wenn ja, ein programm weiter
      selectProgram(program);       //und dann programm einschalten
    } 
    if (program >= 10){             //wenn maximale Pogrammzahl erreicht, wieder vorne Anfangen
      program = 0;
    }//wenn nein, einfach weiter
  }
  Serial.print("program");          //zum debuggen
  Serial.print(program);
  Serial.print("Pin");
  Serial.println(pinvalue);
}

void selectProgram(int program) {
  if (program == 1){
    strip.RainbowCycle(3);
  }
  else if (program == 2){
    strip.TheaterChase(strip.Color(random(0,255), random(0,255), random(0,255)), strip.Color(random(0,255), random(0,255), random(0,255)), 100); //Zufallsfarben
  }
  else if (program ==3){
    for (int i=0; i<=NUMPIXELS; i++){
      strip.setPixelColor(i,strip.Color(0,0,0));
    }
    strip.show();
    strip.ColorWipe(strip.Color(random(0,255), random(0,255), random(0,255)), 50); //Zufallsfarbe, pixel werden nach einander eingeschaltet, wenn durchgelaufen wieder von vorne anfangen
  }
  else if (program == 4){
    strip.Scanner(strip.Color(255, 0, 0), 20, true); //dreier Schlange rennt durch
  }
  else if (program ==5){
    strip.Fade(strip.Color(random(0,255), random(0,255), random(0,255)), strip.Color(random(0,255), random(0,255), random(0,255)), 200, 100); 
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
  else if (program ==9){
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
