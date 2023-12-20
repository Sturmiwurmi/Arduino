

#include <IRremoteESP8266.h>
#include <IRsend.h>

// Pin für die Sende-LED
const uint16_t sendPin = D2;

// IRsend-Objekt für die Infrarotsignalübertragung
IRsend irSender(sendPin);

void setup() {
  Serial.begin(115200);
  pinMode(sendPin, OUTPUT);
  digitalWrite(sendPin, LOW);
}

void loop() {
  sendIRSignal(0xFF02FD); // Wert für "An" senden
  delay(1000); // Eine Sekunde warten
  sendIRSignal(0xFF827D); // Wert für "Aus" senden
  delay(1000); // Eine Sekunde warten
}

void sendIRSignal(unsigned long value) {
  irSender.sendNEC(value, 32);
  Serial.print("IR-Signal gesendet: 0x");
  Serial.println(value, HEX);
}
