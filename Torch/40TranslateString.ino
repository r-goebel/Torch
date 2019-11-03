
char* TranslateString(String incomingMessage){
  programm = "Init";
  if (incomingMessage.startsWith("Fade")){
    programm = "Fade";
  }
  if (incomingMessage.startsWith("Cyclon")){
    programm = "Cyclon";
  }
  if (incomingMessage.startsWith("Twinkle")){
    programm = "Twinkle";
  }
  if (incomingMessage.startsWith("TwinkleRandom")){
    programm = "TwinkleRandom";
  }
  if (incomingMessage.startsWith("Sparkle")){
    programm = "Sparkle";
  }
  if (incomingMessage.startsWith("ColorWipe")){
    programm = "ColorWipe";
  }
  if (incomingMessage.startsWith("TheaterChase")){
    programm = "TheaterChase";
  }
  if (incomingMessage.startsWith("TheaterChaseRainbow")){
    programm = "TheaterChaseRainbow";
  }
  if (incomingMessage.startsWith("Fire")){
    programm = "Fire";
  }
  if (incomingMessage.startsWith("MeteorRain")){
    programm = "MeteorRain";
  }
  if (incomingMessage.startsWith("Rain")){
    programm = "Rain";
  }
  if (incomingMessage.startsWith("RainbowCycle")){
    programm = "RainbowCycle";
  }
  if (incomingMessage.startsWith("Plasma")){
    programm = "Plasma";
  }
  return programm;
}
