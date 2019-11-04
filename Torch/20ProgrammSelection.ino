
void EffectSelection (byte NumberEffectSelected){
  if (NumberEffectSelected == 0){
    FadeInOut(255, 0, 0); // red
    
  } else if (NumberEffectSelected == 1){
    CylonBounce(255, 0, 0, 4, 10, 50);
    
  } else if (NumberEffectSelected == 2){
    Twinkle(255,0,0,10,100,false);
    
  }else if (NumberEffectSelected == 3){
    TwinkleRandom(20,100,false);
    
  }else if (NumberEffectSelected == 4){
    Sparkle(255,255,255,0);
    
  }else if (NumberEffectSelected == 5){
    colorWipe(0,255,0,50);
    
  }else if (NumberEffectSelected == 6){
    rainbowCycle(20);
    
  }else if (NumberEffectSelected == 7){
    theaterChase(255,0,0,50);
    
  }else if (NumberEffectSelected == 8){
    theaterChaseRainbow(50);
    
  }else if (NumberEffectSelected == 9){
    Fire(); 
    
  }else if (NumberEffectSelected == 10){
    meteorRain(255,255,255,4,64,true,30); 
    
  }else if (NumberEffectSelected == 11){
    Rain(false);
    
  }else if (NumberEffectSelected == 12){
    Plasma();
    
  }else{ //Just to be sure
    Twinkle(255,0,0,10,100,false);
    
  }
}
