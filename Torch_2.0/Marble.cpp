
#include "Marble.h"

Marble::Marble()
{

}

void Marble::marbleInitialize(){
  Mass = 0.5; //g
  Alpha = 0.04;
  PixelDistance = 500/300; //300 pixel per 5m
  t_last = millis();
  v = 0;
  Pos = 0;
  MarblePixel = 0;
  
  //Color1 = massbasedColor(Mass); 

}

void Marble::marbleUpdate(){

  Delta_t = (millis() - t_last)/1000;
  
  //Determine the current Pixel for marble
  physicsUpdate();

  if (Pos >= PixelDistance/2) {
    MarblePixel++;
    Pos = 0;
  }

  Serial.print("Updated Marble, MarblePixel: ");
  Serial.println(MarblePixel);
}

void Marble::physicsUpdate(){ 
  
  float Gravity = 9.81;   //m/s²
  float Mu = 0.05;        //
  float Cw = 0.45;        //sphere (Reference "Das große Tafelwerk")
  int Rho = 1290;       //g/m³ for air (Reference "Das große Tafelwerk")
  float A = 0.2;          //cm² (shadow surface of sphere with diameter 0.5cm)

  //Calculate weight force
  F_G = Mass * Gravity * sin(Alpha); 

  //Caclulate friction force
  F_F = Mu * Mass * Gravity * cos(Alpha);

  //Calculate air resistance
  F_Air = Cw * A / 1000000 * 0.5 * Rho * pow(v,2); 

  //Calculate current acceleration
  if (v <= 0 ) {
    F_F = F_F * (-1);
    F_Air = F_Air * (-1);
  }
  a = 1/Mass * (F_G-F_F-F_Air); 

  //Calculate current velocity
  v = a * Delta_t + v;  

  Serial.println(v);

  //Calculate current position
  Pos = v * Delta_t + Pos;
  
}
