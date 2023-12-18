//10kOhm pulldown wiederstand zwischen pind d2 von sende nodemcu und d2 von empfang nodemcu. +diode
const int datapin = D2;
 int state = digitalRead(datapin);

 int delaydata =2; 
 
void setup() {
  // Initialisierung des Eingangs für den LED-Pin
  pinMode(datapin, INPUT);
   Serial.begin(115200);
}

void loop() {
  state = digitalRead(datapin);
 
  
if(state == 1){ // startbitempfangen
  getmessage();
}
 
  
}

void getmessage(){
 int datenbits[8]; 
  
  delay(delaydata); 
  delay(1);
  for(int i = 0; i<8;i++){
    
    state = digitalRead(datapin);
   
    datenbits[i] = state; 
    delay(delaydata);
  }

  state = digitalRead(datapin);
  //Serial.println(state);
  if(state != 0){
    Serial.println("stopbit nicht empfangen");
   
  }
  else{
     //printArray(datenbits,8);
     char asciizeichen = getBuchstabeFromBitfolge(datenbits); 
    if(asciizeichen == ' '){
      Serial.println();
    }
    else{
      Serial.print(asciizeichen);
    }
  }

 
}

void printArray(int array[], int size) {
  for (int i = 0; i < size; i++) {   
    Serial.print(array[i]);
  }
  Serial.println();
}

char getBuchstabeFromBitfolge(int bitfolge[8]) {
  int dezimalWert = 0;
  int bitgewicht = 1;

  // Die Bitfolge in einen dezimalen Wert umwandeln
  for (int i = 7; i >= 0; i--) {
    if (bitfolge[i] == 1) {
      dezimalWert += bitgewicht;
    }
    bitgewicht <<= 1; // Bitweise Linksschiebung um 1 Bit, um zum nächsten Bitgewicht zu gelangen
  }

  // Den ASCII-Wert in einen Buchstaben umwandeln
  char buchstabe = (char)dezimalWert;
  return buchstabe;
}
