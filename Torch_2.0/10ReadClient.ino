
//Definition of Messages sent to client
char* Messages[] = {"Welcome",
                    "To list available effects, type 'help'.",
                    "Please select effect: ",
                    "Succesfully selected effect.",
                    "Input did not match any effect.",
                    "Do you wish to select color (y/n)?",
                    "Selected random color: ",
                    "Please select color: ",
                    "Succesfully selected color.",
                    "Input did not match any color.",
                    "Effect is changed now.",
                    "Available effects:",
                    "Available colors:",
                    "To list available colors, type 'help'",
                    "Selected random effect: "};

int clientStatus;
int i;
                        
bool ReadClient(bool EffectChange){
  if (!client.connected()){ 
  //no client is connected: try to connect new one, ClientStatus = 0, return to loop
    clientStatus = 0;
    client = server.available();
  }
  else { //client is connected
    
    //New client connected: Welcome-Message-Package, set ClientStatus to 1
    if (clientStatus == 0){
      client.println(Messages[0]);
      client.println(Messages[1]);
      clientStatus = 1;    
    }

    //ClientStatus 1: Ask for effect selection, set ClientStatus to 2
    if (clientStatus == 1){
      client.print(Messages[2]);
      clientStatus = 2;
    }

    //ClientStatus > 2: Read client input
    if (client.available() > 0 && clientStatus > 1) { 
      i = 0;  
      char incomingMessage[EffectLengthMax];  
      while (client.available() > 0 && i < EffectLengthMax) {
        delay(10);     
        incomingMessage[i] = client.read();

        if (incomingMessage[i] == '\n' || incomingMessage[i] == '\r'){
          incomingMessage[i] = '\0';                    //delets last character
          i = EffectLengthMax;
        } 
        i++;
      }

      //Evaluate Message:
       
      //ClientStatus 2: evaluate input of effect
      if (clientStatus == 2){
        //Input equals "help": sent Message 11, print list of effects, set clientStatus to 1
        if (strcmp(incomingMessage, "help") == 0){
          client.println(Messages[11]);
          for (int k=0;k<NumberEffects;k++){
            client.println(effectList[k]);
          }
          client.println("random");
          clientStatus = 1;
        }
        //Input is something else, check list of effects for Match
        else{
          int Match = 0;
          for (int k=0;k<NumberEffects;k++){
          //Input equals effect name: Change value of SelectedNew[0]
            if (strcmp(incomingMessage,effectList[k]) == 0){
              SelectedNew[0] = k;
              Match = 1;
              client.println(Messages[3]);
            }
          }
          //Same for random effect but sent Message 14
          if (strcmp(incomingMessage, "random") == 0){
            SelectedNew[0] = random(NumberEffects-1);
            Match = 1;
            client.print(Messages[14]);
            client.println(effectList[SelectedNew[0]]);
          }
            //selected effect needs color selection: sent Message 5, set clientStatus to 3
            if (ColorSelection[SelectedNew[0]] == 1 && Match == 1){
               client.print(Messages[5]);
              clientStatus = 3;
            }
            
            //selected effect does not need color selection: sent Message 10, set clientStatus to 1
            else if (ColorSelection[SelectedNew[0]] == 0 && Match == 1){
              client.println(Messages[10]);
              clientStatus = 1;
            }

          //Input does not match any effect: sent Message 4&1, set clientSatus to 1
          if (Match == 0){
            client.println(Messages[4]);
            client.println(Messages[1]);
            clientStatus = 1;
          }
        }           
      }//End of if clientStatus = 2
        
      //ClientStatus 3: evaluate input for color-selection (y/n)
      else if (clientStatus == 3){
        
        //Input equals "n": Change value in SelectNew[1] to radom color, sent Message 6&10, chnage EffectChange to 1, set clientStatus to 1
        if (strcmp(incomingMessage, "n") == 0){
          SelectedNew[1] = random(NumberColors-1);
          client.print(Messages[6]);
          client.println(colorList[SelectedNew[1]]);
          client.println(Messages[10]);
          EffectChange = 1;
          clientStatus = 1;
        }
        
        //Input equals "y": sent Message 13&7, set clientStatus to 4
        else if (strcmp(incomingMessage, "y") == 0){
          client.println(Messages[13]);
          client.print(Messages[7]);
          clientStatus = 4;
        }

        //Input does not match y or n: sent specific Message and Message 5 
        else {
          client.println("Unknown input.");
          client.println(Messages[5]);            
        }
      }//End of if clientStatus = 3
        
      //ClientStatus 4: evaluate input of color
      else if (clientStatus = 4){
        
        //Input equals "help": sent Message 12&7, print list of colors
        if (strcmp(incomingMessage, "help") == 0){
          client.println(Messages[12]);
          for (int k=0;k<NumberColors;k++){
            client.println(colorList[k]);
          }
          client.println("random");
          client.print(Messages[7]);
        }

        //Input is something else, check list of colors for Match
        else{
          int Match = 0;
          for (int k=0;k<NumberColors;k++){
          //Input equals color name: Change value of SelectedNew[1], sent Message 8&10, chnage EffectChange to 1,set clientStatus to 1
            if (strcmp(incomingMessage,colorList[k]) == 0){
              SelectedNew[1] = k;
              Match = 1;
              client.println(Messages[8]);
              client.println(Messages[10]);
              EffectChange = 1;
              clientStatus = 1;
            }
          }
          //Same for random color but send Message 6&10
          if (strcmp(incomingMessage, "random") == 0){
            SelectedNew[1] = random(NumberColors-1);
            Match = 1;
            client.print(Messages[6]);
            client.println(colorList[SelectedNew[1]]);
            client.println(Messages[10]);
            EffectChange = 1;
            clientStatus = 1;
          }
          //Input does not match any color: sent Message 9&13&7
          if (Match == 0){
            client.println(Messages[9]);
            client.println(Messages[13]);
            client.print(Messages[7]);
          }
        }          
      }//End of if clientStatus = 4
    }//End of if client.available and clientStatus > 1
  }//end of else (client connected)
  
  //return EffectChange (only set to 1 if effect/color was changed, otherwise equals input value)
  return EffectChange;
}
