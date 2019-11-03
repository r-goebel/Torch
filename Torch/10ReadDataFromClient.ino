
long clientMessage = 0;   //to indicate, which messages were already sent to client
byte i;
String incomingMessage;   //stores incoming message of client
char incomingChar;        //incoming characters of client
byte programmKnown;

// Checks for user input, and saves to programm array
char* readDataFromClient(char* programmIn) {
             
  // if no client is connected, try to connect to a new client
  if (!client.connected()){ 
    clientMessage = 0;
    client = server.available();
    programm = programmIn;
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
        incomingMessage = "";   
        while (client.available() > 0 && i < ProgrammLengthMax) {
          delay(10);     
          
          incomingChar = client.read();
          
          if (incomingMessage == "\cr" || incomingMessage == "\r"|| incomingMessage == "\n"){
            incomingMessage += '\0';                    //Adds character to string
            i = ProgrammLengthMax;
            Serial.println("check");
            client.flush();
          }
          incomingMessage += incomingChar;
          i++;
       }                    
      
      //react to client message
      if (incomingMessage.startsWith("help")){                 //Compares to strings
        client.println("Available effects:\n Fade,\n Cyclon,\n Twinkle,\n TwinkleRandom,\n Sparkle,\n ColorWipe,\n RainbowCycle,\n TheaterChase,\n TheaterChaseRainbow,\n Fire,\n MeteorRain,\n Rain,\n Plasma");
        clientMessage = 1;
      }else {
        programmNew = TranslateString(incomingMessage);
        if (programmNew == "Init"){
          client.println("Effect unknown.");
          Serial.println("Effect unknown.");
          programm = programmIn;
        } else {
          client.println("Succesfully selected effect.");
          Serial.println("Succesfully selected effect.");
          incomingMessage.toCharArray(programmNew,incomingMessage.length());
          Serial.print("programmNew: ");
          Serial.println(programmNew);
        }
          delay(10);
          clientMessage = 1;
      }
    }
  }
    return programm;
}
