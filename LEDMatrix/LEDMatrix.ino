#define PIN_DIN 13  //D7 für NoteMCU
#define PIN_CLK 14  //D5
#define PIN_CS  2   //D4
#define NUM_DEVICES 1

#include <LedControl.h>

LedControl lc = LedControl(PIN_DIN, PIN_CLK, PIN_CS, NUM_DEVICES);

byte frames[3][8] = {  // Das Bild ist um 90 Grad gedreht 
  {
    B00111100,
    B01000010,
    B10010101,
    B10100001,
    B10100001,
    B10010101,
    B01000010,
    B00111100
  },
  {
    B00111100,
    B01000010,
    B10010101,
    B10010001,
    B10010001,
    B10010101,
    B01000010,
    B00111100
  },
  {
    B00111100,
    B01000010,
    B10100101,
    B10010001,
    B10010001,
    B10100101,
    B01000010,
    B00111100
  }
};

byte frames2[8][8] = {
  {
    B11111111,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  {
    B00000000,
    B11111111,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  {
    B00000000,
    B00000000,
    B11111111,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  {
    B00000000,
    B00000000,
    B00000000,
    B11111111,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111111,
    B00000000,
    B00000000,
    B00000000
  } ,
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111111,
    B00000000,
    B00000000
  } ,
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111111,
    B00000000
  },
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111111
  }
  };
void setup()
{
  lc.shutdown(0, false);

  // intensity level (0..15)
  lc.setIntensity(0, 2);

  lc.clearDisplay(0);
  Serial.begin(9600);
}

void loop()
{
 
  
  for (int frame=0; frame<8; frame++) {
  for (int dot=0; dot<8; dot++) {
      lc.setRow(0, dot, frames2[frame][dot]);
    }
     
  Serial.println(sizeof(frames2));
  Serial.println(sizeof(frames2[0]));
  Serial.println(sizeof(frames2) /sizeof(frames2[0])); // gibt Länge des Arrays (anzahl der Frames wieder)
    delay(400);
  }
  /*
   * 
  
  for (int frame=0; frame<3; frame++) {
    for (int dot=0; dot<8; dot++) {
      lc.setRow(0, dot, frames[frame][dot]);
    }
    delay(750);
  }
    */
}
