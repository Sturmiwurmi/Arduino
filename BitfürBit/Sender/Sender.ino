// PIN für die LED am Sender
const int DATAPIN = D2;
int state = digitalRead(DATAPIN);

int delaydata =2; 
void setup() {
  // Initialisierung des Ausgangs für die LED
  pinMode(DATAPIN, OUTPUT);
  Serial.begin(115200);

}

void loop() {
   userinputhandler(); 
  
  
  
  
}

void userinputhandler(){
  if (Serial.available()) {
    String receivedData = Serial.readStringUntil('\n'); // Lies die empfangene Zeile bis zum Zeilenumbruch

    // Prüfe, ob die empfangene Zeile mit einem "/" beginnt
    if (receivedData.startsWith("/")) {
      // Zeile mit "/" am Anfang wurde empfangen, verarbeite sie
      receivedData.remove(0, 1); // Entferne das "/" aus der empfangenen Zeile

      // Hier kannst du auf die empfangene Zeile reagieren oder sie verwenden
      // Zum Beispiel, drucke sie aus
      Serial.print("Empfangene Zeile: ");
      Serial.println(receivedData);

      sendtext(delaydata,receivedData);

      
    }
  }
}
void sendtext(int bitzeit, String text){
  int länge = text.length();
  
  for (int i = 0; i < länge; i++) {
    char buchstabe = text.charAt(i);
    Serial.println(buchstabe);
   sendByte(delaydata,getBitfolge(buchstabe)); // wandelt buchstaben in binärzahl um und sendet diesen 
  }
  
}
void sendByte(int bitzeit, int bitfolge[]){
  setdata(1); // startbit
  delay(bitzeit);

  for(int i = 0; i<8;i++){
  
    setdata(bitfolge[i]);
     delay(bitzeit);
  }

  setdata(0); // stoppbit
  delay(bitzeit);
}

void setdata(int state){
  if(state == 0 || state == 1){
  digitalWrite(DATAPIN, state);
  state = digitalRead(DATAPIN);
  Serial.println(state);
  }else{
    Serial.println("state =! 0 || 1");
  }
}

int* getBitfolge(char zeichen) {
  int* bitfolge = new int[8]; // Speicher für das 8-Bit-Array dynamisch reservieren
  int zeichenWert = int(zeichen); // ASCII-Wert des Buchstabens ermitteln
  for (int i = 7; i >= 0; i--) {
    bitfolge[i] = zeichenWert & 1; // Bitweise AND-Operation mit 1, um das letzte Bit zu isolieren
    zeichenWert >>= 1; // Bitweise Rechtsverschiebung um 1 Bit, um zum nächsten Bit zu gelangen
  }
  return bitfolge; // Das Array zurückgeben
}
