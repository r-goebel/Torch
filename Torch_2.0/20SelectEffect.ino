void SelectEffect (){
  if (Selected[0] == 0){
    strip.FadeInOut(colorListRGB[Selected[1]],10); 
    
  } else if (Selected[0] == 1){
    strip.Cylon(colorListRGB[Selected[1]], 4, 10);
    
  } else if (Selected[0] == 2){ //Twinkle
    strip.Twinkle(colorListRGB[Selected[1]],10,100);
       
  }else if (Selected[0] == 3){ //TwinkleRandom
    strip.Twinkle(colorListRGB[Selected[1]],10,100,1);
    
  }else if (Selected[0] == 4){ //Sparkle
    strip.Sparkle(colorListRGB[Selected[1]],0);
    
  }else if (Selected[0] == 5){ //SparkleRandom
    strip.Sparkle(colorListRGB[Selected[1]],0,1);
    
  }else if (Selected[0] == 6){ //ColorWipe
    strip.colorWipe(colorListRGB[Selected[1]],50);
    
  } else if (Selected[0] == 7){ //RainbowCycle
    strip.rainbowCycle(10);
  } 
}
