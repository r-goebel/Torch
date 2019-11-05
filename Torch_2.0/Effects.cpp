
//#include "Arduino.h"
//#include <Adafruit_NeoPixel.h>
#include "Effects.h"

Effects::Effects() :
  Adafruit_NeoPixel()
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

/******************  Effects  ******************/

void Effects::FadeInOut(byte red, byte green, byte blue){
  ActiveEffect = Fade_InOut;
  
  
}

void Effects::FadeInOutUpdate(){
  
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
