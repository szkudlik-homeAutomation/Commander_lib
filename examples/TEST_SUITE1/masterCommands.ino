//All commands for 'master'
//COMMAND ARRAY ------------------------------------------------------------------------------

commandList_t masterCommands[] = {
  {"hello",       helloHandler,     "hello"},
  {"set",         setHandler,       "Quick set commands. Help: \"set help\""},
  {"get",         getHandler,       "Quick get commands. Help: \"get help\""},
  {"get int",     getIntHandler,    "get an int"},
  {"set int",     setIntHandler,    "set an int"},
  {"get float",   getFloatHandler,  "get a float"},
  {"set float",   setFloatHandler,  "set a float"},
  {"hidden1",     hiddenHandler,    "-Command hidden from help"},
  {"myint",       setIntHandler,    "try myint=23"},
  {"myfloat",     setFloatHandler,  "try myfloat=23.5"},
  {"set ints",    setIntsHandler,   "set up to four ints"},
  {"set floats",  setFloatsHandler, "set up to four floats"},
  {"set strings", setStringsHandler,"set up to four Strings"},
  {"hidden2",     hiddenHandler,    "-Command hidden from help"},
  {"step",        stepHandler0,      "iterate through several handlers"},
  {"print",        printHandler,      "print something"},
};

/* Command handler template
bool myFunc(Commander &Cmdr){
  //put your command handler code here
  return 0;
}
*/
//Array of function pointers that can be stepped through
cmdHandler handlerArray[] = {
  stepHandler0,
  stepHandler1,
  stepHandler2,
  stepHandler3,
};
uint8_t handlerIndex = 0;

//function to step to the next handler and assign the pointer it to the command list pointer that was called.
void handlerStep(int cmdIdx){
  handlerIndex++;
  if(handlerIndex > 3) handlerIndex = 0;
  masterCommands[cmdIdx].handler = handlerArray[handlerIndex];
}

//Initialisation function that avoids having to forward declare the command array and a size variable.
void initialiseCommander(){
  cmd.begin(&Serial, masterCommands, sizeof(masterCommands))
                                                            .commandPrompt(ON)
                                                            .echo(true)
                                                            .errorMessages(ON)
                                                            .autoChain(ON)
                                                            .setUserString(deviceInfo);
}


//These are the command handlers, there needs to be one for each command in the command array myCommands[]
//The command array can have multiple commands strings that all call the same function
bool helloHandler(Commander &Cmdr){
  Cmdr.print("Hello! this is ");
  Cmdr.println(Cmdr.commanderName);
  Cmdr.print("This is my buffer: ");
  Cmdr.print(Cmdr.bufferString);
  Cmdr.print("This handler was called by command at index ");
  Cmdr.println(Cmdr.getCommandIndex());
  //Cmdr.printDiagnostics();
  return 0;
}

bool setHandler(Commander &Cmdr){
  
  Cmdr.print("This handler was called by command at index ");
  Cmdr.println(Cmdr.getCommandIndex());
  //quickget function
  //Call quickSetHelp() first to handle any help command
  Cmdr.quickSetHelp();
  if( Cmdr.quickSet("int1",   myInt1) )   Cmdr.println("int1 set to " + String(myInt1));
  if( Cmdr.quickSet("int2",   myInt2) )   Cmdr.println("int2 set to " + String(myInt2));
  if( Cmdr.quickSet("float1", myFloat1) ) Cmdr.println("float1 set to " + String(myFloat1));
  if( Cmdr.quickSet("float2", myFloat2) ) Cmdr.println("float2 set to " + String(myFloat2));
  if( Cmdr.quickSet("str1", myString1) ) Cmdr.println("str1 set to " + String(myString1));
  if( Cmdr.quickSet("str2", myString2) ) Cmdr.println("str2 set to " + String(myString2));
  return 0;
}
bool getHandler(Commander &Cmdr){
  
  Cmdr.print("This handler was called by command at index ");
  Cmdr.println(Cmdr.getCommandIndex());
  //quickset function
  //Call quickSetHelp() first to handle any help command
  Cmdr.quickSetHelp();
  Cmdr.quickGet("int1",   myInt1);
  Cmdr.quickGet("int2",   myInt2) ;
  Cmdr.quickGet("float1", myFloat1);
  Cmdr.quickGet("float2", myFloat2) ;
  Cmdr.quickGet("str1", myString1);
  Cmdr.quickGet("str2", myString2) ;
  return 0;
}


bool getIntHandler(Commander &Cmdr){
  
  Cmdr.print("This handler was called by command at index ");
  Cmdr.println(Cmdr.getCommandIndex());
  Cmdr.print("myInt = ");
  Cmdr.println(myInt);
  //Cmdr.printDiagnostics();
  return 0;
}

bool setIntHandler(Commander &Cmdr){
  
  Cmdr.print("This handler was called by command at index ");
  Cmdr.println(Cmdr.getCommandIndex());
  if(Cmdr.getInt(myInt)){
    Cmdr.print("myInt set to ");
    Cmdr.println(myInt);
  }
  //Cmdr.printDiagnostics();
  return 0;
}
bool getFloatHandler(Commander &Cmdr){
  
  Cmdr.print("This handler was called by command at index ");
  Cmdr.println(Cmdr.getCommandIndex());
  Cmdr.print("myFloat = ");
  Cmdr.println(myFloat);
  
  //Cmdr.printDiagnostics();
  return 0;
}

bool setFloatHandler(Commander &Cmdr){
  
  Cmdr.print("This handler was called by command at index ");
  Cmdr.println(Cmdr.getCommandIndex());
  if(Cmdr.getFloat(myFloat)){
    Cmdr.print("myFloat set to ");
    Cmdr.println(myFloat, 4); //print with 4 decimal places
  }
  //Cmdr.printDiagnostics();
  return 0;
}

bool setIntsHandler(Commander &Cmdr){
  Cmdr.print("This handler was called by command at index ");
  Cmdr.println(Cmdr.getCommandIndex());
  //create an array to store any values we find
  int values[4] = {0,0,0,0};

  int itms = Cmdr.countItems();
  Cmdr.print("There are ");
  Cmdr.print(itms);
  Cmdr.println(" items in the payload");
  
  for(int n = 0; n < 4; n++){
    //try and unpack an int, if it fails there are no more left so exit the loop
    if(Cmdr.getInt(values[n])){
      Cmdr.print("unpacked ");
      Cmdr.println(values[n]);
    }else break;
  }
  //print it out
  Cmdr.println("Array contents after processing:");
  for(int n = 0; n < 4; n++){
    Cmdr.print(n);
    Cmdr.print(" = ");
    Cmdr.println(values[n]);
  }
  //Cmdr.chain();
  //Cmdr.printDiagnostics();
  return 0;
}

bool setFloatsHandler(Commander &Cmdr){
  Cmdr.print("This handler was called by command at index ");
  Cmdr.println(Cmdr.getCommandIndex());
  float values[4] = {0.0,0.0,0.0,0.0};
  int itms = Cmdr.countItems();
  Cmdr.print("There are ");
  Cmdr.print(itms);
  Cmdr.println(" items in the payload");
  
  for(int n = 0; n < 4; n++){
    if(Cmdr.getFloat(values[n])){
      Cmdr.print("unpacked ");
      Cmdr.println(values[n]);
    }else break;
  }
  Cmdr.println("Array contents after processing:");
  for(int n = 0; n < 4; n++){
    Cmdr.print(n);
    Cmdr.print(" = ");
    Cmdr.println(values[n]);
  }
  //Cmdr.chain();
  //Cmdr.printDiagnostics();
  return 0;
}

bool setStringsHandler(Commander &Cmdr){
  Cmdr.print("This handler was called by command at index ");
  Cmdr.println(Cmdr.getCommandIndex());
  String myString = "";
  int itms = Cmdr.countItems();
  Cmdr.print("There are ");
  Cmdr.print(itms);
  Cmdr.println(" items in the payload");
  for(int n = 0; n < itms; n++){
    if(Cmdr.getString(myString)){
      Cmdr.print("String ");
      Cmdr.print(n);
      Cmdr.print(" = ");
      Cmdr.println(myString);
    }else Cmdr.println("Operation failed");
  }
  //Cmdr.chain();
  //Cmdr.printDiagnostics();
  return 0;
}

bool hiddenHandler(Commander &Cmdr){
  Cmdr.print("===========================\nThis handler was called by command at index ");
  Cmdr.println(Cmdr.getCommandIndex());
  Cmdr.println("This command is hidden from the help system");
  //Cmdr.printDiagnostics();
  Cmdr.unchain();
  return 0;
}

bool stepHandler0(Commander &Cmdr){
  Cmdr.print("===========================\nThis handler was called by command at index ");
  Cmdr.println(Cmdr.getCommandIndex());
  Cmdr.println("This is step handler 0\n===========================");
  handlerStep(Cmdr.getCommandIndex());
  return 0;
}

bool stepHandler1(Commander &Cmdr){
  Cmdr.print("===========================\nThis handler was called by command at index ");
  Cmdr.println(Cmdr.getCommandIndex());
  Cmdr.println("This is step handler 1\n===========================");
  handlerStep(Cmdr.getCommandIndex());
  return 0;
}

bool stepHandler2(Commander &Cmdr){
  Cmdr.print("===========================\nThis handler was called by command at index ");
  Cmdr.println(Cmdr.getCommandIndex());
  Cmdr.println("This is step handler 2\n===========================");
  handlerStep(Cmdr.getCommandIndex());
  return 0;
}

bool stepHandler3(Commander &Cmdr){
  Cmdr.print("===========================\nThis handler was called by command at index ");
  Cmdr.println(Cmdr.getCommandIndex());
  Cmdr.println("This is step handler 3\n===========================");
  handlerStep(Cmdr.getCommandIndex());
  return 0;
}
bool printHandler(Commander &Cmdr){
  String myString = "";
  Cmdr.print("myString = ");
  Cmdr.println(myString);
  Cmdr.println("OK?");
  return 0;
}
