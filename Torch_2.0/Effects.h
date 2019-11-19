
#ifndef Effects_h
#define Effects_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

//Supported effects
enum effect {Fade_InOut, Cylon_Scanner, Twinkle_, Sparkle_, Color_Wipe, Rainbow_Cycle, Theater_Chase, Fire_Spiral, Meteor_Rain_Spiral, Rain_Spiral, Rolling_Marble};

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
    void colorWipe(uint32_t color1, uint8_t interval, direction dir = FORWARD);
    void colorWipeUpdate();
    void rainbowCycle(uint8_t interval, direction dir = FORWARD);
    void rainbowCycleUpdate();
    void theaterChase(uint32_t color1, bool rainbow = 0, uint32_t color2=Color(0,0,0), uint8_t interval=50);
    void theaterChaseUpdate();
    void fireSpiral(uint8_t numcols, uint8_t cooling = 50, uint8_t sparking = 120, uint8_t interval = 15); //Only possible on Neopixel strip wrapped around something
    void fireSpiralUpdate();
    void meteorRainSpiral(uint32_t color1, uint8_t numcols, uint8_t meteorSize = 4, uint8_t TrailDecay = 64, bool RandomDecay = 1, uint8_t interval = 30); //Only possible on Neopixel strip wrapped around something
    void meteorRainSpiralUpdate();
    void rainSpiral(uint32_t color1, bool wind, uint8_t numcols, uint8_t interval = 50, uint8_t chanceNew = 5);
    void rainSpiralUpdate();
    void rollingMarble(uint8_t interval, direction dir = FORWARD);
    void rollingMarbleUpdate();

    //helper functions
    uint8_t Red(uint32_t color);
    uint8_t Green(uint32_t color);
    uint8_t Blue(uint32_t color);
    uint32_t Wheel(byte WheelPos);
    void setPixelHeatColor(int Pixel, byte temperature);
    void fadeToBlack(int Pixel, uint8_t fadeValue);

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
  
    uint32_t Color1, Color2, ColorOld;
    uint8_t r, g, b;
    uint8_t red, green, blue;
    bool RandomColor;               //1, if random color selection is on
    bool Rainbow;                   //1, if rainbow colors selection is on

    uint8_t SizeEffect;             //number of Pixel for the effect
    uint32_t *Positions;            //Array to store positions, length equals Effectsize
    int Pixel;                      //Pixel to be changed

    int Cooling;                    //How much does the air cool as it rises
    int Sparking;                   //What chance (out of 255) is there that a new spark will be lit
    uint8_t *Heat;                  //Heat of each pixel
    int cooldown;                   //cooldown factor
    byte temperature;               //temperature of a pixel

    uint8_t TrailDecay;             //Fading value for Decay
    bool RandomDecay;               //1 if random Decay is selected
    uint8_t fadeValue;              //Variable for Fading value inside fade to black function

    bool *MeteorPos;

    bool *Rain;                     //Array to store which pixel is switched on
    uint8_t ChanceNew;              //Chance for new drop/pixel
    bool Wind;                      //1 if wind is on

    uint8_t NumCols;                //Number of columns in matrix
    uint8_t IncrementValue;         //Incrementing value

    float Mass;                     //Mass of marble
    float Alpha;                    //angle of strip
    float PixelDistance;            //distance between pixels
    float v;                        // velocity of marble
    float Pos;                      //Position of marble
    float Delta_t, t_last;          //time variables
    float F_G, F_F, F_Air;          //forces: gravity, friction, air resistance
    float a;                        //acceleration

    //Definition of privat helper functions:
    void Increment(uint8_t IncrementValue);
    void IncrementChangingDirections();

    void marblePhysicsUpdate();
};



#endif
