int button = 0;  
char buttonState = LOW; 
IRsend irsend;

#include "IRremote.h"

IRrecv Empfaenger(5);
decode_results Daten; 
void setup() {
  pinMode(button, INPUT);
  // put your setup code here, to run once:
Serial.begin(9600);
Empfaenger.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
if(Empfaenger.decode(&Daten)){
  Serial.print("Empfangene Daten: ");
  Serial.println(Daten.value, HEX);
  Empfaenger.resume();
  }
  buttonState = digitalRead(button);

if(buttonState == HIGH){
  Serial.println("Button presse, sending data");
  for(int i = 0; i<3; i++){
    irsend.sendSony(0xFF02FD, 12);
    delay(40);
    }
  }
}
