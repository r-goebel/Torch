#include <Adafruit_NeoPixel.h>
#include "font.h"
typedef uint32_t color32_t;
// Pattern types supported:
enum  pattern { NONE, RAINBOW_CYCLE, THEATER_CHASE, COLOR_WIPE, SCANNER, FADE, RANDOM_FADE, SMOOTH, ICON, TEXT, RANDOM_FADE_SINGLE, PLASMA, FILL, RANDOM };
// Patern directions supported:
enum  direction { FORWARD, REVERSE };

class NeoPatterns : public Adafruit_NeoPixel
{
  public:
    NeoPatterns(uint16_t pixels, uint8_t pin, uint8_t type, void (*callback)());

    void Update();
    void Reverse();
    void None(uint8_t interval = 40);
    void Stop(uint8_t interval = 40);
    void RainbowCycle(uint8_t interval, direction dir = FORWARD);
    void RainbowCycleUpdate();
    void TheaterChase(uint32_t color1, uint32_t color2, uint8_t interval, direction dir = FORWARD);
    void TheaterChaseUpdate();
    void ColorWipe(uint32_t color, uint8_t interval, direction dir = FORWARD);
    void ColorWipeUpdate();
    void Scanner(uint32_t color1 = 16711680, uint8_t interval = 40, bool colorful = false, bool spiral = false);
    void ScannerUpdate();
    void Fade(uint32_t color1, uint32_t color2, uint16_t steps, uint8_t interval, direction dir = FORWARD);
    void FadeUpdate();
    void RandomFade(uint8_t interval = 100);
    void RandomFadeUpdate();
    void RandomFadeSingle(uint8_t interval = 100, uint8_t speed = 5);
    void RandomFadeSingleUpdate();
    void RandomBuffer();
    void Random();
    void Smooth(uint8_t wheelSpeed = 16, uint8_t smoothing = 80, uint8_t strength = 50, uint8_t interval = 40);
    void SmoothUpdate();
    void Icon(uint8_t fontchar, String iconcolor = "#FFFFFF", uint8_t interval = 30);
    void IconUpdate();
    void IconComplete();
    void Plasma(float phase = 0, float phaseIncrement = 0.08, float colorStretch = 0.11, uint8_t interval = 60); // 0.08 and 0.11   // 0.03 und 0.3
    void PlasmaUpdate();

    void SetColor1(uint32_t color);
    void SetColor2(uint32_t color);
    //Utilities
    void ColorSet(uint32_t color);
    void ColorSetParameters(String parameters);
    uint8_t Red(uint32_t color);
    uint8_t Green(uint32_t color);
    uint8_t Blue(uint32_t color);
    uint32_t Wheel(byte WheelPos);
    uint8_t numToSpiralPos(int num);
    uint8_t xyToPos(int x, int y);
    uint8_t xyToSimplePos(int x, int y);
    uint8_t charxyToPos(int x, int y);
    uint8_t numToPos(int num);
    uint8_t getAverage(uint8_t array[], uint8_t i, int x, int y);
    uint32_t parseColor(String value);
  private:

    // Member Variables:
    pattern ActivePattern;       // which pattern is running
    pattern SavedPattern;
    direction Direction;         // direction to run the pattern
    direction SavedDirection;

    unsigned long Interval;       // milliseconds between updates
    unsigned long SavedInterval;
    unsigned long lastUpdate;     // last update of position

    uint32_t Color1, Color2;      // What colors are in use
    uint32_t SavedColor1;
    uint16_t TotalSteps;      // total number of steps in the pattern
    uint16_t SavedTotalSteps;
    uint16_t Index;      // current step within the pattern
    uint16_t SavedIndex;
    uint8_t Every;                // Turn every "Every" pixel in Color1/Color2

    byte wPos;
    bool colorful;
    bool spiral;
    uint8_t wPosSlow;
    uint8_t WheelSpeed;
    uint8_t Smoothing;
    uint8_t Strength;
    uint8_t movingPoint_x;
    uint8_t movingPoint_y;
    uint8_t *pixelR;
    uint8_t *pixelG;
    uint8_t *pixelB;
    uint8_t *pixelR_buffer;
    uint8_t *pixelG_buffer;
    uint8_t *pixelB_buffer;

    uint8_t textposition;
    uint8_t charposition;
    String Text1;

    uint8_t FontChar;

    float PlasmaPhase;
    float SavedPlasmaPhase;
    float PlasmaPhaseIncrement;
    float SavedPlasmaPhaseIncrement;
    float PlasmaColorStretch;
    float SavedPlasmaColorStretch;

    uint32_t DimColor(uint32_t color);
    void Increment();
    void (*OnComplete)();      // Callback on completion of pattern

    // Convenient 2D point structure
    struct Point {
      float x;
      float y;
    };


};
