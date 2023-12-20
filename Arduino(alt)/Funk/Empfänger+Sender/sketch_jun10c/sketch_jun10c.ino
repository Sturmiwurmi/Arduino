#include "RCSwitch.h"

RCSwitch Sendemodul = RCSwitch();

RCSwitch Empfangsmodul = RCSwitch();w

void setup() {
  Serial.begin(9600);
  Sendemodul.enableTransmit(15); //D8
  Empfangsmodul.enableReceive(13); 
  // put your setup code here, to run once:

}

void loop() {
  delay(1000); 
  Sendemodul.send(11,16);
  Serial.println("Gesendet"); 
 
  // put your main code here, to run repeatedly:
  if(Empfangsmodul.available()){
  int Empfangswert = Empfangsmodul.getReceivedValue(); 

  Serial.print("Empfangswert: "); 
  Serial.println(Empfangswert); 
  }
  Empfangsmodul.resetAvailable();

}
