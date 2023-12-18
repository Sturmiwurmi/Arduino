#include "IRremote.h"
int button = 0;  
char buttonState = LOW; 

IRsend irsend(16);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(button, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
buttonState = digitalRead(button);

if(buttonState == HIGH){
  Serial.println("Button presse, sending data");
  for(int i = 0; i<3; i++){
    irsend.sendSony(0xFF02FD, 12);
    delay(40);
    }
  }

  irsend.sendSony(0xFF02FD, 12);
  delay(50);
}
