
//#include "Arduino.h"
//#include <Adafruit_NeoPixel.h>
#include "Effects.h"

Effects::Effects(uint16_t pixels, uint8_t pin, uint8_t type) :
  Adafruit_NeoPixel(pixels, pin,type)
{
}

void Effects::Update(){
  if ((millis() - lastUpdate) > Interval) // time to update
  {
    lastUpdate = millis();
    switch (ActiveEffect)
    {
      case Fade_InOut:
        FadeInOutUpdate();
        break;
      case Cyclon_Scanner:
        CyclonUpdate();
        break;
      case Twinkle_:
        TwinkleUpdate();
        break;
      case Sparkle_:
        SparkleUpdate();
        break;
      case Rainbow_Cycle:
        rainbowCycleUpdate();
        break;
    }
  } else {
    delay(1);
  }
}

void Effects::Increment(){
  if (Direction == FORWARD){
    Index++;
    if (Index >= TotalSteps){
      Index = 0;
    }
  }
  else { // Direction == REVERSE
    --Index;
    if (Index <= 0){
      Index = TotalSteps - 1;
    }
  }
}

void Effects::IncrementChangingDirections(){
  Interval = Interval_Initial;
  if (Direction == FORWARD){
    Index++;
    if (Index > TotalSteps){
      Direction = REVERSE;
      Interval = ReturnDelay;
    }
  }
  else { // Direction == REVERSE
    --Index;
    if (Index <= 0){
      Direction = FORWARD;
      Interval = ReturnDelay;
    }
  }
}

/******************  Effects  ******************/

void Effects::FadeInOut(uint32_t color1, uint8_t interval, direction dir){
  ActiveEffect = Fade_InOut;
  Interval_Initial = interval;
  ReturnDelay = interval;
  TotalSteps = 256;
  Index = 0;
  Color1 = color1;
  Direction = dir;
}

void Effects::FadeInOutUpdate(){
  r = (Index/256.0) * Red(Color1);
  g = (Index/256.0) * Green(Color1);
  b = (Index/256.0) * Blue(Color1);

  fill(Color(r,g,b),0,(numPixels()-1));

  //if (Index == (TotalSteps-1) && Direction == FORWARD){        //Change direction if highest or lowest color value is reached
  //  Direction = REVERSE;
  //} else if (Index == 1 && Direction == REVERSE){
  //  Direction = FORWARD;
  //}
  show();
  IncrementChangingDirections(); 
}

void Effects::Cyclon(uint32_t color1, uint8_t EyeSize, uint8_t interval){
  ActiveEffect = Cyclon_Scanner;
  Interval_Initial = interval;
  Direction = FORWARD;
  Color1 = color1;
  SizeEffect = EyeSize;
  TotalSteps = numPixels()-SizeEffect-2;
  ReturnDelay = 5*interval;
  Index = 0;
}

void Effects::CyclonUpdate(){

    clear(); //reset all pixels
    
    for (int i=Index+1; i<=Index+SizeEffect;i++){   //does not work using "fill"
      setPixelColor(i,Color1);
    }
    setPixelColor(Index, Red(Color1)/10, Green(Color1)/10, Blue(Color1)/10);              //To set one pixel in front and after eye to color/10
    setPixelColor(Index+SizeEffect+1, Red(Color1)/10, Green(Color1)/10, Blue(Color1)/10);
      
    show();
    IncrementChangingDirections();
}

void Effects::Twinkle(uint32_t color1, int count, uint8_t interval, bool randomColor){
  ActiveEffect = Twinkle_;
  Interval = interval;
  Index = 0;
  Color1 = color1;
  SizeEffect = count;
  RandomColor = randomColor;
  int Positions[SizeEffect]; //Array to store positions, length equals Effectsize
}

void Effects::TwinkleUpdate(){

  //select random Pixel & store Position in Position-Array as first value
  Positions[0] = random(numPixels());
  
  //Switch on selected pixel, Store position in Position-Array on first position
  setPixelColor(Positions[0],Color1);
    
  //Switch off  pixel that has been on the longest (=last entry in Position-Array)
  setPixelColor(Positions[SizeEffect-1],0,0,0);
    
  //Move all positions in Positionsarry one entry backwards, starting from last entry to avoid overwriting
  for (int i = SizeEffect-1;i>0;i--){
    if (RandomColor){
      Color1 = Wheel(random(256));
    }
    setPixelColor(Positions[0],Color1);
    Positions[i] = Positions[i-1];
  }
  show();
}

void Effects::Sparkle(uint32_t color1, uint8_t interval, bool randomColor){
  ActiveEffect = Sparkle_;
  Interval = interval;
  Index = 0;
  Color1 = color1;
  RandomColor = randomColor;
}

void Effects::SparkleUpdate(){
  clear(); 
  if (RandomColor){
    Color1 = Wheel(random(256));
  }
  setPixelColor(random(numPixels()),Color1);
  show();
}

void Effects::rainbowCycle(uint8_t interval, direction dir){
  ActiveEffect = Rainbow_Cycle;
  Interval = interval;
  TotalSteps = 255;
  Index = 0;
  Direction = dir;
}

void Effects::rainbowCycleUpdate(){
  for (int i = 0; i < numPixels(); i++)  {
    setPixelColor(i, Wheel(((i * 256 / numPixels()) + Index) & 255));
  }
  show();
  Increment();
}

/******************  Helper functions  ******************/
uint32_t Effects::Wheel(byte WheelPos){
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85)  {
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }  else if (WheelPos < 170)  {
    WheelPos -= 85;
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }  else  {
    WheelPos -= 170;
    return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

// Returns the Red component of a 32-bit color
uint8_t Effects::Red(uint32_t color)
{
  return (color >> 16) & 255;
}

// Returns the Green component of a 32-bit color
uint8_t Effects::Green(uint32_t color)
{
  return (color >> 8) & 255;
}

// Returns the Blue component of a 32-bit color
uint8_t Effects::Blue(uint32_t color)
{
  return color & 255;
}
