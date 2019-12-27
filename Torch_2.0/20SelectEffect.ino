void SelectEffect (){
  if (Selected[0] == 0){
    strip.FadeInOut(colorListRGB[Selected[1]],10); 
    
  } else if (Selected[0] == 1){
    strip.Cylon(colorListRGB[Selected[1]], 4, 10);
    
  } else if (Selected[0] == 2){ //Twinkle
    strip.Twinkle(colorListRGB[Selected[1]],10,250);
       
  }else if (Selected[0] == 3){ //TwinkleRandom
    strip.Twinkle(colorListRGB[Selected[1]],10,250,1);
    
  }else if (Selected[0] == 4){ //Sparkle
    strip.Sparkle(colorListRGB[Selected[1]],0);
    
  }else if (Selected[0] == 5){ //SparkleRandom
    strip.Sparkle(colorListRGB[Selected[1]],0,1);
    
  }else if (Selected[0] == 6){ //ColorWipe
    strip.colorWipe(colorListRGB[Selected[1]],50);
    
  } else if (Selected[0] == 7){ //RainbowCycle
    strip.rainbowCycle(10);
    
  } else if (Selected[0] == 8){ //TheaterChase
    strip.theaterChase(colorListRGB[Selected[1]]);
    
  } else if (Selected[0] == 9){ //TheaterChaseRainbow
    strip.theaterChase(colorListRGB[Selected[1]],1);
    
  } else if (Selected[0] == 10){ //Fire
    strip.fireSpiral(NumCols);
    
  } else if (Selected[0] == 11){ //Ice Fire
    strip.fireSpiral(NumCols,1,100,175);
      
  } else if (Selected[0] == 12){ //Meteor Rain
    strip.meteorRainSpiral(colorListRGB[Selected[1]],NumCols);
  
  } else if (Selected[0] == 13){ //Rain without wind
    strip.rainSpiral(colorListRGB[Selected[1]],0,NumCols);
  
  }else if (Selected[0] == 14){ //Marble
    strip.rollingMarble(10);
  
  }
}
