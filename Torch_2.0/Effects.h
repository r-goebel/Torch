
#ifndef Effects_h
#define Effects_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

//Supported effects
enum effect {Fade_InOut, Cylon_Scanner, Twinkle_, Sparkle_, Rainbow_Cycle};

//Supported directions:
enum  direction { FORWARD, REVERSE };

class Effects : public Adafruit_NeoPixel //Class Effects includes class Adafruit_Neopixel
{
  public: 
    Effects(uint16_t pixels, uint8_t pin, uint8_t type);

    //public effects:
    void Update();
    void FadeInOut(uint32_t color1, uint8_t interval, direction dir = FORWARD);
    void FadeInOutUpdate();
    void Cylon(uint32_t color1, uint8_t EyeSize, uint8_t interval);
    void CylonUpdate();
    void Twinkle(uint32_t color1, int count, uint8_t interval, bool randomColor = 0);
    void TwinkleUpdate();
    void Sparkle(uint32_t color1, uint8_t interval, bool randomColor = 0);
    void SparkleUpdate();
    void rainbowCycle(uint8_t interval, direction dir = FORWARD);
    void rainbowCycleUpdate();

    //helper functions
    uint8_t Red(uint32_t color);
    uint8_t Green(uint32_t color);
    uint8_t Blue(uint32_t color);
    uint32_t Wheel(byte WheelPos);

  private:
    effect ActiveEffect;       // which pattern is running
    direction Direction;       // direction to run the pattern
    
    //Definition of private variables:
    unsigned long Interval;         // milliseconds between updates
    unsigned long Interval_Initial; //Storage for initial interval
    unsigned long lastUpdate;       // last update of position
    unsigned long ReturnDelay;      //Delay before direction reversal
    uint16_t Index;                 // current step within the pattern
    uint16_t TotalSteps;            // total number of steps in the pattern
  
    uint32_t Color1, Color2;
    uint8_t r, g, b;
    uint8_t red, green, blue;
    bool RandomColor;               //1, if random color selection is on

    uint8_t SizeEffect;             //number of Pixel for the effect
    int Positions[];                //Array to store positions, length equals Effectsize

    //Definition of privat helper functions:
    void Increment();
    void IncrementChangingDirections();
};



#endif
