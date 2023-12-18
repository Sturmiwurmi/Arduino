#define PIN_SHIFT 8   // connected to SHCP
#define PIN_STORE 9   // connected to STCP
#define PIN_DATA  10  // connected to DS

int ledPattern[8] = {1,0, 1,0,1, 0, 1, 0};

void setup()
{
  pinMode(PIN_STORE, OUTPUT);
  pinMode(PIN_SHIFT, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);

  for (int i=0; i<8; i++) {
    // set shift pin to "wait"
      //Register pin grounden und low halten, solange übertragen wird
    digitalWrite(PIN_SHIFT, LOW);

    // writing to data pin
    digitalWrite(PIN_DATA, ledPattern[i]);

    // rising slope -> shifting data in the register
    digitalWrite(PIN_SHIFT, HIGH);
  }

  // write whole register to output
  digitalWrite(PIN_STORE, HIGH);
  delay(1000);
}

void loop ()
{
    //Zähler-Routine
  for (int j = 0; j < 256; j++) {
  //Register pin grounden und low halten, solange übertragen wird
    digitalWrite(PIN_SHIFT, LOW);
    shiftOut(PIN_DATA, PIN_STORE, LSBFIRST, j);
  //Register pin auf high setzen, um dem Chip zu signalisieren, dass
  //er nicht mehr länger Informationen lesen muss
    digitalWrite(PIN_SHIFT, HIGH);
    delay(1000);
  }
}

/* // Binär Zähler von 0-255
 * 

byte count = 0;

// Binary count from 0-255:
// 1 = 000000001
// 2 = 000000010
// 3 = 000000011
// 4 = 000000100
// 5 = 000000101
// etc.

void setup()
{
  pinMode(PIN_STORE, OUTPUT);
  pinMode(PIN_SHIFT, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);


  digitalWrite(PIN_STORE, LOW);
  //shiftOut(dataPin, clockPin,bitOrder, value);
  shiftOut(PIN_DATA, PIN_SHIFT, LSBFIRST, count); // LSBFIRST = Last Significant Bit First =rechtes Bit     MSBFIRST = Most significant Bit First = linkes Bit
  digitalWrite(PIN_STORE, HIGH);

  delay(2000);
}

void loop ()
{
  digitalWrite(PIN_STORE, LOW);
  shiftOut(PIN_DATA, PIN_SHIFT, LSBFIRST, count);
  digitalWrite(PIN_STORE, HIGH);
  delay(100);

 count ++;
}
 */
