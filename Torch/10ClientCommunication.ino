
//******Effect selection
byte clientMessage = 0;   //to indicate, which messages were already sent to client
int i;

// Checks for user input, and saves to programm array
bool readDataFromClient() {
             
  // if no client is connected, try to connect to a new client
  if (!client.connected()){ 
    clientMessage = 0;
    client = server.available();
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
      if (clientMessage == 2){
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
                NumbersSelected[0][0] = i;
                Serial.print("effect: ");
                Serial.println(effectList[i]);
                Match = 1;
                clientMessage = 3;
                colorSelection();
                ChangeEffect = 1;
              }
            }
            if (Match == 0){
              client.println("Effect unknown.");
              Serial.println("Effect unknown."); 
            } 
            
            delay(10);
            clientMessage = 1;
        }
      } //end of if for programm selection
    }
  }
    return ChangeEffect;
}


//******Color selection

bool colorSelection(){
  if (clientMessage == 3){            
    client.println("Do you wish to select color (y/n)?");
    clientMessage = 4;
  }
  if (clientMessage == 5){
    client.println("Available colors:");
    for (i=0;i<NumberColors;i++){
          client.println(colorList[i]);
        }
    client.println("Please select color: ");
    clientMessage = 6;    
  }

  //read message of client
  if (client.available() > 0) {
    i = 0;  
    char incomingMessage[20];  
    while (client.available() > 0 && i < EffectLengthMax) {
      delay(10);     
      
      incomingMessage[i] = client.read();

      if (incomingMessage[i] == '\n' || incomingMessage[i] == '\r'){
        incomingMessage[i] = '\0';                    //delets last character
        i = EffectLengthMax;
      } 
      i++;
    }
    if (clientMessage == 4){
      if (strcmp(incomingMessage,"n") == 0){
        client.println("Selected default color.");
        NumbersSelected[0][1] = 1;
        clientMessage = 1;
      
      } else if (strcmp(incomingMessage,"y") == 0){
        clientMessage = 5;
      }
      
    } else if (clientMessage ==  6){
      int Match = 0;
      for (i=0;i<NumberColors;i++){
        //compare input and possible colors
        //if input equals color set match to 1 and color to selected color
        if (strcmp(incomingMessage,colorList[i]) == 0){
          client.println("Succesfully selected color.");
          Serial.println("Succesfully selected color.");
          Serial.print("color: ");
          Serial.println(colorList[i]);
          NumbersSelected[0][1] = i;
          Match = 1;
          ChangeColor = 1;
        }
      }
      if (Match ==1){
        //input did not match any color
        client.println("Input did not match any color.");
        clientMessage = 5;
      }
    } 
  }
  return ChangeColor;
}
