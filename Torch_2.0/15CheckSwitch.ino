
 
bool SwitchState;

bool CheckSwitch(){
  //Check switch state
    SwitchState = digitalRead(PinSwitch);
    
  //if Sensor value exceeds limit
  if(SwitchState == HIGH){
    //Change Effect randonly
    SelectedNew[0] = random(NumberEffects-1);
    SelectedNew[1] = random(NumberColors-1);
    EffectChange = 1;
  }
    
  else{
    EffectChange = 0;
  }

  return EffectChange;
}
