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
  //FadeInOut(255, 0, 0); // red
  //FadeInOut(0, 255, 0); // green
  //CylonBounce(255, 0, 0, 4, 10, 50);
  //Twinkle(255,0,0,10,100,false);
  //TwinkleRandom(20,100,false);
  //Sparkle(255,255,255,0);
  //colorWipe(0,255,0,50);
  //rainbowCycle(20);
  //theaterChase(255,0,0,50);
  //theaterChaseRainbow(50);
  //Fire(55,120,15);
  //BouncingBalls(255,0,0,3); 

    //byte colors[3][3] = { {0xff, 0,0},
    //                    {0xff, 0xff, 0xff},
    //                    {0   , 0   , 0xff} };

  //BouncingColoredBalls(3, colors);
  meteorRain(255,255,255,10,64,true,30); 
}

void setAll(byte red, byte green, byte blue){
  for (int i = 0; i<=NumPixel; i++){
    strip.setPixelColor(i,red,green,blue);
  }
}

//********************EFFECTS********************

//******Fade in and out --Über Helligkeit???

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
     
  for(int j = 255; j >= 0; j=j-1) {
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
void Fire(int Cooling, int Sparking, int SpeedDelay) {
  //static byte heat[NumPixel];
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
  for( int k= NumPixel - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
   
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < NumPixel; j++) {
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

//******Bouncing Ball
void BouncingBalls(byte red, byte green, byte blue, int BallCount) {
  float Gravity = -9.81;
  int StartHeight = 1;
 
  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];
 
  for (int i = 0 ; i < BallCount ; i++) {  
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i)/pow(BallCount,2);
  }

  while (true) {
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i]/1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i]/1000;
 
      if ( Height[i] < 0 ) {                      
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();
 
        if ( ImpactVelocity[i] < 0.01 ) {
          ImpactVelocity[i] = ImpactVelocityStart;
        }
      }
      Position[i] = round( Height[i] * (NumPixel - 1) / StartHeight);
    }
 
    for (int i = 0 ; i < BallCount ; i++) {
      strip.setPixelColor(Position[i],red,green,blue);
    }
   
    strip.show();
    setAll(0,0,0);
  }
}

//******Multi Color Bouncing Ball
void BouncingColoredBalls(int BallCount, byte colors[][3]) {
  float Gravity = -9.81;
  int StartHeight = 1;
 
  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];
 
  for (int i = 0 ; i < BallCount ; i++) {  
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i)/pow(BallCount,2);
  }

  while (true) {
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i]/1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i]/1000;
 
      if ( Height[i] < 0 ) {                      
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();
 
        if ( ImpactVelocity[i] < 0.01 ) {
          ImpactVelocity[i] = ImpactVelocityStart;
        }
      }
      Position[i] = round( Height[i] * (NumPixel - 1) / StartHeight);
    }
 
    for (int i = 0 ; i < BallCount ; i++) {
      strip.setPixelColor(Position[i],colors[i][0],colors[i][1],colors[i][2]);
    }
   
    strip.show();
    setAll(0,0,0);
  }
}

//******Meteor Rain
void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  setAll(0,0,0);
 
  for(int i = 0; i < NumPixel+NumPixel; i++) {
   
   
    // fade brightness all LEDs one step
    for(int j=0; j<NumPixel; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
   
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <NumPixel) && (i-j>=0) ) {
        strip.setPixelColor(i-j, red, green, blue);
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
