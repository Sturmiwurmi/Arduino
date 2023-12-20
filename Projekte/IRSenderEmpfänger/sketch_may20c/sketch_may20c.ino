#include <IRremote.h>

unsigned int IREmpfangen; 
IRsend irsend(D2);



IRrecv Empfaenger(D3);
decode_results Daten; 



void setup() {
  Serial.begin(115200);
  Empfaenger.enableIRIn();



}

void loop() {
 if(Empfaenger.decode(&Daten)){

 Serial.print("Empfangene Daten: ");
Serial.println(Daten.value, HEX);
   
  Empfaenger.resume();
}

 if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    // Überprüfen, ob die Eingabe eine gültige Hexadezimalzahl ist
    if (isHexString(input)) {
      unsigned long hexValue = strtoul(input.c_str(), NULL, 16);
      sendIRSignal(hexValue);
    } else {
      Serial.println("Ungültige Eingabe. Bitte geben Sie eine Hexadezimalzahl ein.");
    }
  }
}

void sendIRSignal(unsigned long value) {
  irsend.sendNEC(value, 32);
  Serial.print("IR-Signal gesendet: 0x");
  Serial.println(value, HEX);
}

boolean isHexString(String input) {
  for (int i = 0; i < input.length(); i++) {
    char c = input.charAt(i);
    if (!isHexadecimalDigit(c)) {
      return false;
    }
  }
  return true;
}
