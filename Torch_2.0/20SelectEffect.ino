void SelectEffect (){
  if (Selected[0] == 0){
    strip.FadeInOut(colorListRGB[Selected[1]],10); 
    
  } else if (Selected[0] == 1){
    strip.Cylon(colorListRGB[Selected[1]], 4, 10);
    
  } else if (Selected[0] == 2){
    strip.Twinkle(colorListRGB[Selected[1]],10,100);
       
  }else if (Selected[0] == 3){
    strip.Twinkle(colorListRGB[Selected[1]],10,100,1);
    
  }else if (Selected[0] == 4){
    strip.Sparkle(colorListRGB[Selected[1]],0);
    
  }else if (Selected[0] == 5){
    strip.Sparkle(colorListRGB[Selected[1]],0,1);
  }  
}
