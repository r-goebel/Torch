
//#include "Arduino.h"
//#include <Adafruit_NeoPixel.h>
#include "Effects.h"
#include "Marble.h"

Effects::Effects(uint16_t pixels, uint8_t pin, uint8_t type) :
  Adafruit_NeoPixel(pixels, pin,type)
{
  //Allocate a zero initialized block of memory big enough to hold "pixels" uint8_t.
  Positions = ( uint32_t* ) calloc( pixels, sizeof( uint32_t ) );
  Heat = ( uint8_t* ) calloc( pixels, sizeof( uint8_t ) );
  Rain = (bool* ) calloc ( pixels, sizeof( bool ) );
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
      case Cylon_Scanner:
        CylonUpdate();
        break;
      case Twinkle_:
        TwinkleUpdate();
        break;
      case Sparkle_:
        SparkleUpdate();
        break;
      case Color_Wipe:
        colorWipeUpdate();
        break;
      case Rainbow_Cycle:
        rainbowCycleUpdate();
        break;
      case Theater_Chase:
        theaterChaseUpdate();
        break;
      case Fire_Spiral:
        fireSpiralUpdate();
        break;
      case Meteor_Rain_Spiral:
        meteorRainSpiralUpdate();
        break;
      case Rain_Spiral:
        rainSpiralUpdate();
        break;
      case  Rolling_Marble:
        rollingMarbleUpdate();
        break;
    }
  } else {
    delay(1);
  }
}

void Effects::Increment(uint8_t IncrementValue){
  if (Direction == FORWARD){
    Index = Index + IncrementValue;
    if (Index >= TotalSteps){
      Index = 0;
    }
  }
  else { // Direction == REVERSE
    Index = Index - IncrementValue;
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

//******Fade

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

//******Cylon

void Effects::Cylon(uint32_t color1, uint8_t EyeSize, uint8_t interval){
  ActiveEffect = Cylon_Scanner;
  Interval_Initial = interval;
  Direction = FORWARD;
  Color1 = color1;
  SizeEffect = EyeSize;
  TotalSteps = numPixels()-SizeEffect-2;
  ReturnDelay = 5*interval;
  Index = 0;
}

void Effects::CylonUpdate(){

    clear(); //reset all pixels
    
    for (int i=Index+1; i<=Index+SizeEffect;i++){   //does not work using "fill"
      setPixelColor(i,Color1);
    }
    setPixelColor(Index, Red(Color1)/10, Green(Color1)/10, Blue(Color1)/10);              //To set one pixel in front and after eye to color/10
    setPixelColor(Index+SizeEffect+1, Red(Color1)/10, Green(Color1)/10, Blue(Color1)/10);
      
    show();
    IncrementChangingDirections();
}

//******Twinkle

void Effects::Twinkle(uint32_t color1, int count, uint8_t interval, bool randomColor){
  ActiveEffect = Twinkle_;
  Interval = interval;
  Color1 = color1;
  SizeEffect = count;
  Index = 0;
  TotalSteps = SizeEffect+1;
  RandomColor = randomColor;
  Direction = FORWARD;
  // Clear buffer (from previous or different effects)
  for (int i = 0; i < numPixels(); i++){
    Positions[i] = 0;
  }
}

void Effects::TwinkleUpdate(){

  //select random Pixel & store Postition in Position-Array on the Position number "Index"
  Positions[Index] = random(numPixels()); 

  //switch on pixel according the Position stored in Position-Array on "Index"-Position
  if (RandomColor){
    Color1 = Wheel(random(256));
  }
  setPixelColor(Positions[Index],Color1);

  //switch off pixel according the Position stored in Position-Array on "Index+1"-Position
  if (Index == SizeEffect){
    setPixelColor(Positions[0],0,0,0);
  } else {
    setPixelColor(Positions[Index+1],0,0,0);
  }

  //Increase Index by one
  Increment(1);

  show();
 
}

//******Sparkle

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

//******Color Wipe

void Effects::colorWipe(uint32_t color1, uint8_t interval, direction dir){
  ActiveEffect = Color_Wipe;
  Interval = interval;
  TotalSteps = numPixels()*2;
  Color1 = color1;
  Direction = dir;
  Index = 0;
}

void Effects::colorWipeUpdate(){
  //Erst alle an, dann alle aus
  if (Index <numPixels()){ 
    setPixelColor(Index, Color1);
  }else {
    setPixelColor(Index-numPixels(),0,0,0);
  }
  show();
  Increment(1);
}

//******Rainbow Cycle

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
  Increment(1);
}

//******Theater Chase
void Effects::theaterChase(uint32_t color1, bool rainbow, uint32_t color2, uint8_t interval){
  ActiveEffect = Theater_Chase;
  Color1 = color1;
  Color2 = color2;
  Interval = interval;
  Index = 0;
  TotalSteps = numPixels();
  Rainbow = rainbow;
}

void Effects::theaterChaseUpdate(){
  for (int i = 0; i < numPixels(); i++){
    if ((i + Index) % 3 == 0){
      if (Rainbow){
        Color1 = Wheel(((i * 256 / numPixels()) + Index) & 255);
      }
      setPixelColor(i, Color1);
    }
    else
    {
      setPixelColor(i, Color2);
    }
  }
  show();
  Increment(1);
}

//******Fire Spiral (for strip wrapped around something)

//Based on https://github.com/FastLED/FastLED/blob/master/examples/Fire2012/Fire2012.ino
// Recommended 30-100 frames per second, meaning an interframe delay of about 10-35 milliseconds.
// COOLING: How much does the air cool as it rises?
//          Less cooling = taller flames.  More cooling = shorter flames.
//          Default 50, suggested range 20-100 
// SPARKING: What chance (out of 255) is there that a new spark will be lit?
//           Higher chance = more roaring fire.  Lower chance = more flickery fire.
//           Default 120, suggested range 50-200.

void Effects::fireSpiral(uint8_t numcols, uint8_t cooling, uint8_t sparking, uint8_t interval){
  ActiveEffect = Fire_Spiral;
  Interval = interval;
  Cooling = cooling;
  Sparking = sparking;
  NumCols = numcols;
}

void Effects::fireSpiralUpdate(){
 
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < numPixels(); i++) {
    cooldown = random(0, ((Cooling * 10) / numPixels()) + 2);
   
    if(cooldown>Heat[i]) {
      Heat[i]=0;
    } else {
      Heat[i]=Heat[i]-cooldown;
    }
  }
 
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little 
  for( int i= 1; i <= numPixels()-NumCols+1; i++) {
    if (Heat[i+NumCols] == 0){
      Heat[i] = 0;
    }
    else{
        Heat[i] = ((Heat[i + NumCols] + Heat[i + NumCols - 1] + Heat[i + NumCols + 1]) / 3)*0.95;
    }
  }
   
  // Step 3.  Randomly ignite new 'sparks' near the bottom (near bottom = first four rows)
  if( random(255) < Sparking ) {
    int y = random(252,300);
    Heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int i = 0; i <=numPixels(); i++) {
    setPixelHeatColor(i, Heat[i] );
  }

  show();
  
}

//******Meteor Rain (for strip wrapped around something)

void Effects::meteorRainSpiral(uint32_t color1, uint8_t numcols, uint8_t meteorSize, uint8_t trailDecay, bool randomDecay, uint8_t interval){
  ActiveEffect = Meteor_Rain_Spiral;
  Interval = interval;
  Color1 = color1;
  Index = 0;
  TotalSteps = numPixels()*3; //numPixels*3, to ensure enough time for fading to black of all pixels
  Direction = FORWARD;
  SizeEffect = meteorSize;
  TrailDecay = trailDecay;
  RandomDecay = randomDecay; 
  NumCols = numcols;
}

void Effects::meteorRainSpiralUpdate() {  

  //wähle zufälligen pixel in erster Reihe zum starten
  if (Index == 0){
    Pixel = random(15);
  }
   
    // fade brightness all LEDs in selected row one step
    for(int j=Pixel; j<numPixels(); j=j+16) {
      if( (!RandomDecay) || (random(10)>5) ) { //RandomDecay is not selected or with 50% chance
        Serial.print("Fading ");
        Serial.print(j);
        fadeToBlack(j, TrailDecay );        
      }
    }
   
    // draw meteor
    for(int j = 0; j < SizeEffect; j++) {
      if( ( (Pixel+Index) < numPixels()) && (((Pixel+Index)-j*NumCols)>=0) ) {
        setPixelColor(((Pixel+Index)-j*NumCols), Color1);
      }
    }
   
    show();
    Increment(16);
}

//******Rain (for strip wrapped around something)

void Effects::rainSpiral(uint32_t color1, bool wind, uint8_t numcols, uint8_t interval, uint8_t chanceNew){
  ActiveEffect = Rain_Spiral;
  Direction = FORWARD;
  Interval = interval;
  Color1 = color1;
  Wind = wind;
  NumCols = numcols;
  ChanceNew = chanceNew;
}

void Effects::rainSpiralUpdate(){
  clear();
  
  //Copy each Pixel to next row
  for(int i = numPixels()-1;i >= NumCols; i--){
    Rain[i] = Rain[i-NumCols + Wind];
  }

  //delete first row
  for (int i=0; i<NumCols; i++){
    Rain[i] = 0;
  }

  //seed some new drops in first row
  if( random(10) < ChanceNew ) {
    int i = random(0,NumCols);
    Rain[i] = 1;
  }

  //set pixel to desired color
  for (int i = 0; i<numPixels(); i++){
    if (Rain[i]){
      setPixelColor(i, Color1);
    }
  }
  show();
}

//******Rolling Marble

void Effects::rollingMarble(uint32_t color1, uint8_t interval, direction dir) {
  ActiveEffect = Rolling_Marble;
  Index = 0;
  Interval = interval;
  Direction = dir;
  Color1 = color1;
  
  marbleInitialize();
}

void Effects::rollingMarbleUpdate(){
  //separate library due to lots of calculations
  
  clear();
  
  //set Marble pixel
  setPixelColor(MarblePixel, Color1);

  show();
  
  marbleUpdate();

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

//Mapping heat to color
void Effects::setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    setPixelColor(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    setPixelColor(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    setPixelColor(Pixel, heatramp, 0, 0);
  }
}


void Effects::fadeToBlack(int Pixel, uint8_t fadeValue) {

    ColorOld = getPixelColor(Pixel);
    r = (ColorOld & 0x00ff0000UL) >> 16;
    g = (ColorOld & 0x0000ff00UL) >> 8;
    b = (ColorOld & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
   
    setPixelColor(Pixel, r,g,b);
}
