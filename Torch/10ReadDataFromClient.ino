
long clientMessage = 0;   //to indicate, which messages were already sent to client
byte i;
String incomingMessage;   //stores incoming message of client
char incomingChar;        //incoming characters of client

// Checks for user input, and saves to programm array
char readDataFromClient() {
             
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
        while (client.available() > 0 && i < ProgramStringLengthMax) {
          delay(10);     
          
          incomingChar = client.read();

          if (incomingChar == '\n' || incomingChar == '\r'){
            incomingMessage += '\0';                    //Adds character to string
            i = ProgramStringLengthMax;
          } else {
            incomingMessage += incomingChar;            //Adds character to string
            i++;
          }
        }                     
      Serial.println(incomingMessage);
      
      //react to client message
      if (incomingMessage == "help"){                 //Compares to strings
        client.println("Possible programms: Fire, MeteorRain");
        clientMessage = 1;
      }else {
        if (incomingMessage == "Fire"){
        programm = 'Fire';
      }else{
        programm = 'Else';
      }
        client.println("Succesfully selected programm.");
        delay(10);
        clientMessage = 1;
      }
      //delete message
      incomingMessage = "";
    }
  }
    return programm;
}
