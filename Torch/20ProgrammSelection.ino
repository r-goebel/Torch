
byte ProgrammSelection (char* programm){
  if (programm == "Fade"){
    FadeInOut(255, 0, 0); // red
  } else if (programm == "Cyclon"){
    CylonBounce(255, 0, 0, 4, 10, 50);
  } else if (programm == "Twinkle"){
    Twinkle(255,0,0,10,100,false);
  }else if (programm == "TwinkleRandom"){
    TwinkleRandom(20,100,false);
  }else if (programm == "Sparkle"){
    Sparkle(255,255,255,0);
  }else if (programm == "ColorWipe"){
    colorWipe(0,255,0,50);
  }else if (programm == "RainbowCycle"){
    rainbowCycle(20);
  }else if (programm == "TheaterChase"){
    theaterChase(255,0,0,50);
  }else if (programm == "TheaterChaseRainbow"){
    theaterChaseRainbow(50);
  }else if (programm == "Fire"){
    Fire(); 
  }else if (programm == "MeteorRain"){
    meteorRain(255,255,255,4,64,true,30); 
  }else if (programm == "Rain"){
    Rain(false);
  }else if (programm == "Plasma"){
    Plasma();
  }else{
    Twinkle(255,0,0,10,100,false);
  }
}
