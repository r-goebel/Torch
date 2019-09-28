#include "NeoPatterns.h"

NeoPatterns::NeoPatterns(uint16_t pixels, uint8_t pin, uint8_t type, void (*callback)()) :
  Adafruit_NeoPixel(pixels, pin, type)
{
  OnComplete = callback;
  //Allocate a zero initialized block of memory big enough to hold "pixels" uint8_t.
  pixelR = ( uint8_t* ) calloc( pixels, sizeof( uint8_t ) );
  pixelG = ( uint8_t* ) calloc( pixels, sizeof( uint8_t ) );
  pixelB = ( uint8_t* ) calloc( pixels, sizeof( uint8_t ) );
  pixelR_buffer = ( uint8_t* ) calloc( pixels, sizeof( uint8_t ) );
  pixelG_buffer = ( uint8_t* ) calloc( pixels, sizeof( uint8_t ) );
  pixelB_buffer = ( uint8_t* ) calloc( pixels, sizeof( uint8_t ) );
}

void NeoPatterns::Update() {
  if ((millis() - lastUpdate) > Interval) // time to update
  {
    lastUpdate = millis();
    switch (ActivePattern)
    {
      case RAINBOW_CYCLE:
        RainbowCycleUpdate();
        break;
      case THEATER_CHASE:
        TheaterChaseUpdate();
        break;
      case COLOR_WIPE:
        ColorWipeUpdate();
        break;
      case SCANNER:
        ScannerUpdate();
        break;
      case FADE:
        FadeUpdate();
        break;
      case RANDOM_FADE:
        RandomFadeUpdate();
        break;
      case RANDOM_FADE_SINGLE:
        RandomFadeSingleUpdate();
        break;
      case SMOOTH:
        SmoothUpdate();
        break;
      case ICON:
        IconUpdate();
        break;
      case PLASMA:
        PlasmaUpdate();
        break;
      case FILL:
        break;
      case RANDOM:
        break;
      case NONE:
        break;
      default:
        break;
    }
  } else {
    delay(1);
  }
}

void NeoPatterns::Increment()
{
  if (Direction == FORWARD)
  {
    Index++;
    if (Index >= TotalSteps)
    {
      Index = 0;
      if (OnComplete != NULL)
      {
        OnComplete(); // call the completion callback
      }
    }
  }
  else // Direction == REVERSE
  {
    --Index;
    if (Index <= 0)
    {
      Index = TotalSteps - 1;
      if (OnComplete != NULL)
      {
        OnComplete(); // call the completion callback
      }
    }
  }
}

void NeoPatterns::Reverse() {
  if (Direction == FORWARD)
  {
    Direction = REVERSE;
    Index = TotalSteps - 1;
  }
  else
  {
    Direction = FORWARD;
    Index = 0;
  }
}

void NeoPatterns::Stop(uint8_t interval) {
  Interval = interval;
  ActivePattern = NONE;
}

void NeoPatterns::None(uint8_t interval) {
  Interval = interval;
  if (ActivePattern != NONE) {
    clear();
    show();
  }
  ActivePattern = NONE;
}

/******************  Effects  ******************/

void NeoPatterns::RainbowCycle(uint8_t interval, direction dir) {
  ActivePattern = RAINBOW_CYCLE;
  Interval = interval;
  TotalSteps = 255;
  Index = 0;
  Direction = dir;
}

void NeoPatterns::RainbowCycleUpdate()
{
  for (int i = 0; i < numPixels(); i++)
  {
    setPixelColor(i, Wheel(((i * 256 / numPixels()) + Index) & 255));
  }
  show();
  Increment();
}

void NeoPatterns::TheaterChase(uint32_t color1, uint32_t color2, uint8_t interval, direction dir) {
  ActivePattern = THEATER_CHASE;
  Interval = interval;
  TotalSteps = numPixels();
  Color1 = color1;
  Color2 = color2;
  Index = 0;
  Direction = dir;
}
void NeoPatterns::TheaterChaseUpdate() {
  for (int i = 0; i < numPixels(); i++)
  {
    if ((i + Index) % 3 == 0)
    {
      setPixelColor(i, Color1);
    }
    else
    {
      setPixelColor(i, Color2);
    }
  }
  show();
  Increment();
}

void NeoPatterns::ColorWipe(uint32_t color, uint8_t interval, direction dir)
{
  ActivePattern = COLOR_WIPE;
  Interval = interval;
  TotalSteps = numPixels();
  Color1 = color;
  Index = 0;
  Direction = dir;
}

// Update the Color Wipe Pattern
void NeoPatterns::ColorWipeUpdate()
{
  setPixelColor(Index, Color1);
  show();
  Increment();
}

// Initialize for a SCANNNER
void NeoPatterns::Scanner(uint32_t color1, uint8_t interval, bool colorful, bool spiral)
{
  ActivePattern = SCANNER;
  Interval = interval;
  TotalSteps = (numPixels() - 1) * 2;
  Color1 = color1;
  Index = 0;
  wPos = 0;
  this->colorful = colorful;
  this->spiral = spiral;
}

// Update the Scanner Pattern
void NeoPatterns::ScannerUpdate()
{
  if (colorful) {
    Color1 = Wheel(wPos);
    if (wPos >= 255) {
      wPos = 0;
    }
    else {
      wPos++;
    }
  }
  for (int i = 0; i < numPixels(); i++)
  {
    int finalpos;
    if (spiral) {
      finalpos = numToSpiralPos(i);
    }
    else
    {
      finalpos = i;
    }
    if (i == Index) // Scan Pixel to the right
    {
      setPixelColor(finalpos, Color1);
    }
    else if (i == TotalSteps - Index) // Scan Pixel to the left
    {
      setPixelColor(finalpos, Color1);
    }
    else // Fading tail
    {
      setPixelColor(finalpos, DimColor(getPixelColor(finalpos)));
    }
  }
  show();
  Increment();

}

void NeoPatterns::Fade(uint32_t color1, uint32_t color2, uint16_t steps, uint8_t interval, direction dir)
{
  ActivePattern = FADE;
  Interval = interval;
  TotalSteps = steps;
  Color1 = color1;
  Color2 = color2;
  Index = 0;
  Direction = dir;
}

// Update the Fade Pattern
void NeoPatterns::FadeUpdate()
{
  // Calculate linear interpolation between Color1 and Color2
  // Optimise order of operations to minimize truncation error
  uint8_t red = ((Red(Color1) * (TotalSteps - Index)) + (Red(Color2) * Index)) / TotalSteps;
  uint8_t green = ((Green(Color1) * (TotalSteps - Index)) + (Green(Color2) * Index)) / TotalSteps;
  uint8_t blue = ((Blue(Color1) * (TotalSteps - Index)) + (Blue(Color2) * Index)) / TotalSteps;

  ColorSet(Color(red, green, blue));
  show();
  Increment();
}

void NeoPatterns::RandomFade(uint8_t interval ) {
  ActivePattern = RANDOM_FADE;
  Interval = interval;
  TotalSteps = 255;
  Index = 0;
}

void NeoPatterns::RandomFadeUpdate() {
  ColorSet(Wheel(Index));
  Increment();
}

void NeoPatterns::RandomFadeSingle(uint8_t interval, uint8_t speed) {
  ActivePattern = RANDOM_FADE_SINGLE;
  Interval = interval;
  TotalSteps = 255;
  Index = 0;
  WheelSpeed = speed;
  RandomBuffer();
}

void NeoPatterns::RandomFadeSingleUpdate() {
  for (int i = 0; i < numPixels(); i++) {
    pixelR_buffer[i] += random(0, random(0, WheelSpeed + 1) + 1); //use buffer red channel for color wheel
    setPixelColor(i, Wheel(pixelR_buffer[i]));
  }
  show();
  Increment();
}

void NeoPatterns::RandomBuffer()
{
  for (int i = 0; i < numPixels(); i++) {
    uint32_t c = Wheel(random(0, 256));
    pixelR_buffer[i] = (uint8_t)(c >> 16);
    pixelG_buffer[i] = (uint8_t)(c >>  8);
    pixelB_buffer[i] = (uint8_t)c;
  }
}

void NeoPatterns::Random()
{
  None(); // Stop all other effects
  ActivePattern = RANDOM;
  for (int i = 0; i < numPixels(); i++) {
    setPixelColor(i, Wheel(random(0, 256)));
  }
  show();
}

void NeoPatterns::Smooth(uint8_t wheelSpeed, uint8_t smoothing, uint8_t strength, uint8_t interval) {
  ActivePattern = SMOOTH;
  Interval = interval;
  Index = 0;
  WheelSpeed = wheelSpeed;
  Smoothing = smoothing;
  Strength = strength;
  movingPoint_x = 3;
  movingPoint_y = 3;
  // Clear buffer (from previous or different effects)
  for (int i = 0; i < numPixels(); i++) {
    pixelR_buffer[i] = 0;
    pixelG_buffer[i] = 0;
    pixelB_buffer[i] = 0;
  }
}

void NeoPatterns::SmoothUpdate() {
  uint32_t c = Wheel(wPos);
  wPosSlow += WheelSpeed;
  wPos = (wPos + (wPosSlow / 10) ) % 255;
  wPosSlow = wPosSlow % 16;

  uint8_t r = (uint8_t)(c >> 16);
  uint8_t g = (uint8_t)(c >>  8);
  uint8_t b = (uint8_t)c;

  movingPoint_x = movingPoint_x + 8 + random(-random(0, 1 + 1), random(0, 1 + 1) + 1);
  movingPoint_y = movingPoint_y + 8 + random(-random(0, 1 + 1), random(0, 1 + 1) + 1);
  if (movingPoint_x < 8) {
    movingPoint_x = 8 - movingPoint_x;
  } else if (movingPoint_x >= 16) {
    movingPoint_x = 22 - movingPoint_x;
  } else {
    movingPoint_x -= 8;
  }

  if (movingPoint_y < 8) {
    movingPoint_y = 8 - movingPoint_y;
  } else if (movingPoint_y >= 16) {
    movingPoint_y = 22 - movingPoint_y;
  } else {
    movingPoint_y -= 8;
  }
  uint8_t startx = movingPoint_x;
  uint8_t starty = movingPoint_y;

  for (int i = 0; i < Strength; i++) {

    movingPoint_x = startx + 8 + random(-random(0, 2 + 1), random(0, 2 + 1) + 1);
    movingPoint_y = starty + 8 + random(-random(0, 2 + 1), random(0, 2 + 1) + 1);

    if (movingPoint_x < 8) {
      movingPoint_x = 8 - movingPoint_x;
    } else if (movingPoint_x >= 16) {
      movingPoint_x = 22 - movingPoint_x;
    } else {
      movingPoint_x -= 8;
    }

    if (movingPoint_y < 8) {
      movingPoint_y = 8 - movingPoint_y;
    } else if (movingPoint_y >= 16) {
      movingPoint_y = 22 - movingPoint_y;
    } else {
      movingPoint_y -= 8;
    }

    if (pixelR[xyToPos(movingPoint_x, movingPoint_y)] < r) {
      pixelR[xyToPos(movingPoint_x, movingPoint_y)]++;
    } else if (pixelR[xyToPos(movingPoint_x, movingPoint_y)] > r) {
      pixelR[xyToPos(movingPoint_x, movingPoint_y)]--;
    }
    if (pixelG[xyToPos(movingPoint_x, movingPoint_y)] < g) {
      pixelG[xyToPos(movingPoint_x, movingPoint_y)]++;
    } else if (pixelG[xyToPos(movingPoint_x, movingPoint_y)] > g) {
      pixelG[xyToPos(movingPoint_x, movingPoint_y)]--;
    }
    if (pixelB[xyToPos(movingPoint_x, movingPoint_y)] < b) {
      pixelB[xyToPos(movingPoint_x, movingPoint_y)]++;
    } else if (pixelB[xyToPos(movingPoint_x, movingPoint_y)] > b) {
      pixelB[xyToPos(movingPoint_x, movingPoint_y)]--;
    }
  }

  movingPoint_x = startx;
  movingPoint_y = starty;

  for (int i = 0; i < numPixels(); i++) {
    pixelR_buffer[i] = (Smoothing / 100.0) * pixelR[i] + (1.0 - (Smoothing / 100.0)) * getAverage(pixelR, i, 0, 0);
    pixelG_buffer[i] = (Smoothing / 100.0) * pixelG[i] + (1.0 - (Smoothing / 100.0)) * getAverage(pixelG, i, 0, 0);
    pixelB_buffer[i] = (Smoothing / 100.0) * pixelB[i] + (1.0 - (Smoothing / 100.0)) * getAverage(pixelB, i, 0, 0);

  }

  for (int i = 0; i < numPixels(); i++) {
    pixelR[i] = pixelR_buffer[i];
    pixelG[i] = pixelG_buffer[i];
    pixelB[i] = pixelB_buffer[i];
    setPixelColor(i, pixelR[i], pixelG[i], pixelB[i]);
  }

  show();
}


/****************** Icon ******************/

void NeoPatterns::Icon(uint8_t fontchar, String iconcolor, uint8_t interval)
{
  // Save last effect, should be called after completion again
  SavedPattern = ActivePattern;
  SavedInterval = Interval;
  SavedTotalSteps = TotalSteps;
  SavedIndex = Index;
  SavedColor1 = Color1;
  SavedDirection  = Direction;
  SavedPlasmaPhase = PlasmaPhase;
  SavedPlasmaPhaseIncrement = PlasmaPhaseIncrement;
  SavedPlasmaColorStretch = PlasmaColorStretch;
  ActivePattern = ICON;
  Interval = interval;
  TotalSteps = 80;
  Index = 80;
  Color1 = parseColor(iconcolor);
  FontChar = fontchar;
  Direction = REVERSE;
}

void NeoPatterns::IconUpdate()
{
  for (int i = 0; i < numPixels(); i++) {
    uint64_t mask = 1LL << (uint64_t)i;

    if ( (font[FontChar]&mask) == 0) {
      setPixelColor(numToPos(i), Color(0, 0, 0)); //bit is 0 at pos i
    } else {
      float _brightness = 1.0 - ( (TotalSteps - Index) * 1.0 / TotalSteps );
      uint8_t _r = (uint8_t)(Color1 >> 16);
      uint8_t _g = (uint8_t)(Color1 >>  8);
      uint8_t _b = (uint8_t)Color1;
      setPixelColor(numToPos(i), Color(_r * _brightness, _g * _brightness, _b * _brightness)); //bit is 1 at pos i
    }
  }
  show();
  Increment();
}

void NeoPatterns::IconComplete()
{
  // Reload last effect
  ActivePattern = SavedPattern;
  Interval = SavedInterval;
  TotalSteps = SavedTotalSteps;
  Index = SavedIndex;
  Color1 = SavedColor1;
  Direction = SavedDirection;
  PlasmaPhase = SavedPlasmaPhase;
  PlasmaPhaseIncrement = SavedPlasmaPhaseIncrement;
  PlasmaColorStretch = SavedPlasmaColorStretch;
}

/****************** Plasma ******************/

// Based upon https://github.com/johncarl81/neopixelplasma
void NeoPatterns::Plasma(float phase, float phaseIncrement, float colorStretch, uint8_t interval)
{
  ActivePattern = PLASMA;
  Interval = interval;
  PlasmaPhase = phase;
  PlasmaPhaseIncrement = phaseIncrement;
  PlasmaColorStretch = colorStretch;
}

void NeoPatterns::PlasmaUpdate()
{
  PlasmaPhase += PlasmaPhaseIncrement;
  int edge = (int)sqrt(numPixels());
  // The two points move along Lissajious curves, see: http://en.wikipedia.org/wiki/Lissajous_curve
  // The sin() function returns values in the range of -1.0..1.0, so scale these to our desired ranges.
  // The phase value is multiplied by various constants; I chose these semi-randomly, to produce a nice motion.
  Point p1 = { (sin(PlasmaPhase * 1.000) + 1.0) * (edge / 2), (sin(PlasmaPhase * 1.310) + 1.0) * (edge / 2) };
  Point p2 = { (sin(PlasmaPhase * 1.770) + 1.0) * (edge / 2), (sin(PlasmaPhase * 2.865) + 1.0) * (edge / 2) };
  Point p3 = { (sin(PlasmaPhase * 0.250) + 1.0) * (edge / 2), (sin(PlasmaPhase * 0.750) + 1.0) * (edge / 2)};

  byte row, col;

  // For each row...
  for ( row = 0; row < edge; row++ ) {
    float row_f = float(row);  // Optimization: Keep a floating point value of the row number, instead of recasting it repeatedly.

    // For each column...
    for ( col = 0; col < edge; col++ ) {
      float col_f = float(col);  // Optimization.

      // Calculate the distance between this LED, and p1.
      Point dist1 = { col_f - p1.x, row_f - p1.y };  // The vector from p1 to this LED.
      float distance1 = sqrt( dist1.x * dist1.x + dist1.y * dist1.y );

      // Calculate the distance between this LED, and p2.
      Point dist2 = { col_f - p2.x, row_f - p2.y };  // The vector from p2 to this LED.
      float distance2 = sqrt( dist2.x * dist2.x + dist2.y * dist2.y );

      // Calculate the distance between this LED, and p3.
      Point dist3 = { col_f - p3.x, row_f - p3.y };  // The vector from p3 to this LED.
      float distance3 = sqrt( dist3.x * dist3.x + dist3.y * dist3.y );

      // Warp the distance with a sin() function. As the distance value increases, the LEDs will get light,dark,light,dark,etc...
      // You can use a cos() for slightly different shading, or experiment with other functions. Go crazy!
      float color_1 = distance1;  // range: 0.0...1.0
      float color_2 = distance2;
      float color_3 = distance3;
      float color_4 = (sin( distance1 * distance2 * PlasmaColorStretch )) + 2.0 * 0.5;

      // Square the color_f value to weight it towards 0. The image will be darker and have higher contrast.
      color_1 *= color_1 * color_4;
      color_2 *= color_2 * color_4;
      color_3 *= color_3 * color_4;
      color_4 *= color_4;

      // Scale the color up to 0..7 . Max brightness is 7.
      //strip.setPixelColor(col + (edge * row), strip.Color(color_4, 0, 0) );

      setPixelColor(xyToPos(row, col), Color(color_1, color_2, color_3));
    }
  }
  show();
}


/******************  Helper functions  ******************/

void NeoPatterns::SetColor1(uint32_t color) {
  Color1 = color;
}
void NeoPatterns::SetColor2(uint32_t color) {
  Color2 = color;
}

// Calculate 50% dimmed version of a color (used by ScannerUpdate)
uint32_t NeoPatterns::DimColor(uint32_t color)
{
  // Shift R, G and B components one bit to the right
  uint32_t dimColor = Color(Red(color) >> 1, Green(color) >> 1, Blue(color) >> 1);
  return dimColor;
}

// Set all pixels to a color (synchronously)
void NeoPatterns::ColorSet(uint32_t color)
{
  for (int i = 0; i < numPixels(); i++)
  {
    setPixelColor(i, color);
  }
  show();
}

void NeoPatterns::ColorSetParameters(String parameters)
{
  None();
  ActivePattern = FILL;
  ColorSet(parseColor(parameters));
}

// Returns the Red component of a 32-bit color
uint8_t NeoPatterns::Red(uint32_t color)
{
  return (color >> 16) & 0xFF;
}

// Returns the Green component of a 32-bit color
uint8_t NeoPatterns::Green(uint32_t color)
{
  return (color >> 8) & 0xFF;
}

// Returns the Blue component of a 32-bit color
uint8_t NeoPatterns::Blue(uint32_t color)
{
  return color & 0xFF;
}

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t NeoPatterns::Wheel(byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85)
  {
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else if (WheelPos < 170)
  {
    WheelPos -= 85;
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  else
  {
    WheelPos -= 170;
    return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

uint8_t NeoPatterns::xyToSimplePos(int x, int y) {
  // Alternating rows
  if (y % 2 == 0) {
    return (y * 8 + x);
  } else {
    return (y * 8 + (7 - x));
  }
}

// Convert x y pixel position to matrix position
uint8_t NeoPatterns::xyToPos(int x, int y) {
  if (y % 2 == 0) {
    return (x + (y * 8));
  } else {
    return ((7 - x) + (y * 8));
  }
}

uint8_t NeoPatterns::charxyToPos(int x, int y) {
  return (y * 8 + x);
}

//convert pixel number to actual 8x8 matrix position
uint8_t NeoPatterns::numToPos(int num) {
  int x = num % 8;
  int y = num / 8;
  return xyToPos(x, y);
}

// Convert pixel number to actual 8x8 matrix position in a spiral
uint8_t NeoPatterns::numToSpiralPos(int num) {
  int edge = (int)sqrt(numPixels());
  int findx = edge - 1; // 7
  int findy = 0;
  int stepsize = edge - 1; // initial value (0..7)
  int stepnumber = 0; // each "step" should be used twice
  int count = -1;
  int dir = 1; // direction: 0 = incX, 1=incY, 2=decX, 3=decY
  if (num < edge) {
    return num;  // trivial
  }
  for (int i = edge; i <= num; i++)
  {
    count++;
    if (count == stepsize) {
      count = 0;
      // Change direction
      dir++;
      stepnumber++;
      if (stepnumber == 2) {
        stepsize -= 1;
        stepnumber = 0;
      }
      if (dir == 4) {
        dir = 0;
      }
    }
    switch (dir) {
      case 0:
        findx++;
        break;
      case 1:
        findy++;
        break;
      case 2:
        findx--;
        break;
      case 3:
        findy--;
        break;
    }
  }
  return xyToPos(findx, findy);
}

uint8_t NeoPatterns::getAverage(uint8_t array[], uint8_t i, int x, int y)
{
  // TODO: This currently works only with 8x8 (64 pixel)!
  uint16_t sum = 0;
  uint8_t count = 0;
  if (i >= 8) { //up
    sum += array[i - 8];
    count++;
  }
  if (i < (64 - 8)) { //down
    sum += array[i + 8];
    count++;
  }
  if (i >= 1) { //left
    sum += array[i - 1];
    count++;
  }
  if (i < (64 - 1)) { //right
    sum += array[i + 1];
    count++;
  }
  return sum / count;
}

uint32_t NeoPatterns::parseColor(String value) {
  if (value.charAt(0) == '#') { //solid fill
    String color = value.substring(1);
    int number = (int) strtol( &color[0], NULL, 16);
    // Split them up into r, g, b values
    int r = number >> 16;
    int g = number >> 8 & 0xFF;
    int b = number & 0xFF;
    return Color(r, g, b);
  }
  return 0;
}
