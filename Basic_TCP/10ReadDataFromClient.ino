
long clientMessage = 0;   //to indicate, which messages were already sent to client
byte i;

// Checks for user input, and saves to programm array
byte readDataFromClient(byte NumberEffectSelectedIn) {
             
  // if no client is connected, try to connect to a new client
  if (!client.connected()){ 
    clientMessage = 0;
    client = server.available();
    NumberEffectSelected = NumberEffectSelected;
  } 

  // if client is connected read data from the connected client
  else {
    //if client is new, sent welcome messages                  
    if (clientMessage == 0){            
      client.println("Welcome.");
      client.println("For help type 'help'");
      clientMessage = 1;
    }
    
    //if client already got welcome message or selected programm
    if (clientMessage == 1){
      client.print("Please select Programm: ");
      clientMessage = 2;
    }

    //Read message from client
    if (client.available() > 0) {
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
      
      //react to client message
      if (strcmp(incomingMessage, "help") == 0){                 //Compares to strings
        Serial.println("Client is asking for help.");
        client.println("Available effects:");
        for (i=0;i<NumberEffects;i++){
          client.println(effectList[i]);
        }
        clientMessage = 1;
      }else {
          int Match = 0;
          for (i=0;i<NumberEffects;i++){
            if (strcmp(incomingMessage,effectList[i]) == 0){
              client.println("Succesfully selected effect.");
              Serial.println("Succesfully selected effect.");
              effect = effectList[i];
              NumberEffectSelected = i;
              Serial.print("effect: ");
              Serial.println(effect);
              Match = 1;
            }
          }
          if (Match == 0){
            client.println("Effect unknown.");
            Serial.println("Effect unknown.");
            NumberEffectSelected = NumberEffectSelectedIn;
          } 
          
          delay(10);
          clientMessage = 1;
      }
    }
  }
    return NumberEffectSelected;
}
