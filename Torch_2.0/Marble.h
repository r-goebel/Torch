#ifndef Marble_h
#define Marble_h

#include "Arduino.h"


class Marble
{
  public: 
    Marble();
    void marbleInitialize();
    void marbleUpdate();
    void physicsUpdate();

    uint32_t MarblePixel;
  
  private:
    
  float Mass;
  float Alpha;
  float PixelDistance;
  float v;
  float Pos;
  float Delta_t, t_last;

  float F_G, F_F, F_Air;
  float a;
  

};

#endif
