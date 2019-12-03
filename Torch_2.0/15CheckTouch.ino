
 
long SensorValue;

bool CheckTouch(){
  //Check sensor value
    SensorValue = sensor.capacitiveSensor(5);
    Serial.println(SensorValue);

  //if Sensor value exceeds limit
  if(SensorValue >= 1000){
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
