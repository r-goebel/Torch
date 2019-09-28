//Board: Wemos D1 R2 & mini
//Upload speed:115200

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            4  //enspricht D2 auf Wemos ESP

#define NUMPIXELS      300


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 1000; 
int currenttime=2000;
int previoustime=0;
int j=0;
int k=0;


void setup() {
  Serial.begin(9600);
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(10);
}


void loop() {  
  
  if (currenttime-previoustime>50){  
    previoustime=currenttime;
    for(int i=0;i<(NUMPIXELS/8);i++){
      for (int k=0;k<8;k++){
        if (i==0){
          pixels.setPixelColor(k, Wheel(j)); 
        }
        else{
          pixels.setPixelColor((k+i*8), Wheel(j+i));  
        } 
      }
    }
    pixels.show();
    
    if (j<255){
      j=j+1;
    }
    else{
      j=0;
    }

  }
  currenttime=millis();
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return pixels.Color(WheelPos * 3, 255 - WheelPos*3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
