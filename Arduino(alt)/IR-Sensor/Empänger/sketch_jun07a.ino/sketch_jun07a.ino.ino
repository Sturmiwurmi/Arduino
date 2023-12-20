


#include "IRremote.h"

int button = 14; 
int button2 = 15;  
int buttonState = 0; 
int buttonState2 = 0; 
unsigned int IREmpfangen; 
IRsend irsend(12);

IRrecv Empfaenger(16);
decode_results Daten; 
void setup() {
  pinMode(button, INPUT);
  pinMode(button2, INPUT);
  // put your setup code here, to run once:
Serial.begin(115200);
Empfaenger.enableIRIn();
}

void loop() {
  buttonState = digitalRead(button);
   buttonState2 = digitalRead(button2);
  // put your main code here, to run repeatedly:

if(buttonState2 == HIGH){
  IREmpfangen = Daten.value;
}

if(Empfaenger.decode(&Daten)){
}
 Serial.print("Empfangene Daten: ");
Serial.println(Daten.value);
   
  Empfaenger.resume();
  
  
 

if(buttonState == HIGH){
  //Serial.println("Button presse, sending data");
  
    irsend.sendSony(IREmpfangen, 64);
   // irsend.sendRaw((unsigned int*)Daten.rawbuf, Daten.rawlen, 38);
    Serial.println(IREmpfangen);
    delay(40);
    
  }
}
