
#ifndef Effects_h
#define Effects_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

//Supported effects
enum effect {Fade_InOut, Rainbow_Cycle};

//Supported directions:
enum  direction { FORWARD, REVERSE };

class Effects : public Adafruit_NeoPixel
{
  public: 
    Effects();

    //public effects:
    void Update();
    void FadeInOut(byte red, byte green, byte blue);
    void FadeInOutUpdate();
    void rainbowCycle(uint8_t interval, direction dir = FORWARD);
    void rainbowCycleUpdate();

    //helper functions
    uint32_t Wheel(byte WheelPos);

  private:
    effect ActiveEffect;       // which pattern is running
    direction Direction;         // direction to run the pattern
    
    //Definition of private variables:
    unsigned long Interval;         // milliseconds between updates
    unsigned long lastUpdate;     // last update of position
    uint16_t Index;      // current step within the pattern
    uint16_t TotalSteps;      // total number of steps in the pattern

    //Definition of privat helper functions:
    void Increment();
};



#endif
