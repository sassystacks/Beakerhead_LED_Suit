// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~` This is for Uno ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

//const int pin = 2;
void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}

int loopNum = 0;
void loop() {
  if (mySwitch.available()) {
    
    Serial.println(mySwitch.getReceivedValue());
    /*
    Serial.print("Received ");
    Serial.print( mySwitch.getReceivedValue() );
    Serial.print(" / ");
    Serial.print( mySwitch.getReceivedBitlength() );
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println( mySwitch.getReceivedProtocol() );
    */
    mySwitch.resetAvailable();  
  }
  else{
    Serial.println(0);
   
  }

  delay(500);
}
