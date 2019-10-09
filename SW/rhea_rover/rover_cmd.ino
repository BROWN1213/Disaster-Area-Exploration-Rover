#include <CmdMessenger.h>  // CmdMessenger
CmdMessenger cmdMessenger = CmdMessenger(Serial);

enum
{
  kAcknowledge, //0
  kError, //1
  kVelocity, // 2
  kRadius //3
};

void attachCommandCallbacks()
{
  // Attach callback methods
  cmdMessenger.attach(OnUnknownCommand);
  cmdMessenger.attach(kFalling, OnFalling);
  cmdMessenger.attach(kVelocity, OnVelocity);
  cmdMessenger.attach(kRadius, OnRadius);
}
void cmdMessengerRun(){
  cmdMessenger.feedinSerialData();
}

void setupCmdMessenger(){
  //setup Command Messenger 
  attachCommandCallbacks();
  Serial.println(F("CmdMessenger begin"));
  cmdMessenger.printLfCr();  
}

// Called when a received command has no attached function
void OnUnknownCommand()
{
  cmdMessenger.sendCmd(kError,F("Command without attached callback"));
  
}


// Callback function that sets falling
void OnVelocity(){
  cmdMessenger.sendCmd(kError,F("Command without attached callback"));
}
void OnRadius(){
  
}
