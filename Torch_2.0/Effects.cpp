
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
  Interval = interval;
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

  if (Index == (TotalSteps-1) && Direction == FORWARD){        //Change direction if highest or lowest color value is reached
    Direction = REVERSE;
  } else if (Index == 1 && Direction == REVERSE){
    Direction = FORWARD;
  }
  show();
  Increment(); 
}

void Effects::Cyclon(uint32_t color1, uint8_t EyeSize, int interval){
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
