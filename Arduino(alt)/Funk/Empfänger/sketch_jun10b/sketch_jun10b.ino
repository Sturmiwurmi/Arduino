#include "RCSwitch.h"
RCSwitch Empfangsmodul = RCSwitch();


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Empfangsmodul.enableReceive(); 
}

void loop() {
  // put your main code here, to run repeatedly:
if(Empfangsmodul.available()){
  int Empfangswert = Empfangsmodul.getReceivedValue(); 

  Serial.print("Empfangswert: "); 
  Serial.print(Empfangswert); 
  }
  Empfangsmodul.resetAvailable();
}
