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
  strip.setBrightness(5);
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
  //Fire(); //noch anpassen
  //meteorRain(255,255,255,4,64,true,30); //noch anpassen
  Rain(false);
}

void setAll(byte red, byte green, byte blue){
  for (int i = 0; i<=NumPixel; i++){
    strip.setPixelColor(i,red,green,blue);
  }
}

//********************EFFECTS********************

//******Fade in and out

void FadeInOut(byte red, byte green, byte blue){
  float r, g, b;
     
  for(int k = 0; k < 256; k++) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    strip.show();
    delay(1);
  }
     
  for(int j = 255; j >= 0; j=j-2) {
    r = (j/255.0)*red;
    g = (j/255.0)*green;
    b = (j/255.0)*blue;
    setAll(r,g,b);
    strip.show();
    delay(1);
  }
}

//******Cyclon/Scanner
void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int k = 0; k < NumPixel-EyeSize-2; k++) {
    setAll(0,0,0);
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
    setAll(0,0,0);
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

//******Twinkle
void Twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
 
  for (int i=0; i<Count; i++) {
     strip.setPixelColor(random(NumPixel),red,green,blue);
     strip.show();
     delay(SpeedDelay);
     if(OnlyOne) {
      setAll(0,0,0);
     }
   }
 
  delay(SpeedDelay);
}

//******TwinkleRandom
void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
 
  for (int i=0; i<Count; i++) {
     strip.setPixelColor(random(NumPixel),random(0,255),random(0,255),random(0,255));
     strip.show();
     delay(SpeedDelay);
     if(OnlyOne) {
       setAll(0,0,0);
     }
   }
 
  delay(SpeedDelay);
}

//******Sparkle
void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(NumPixel);
  strip.setPixelColor(Pixel,red,green,blue);
  strip.show();
  delay(SpeedDelay);
  strip.setPixelColor(Pixel,0,0,0);
}

//******Color Wipe
void colorWipe(byte red, byte green, byte blue, int SpeedDelay) {
  for(uint16_t i=0; i<NumPixel; i++) {
      strip.setPixelColor(i, red, green, blue);
      strip.show();
      delay(SpeedDelay);
  }
}

//******Rainbow Cycle
void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NumPixel; i++) {
      c=Wheel(((i * 256 / NumPixel) + j) & 255);
      strip.setPixelColor(i, *c, *(c+1), *(c+2));
    }
    strip.show();
    delay(SpeedDelay);
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
 
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}

//******Theater Chase
void theaterChase(byte red, byte green, byte blue, int SpeedDelay) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NumPixel; i=i+3) {
        strip.setPixelColor(i+q, red, green, blue);    //turn every third pixel on
      }
      strip. show();
     
      delay(SpeedDelay);
     
      for (int i=0; i < NumPixel; i=i+3) {
        strip.setPixelColor(i+q, 0,0,0);        //turn every third pixel off
      }
    }
  }
}

//******Theater Chase Rainbow
void theaterChaseRainbow(int SpeedDelay) {
  byte *c;
 
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < NumPixel; i=i+3) {
          c = Wheel( (i+j) % 255);
          strip.setPixelColor(i+q, *c, *(c+1), *(c+2));    //turn every third pixel on
        }
        strip.show();
       
        delay(SpeedDelay);
       
        for (int i=0; i < NumPixel; i=i+3) {
          strip.setPixelColor(i+q, 0,0,0);        //turn every third pixel off
        }
    }
  }
}

//******Fire 
//Based on https://github.com/FastLED/FastLED/blob/master/examples/Fire2012/Fire2012.ino
// Recommended 30-100 frames per second, meaning an interframe delay of about 10-35 milliseconds.
// COOLING: How much does the air cool as it rises?
//          Less cooling = taller flames.  More cooling = shorter flames.
//          Default 50, suggested range 20-100 
// SPARKING: What chance (out of 255) is there that a new spark will be lit?
//           Higher chance = more roaring fire.  Lower chance = more flickery fire.
//           Default 120, suggested range 50-200.

void Fire() {
  int Cooling = 75;
  int Sparking = 145;
  int SpeedDelay = 15;
  byte heat[NumPixel];
  int cooldown;
 
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NumPixel; i++) {
    cooldown = random(0, ((Cooling * 10) / NumPixel) + 2);
   
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
 
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little 
  for( int k= 1; k <= NumPixel-17; k++) {
    if (heat[k+16] == 0){
      heat[k] = 0;
    }
    else{
        heat[k] = ((heat[k + 16] + heat[k + 15] + heat[k + 17]) / 3)*0.95;
    }
  }
   
  // Step 3.  Randomly ignite new 'sparks' near the bottom (near bottom = first four rows --> Pixel 300-252)
  if( random(255) < Sparking ) {
    int y = random(252,300);
    //heat[y] = heat[y] + random(160,255);
    heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j <=NumPixel; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  strip.show();
  delay(SpeedDelay);
}

void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    strip.setPixelColor(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    strip.setPixelColor(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    strip.setPixelColor(Pixel, heatramp, 0, 0);
  }
}


//******Meteor Rain //(red=255,green=255,blue=255,size=4,TrailDecay=64,RandomDecay=true,SpeedDelay=30) (Decay=Zerfall)
void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  setAll(0,0,0);

  int start = random(15);
     
  for(int i = start; i < NumPixel*2; i=i+16) { //NumPixel*2, damit genug zeit zum Ausfadenist
   
   
    // fade brightness all LEDs one step
    for(int j=start; j<NumPixel; j=j+16) {
      if( (!meteorRandomDecay) || (random(10)>5) ) { //wenn nicht Zufälliger Zerfall gewählt ist, oder in 50% der Fälle
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
   
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i < NumPixel) && ((i-j*16)>=0) ) {
        strip.setPixelColor((i-j*16), red, green, blue);
      }
    }
   
    strip.show();
    delay(SpeedDelay);
  }
}

void fadeToBlack(int ledNo, byte fadeValue) {
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
   
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
   
    strip.setPixelColor(ledNo, r,g,b);
}

//******Rain
    
void Rain(boolean WindOn){
  int ChanceNew = 145;
  int Cooling = 75;
  int cooldown;
  byte rain[NumPixel];
  int wind = 0;

  if (WindOn){
    wind=1;
  }
  
  //Copy each Pixel to next row
  for(int i = NumPixel-1;i > 15;i--){
    rain[i] = rain[i-16 + wind];
  }

  //delete first row
  for (int i=0; i<17; i++){
    rain[i] = 0;
  }

  //seed some new drops in first row
    if( random(255) < ChanceNew ) {
    int i = random(0,15);
    rain[i] = 255;
    }

  //set pixel to desired color
  for (int i = 0; i<NumPixel; i++){
    strip.setPixelColor(i, 0, rain[i]/2, rain[i]);
  }
  strip.show();
  delay(30);
}
