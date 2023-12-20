#include "RCSwitch.h"

RCSwitch Sendemodul = RCSwitch();

void setup() {
  Sendemodul.enableTransmit(15); //D8
  // put your setup code here, to run once:

}

void loop() {
  Sendemodul.send(10,16);
  delay(1000); 
  // put your main code here, to run repeatedly:

}
