#include <IRremote.h>

const int RECV_PIN = D3;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn(); // Aktivieren des Infrarotempfangs
}

void loop() {
  if (irrecv.decode(&results)) { // Prüfen, ob Infrarotsignal empfangen wurde
    // Ausgabe der Infrarotdaten auf dem seriellen Monitor
    Serial.print("Infrarotwert: ");
    Serial.println(results.value, HEX);
    irrecv.resume(); // Empfang für das nächste Signal fortsetzen
  }
}
