 //Funk
 #include "RCSwitch.h"

RCSwitch Sendemodul = RCSwitch();

RCSwitch Empfangsmodul = RCSwitch();
int FunkEmpfangen; 
 //Funk
 
 // OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

 // OLED 


#include "IRremote.h" // IR

int button = 14; 
int button2 = 10;  
int buttonState = 0; 
int buttonState2 = 0; 
unsigned int IREmpfangen; 
IRsend irsend(12);

IRrecv Empfaenger(16);
decode_results Daten; // IR
 
void setup() {
Serial.begin(115200);

//Funk
 Serial.begin(9600);
  Sendemodul.enableTransmit(15); //D8
  Empfangsmodul.enableReceive(13);
//Funk

  pinMode(button, INPUT); // IR
  pinMode(button2, INPUT);
  // put your setup code here, to run once:

Empfaenger.enableIRIn(); // IR
// OLED 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
   // Clear the buffer
  display.clearDisplay();
  // Draw a single pixel in white
  display.drawPixel(10, 10, WHITE);
  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(500);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(30,25);
  display.println("GULLI STINKT");
  display.setCursor(30,35);
  display.println("MiMiMiMiMiMi"); 
  display.display();
  delay(1000);

  for(byte i = 0; i<160;i++){
    display.drawLine(0,45,i,45, WHITE);
     display.drawLine(0,46,i,46, WHITE);
      display.drawLine(0,47,i,47, WHITE);
       display.drawLine(0,48,i,48, WHITE);
        display.drawLine(0,49,i,49, WHITE);
         display.drawLine(0,50,i,50, WHITE);
          display.drawLine(0,51,i,51, WHITE);
           display.drawLine(0,52,i,52, WHITE);
           
    display.display();
    delay(10);
    }
    display.clearDisplay();
    display.display(); 
// OLED 
}

void loop() {
  
 delay(100);
 
 int Empfangswert = Empfangsmodul.getReceivedValue();
  buttonState = digitalRead(button);
   buttonState2 = digitalRead(button2);
  // put your main code here, to run repeatedly:

if(buttonState2 == HIGH){
  FunkEmpfangen = Empfangswert; 
  IREmpfangen = Daten.value,HEX; 
}

display.clearDisplay();
display.display();

display.setCursor(0,0);
  
  display.println("");
  display.println("Funk: "); 
  display.print("Empfangen: "); 
  display.println(Empfangswert); 
  display.print("Gespeichert: "); 
  display.println(FunkEmpfangen); 
  display.println(""); 
   display.println("Infrarot: "); 
   display.print("Empfangen: "); 
   display.println(Daten.value);
   display.print("Gespeichert: "); 
   display.println(IREmpfangen); 
   display.display();
  
  Empfangsmodul.resetAvailable();
 


(Empfaenger.decode(&Daten));
   // Serial.print("Empfangene Daten: ");
   // Serial.println(Daten.value, HEX);

   
 
  Empfaenger.resume();

  
  

if(buttonState == HIGH){
  //Serial.println("Button presse, sending data");
  // for(int i = 30; i<65;i++){
    irsend.sendNEC(IREmpfangen,32);
    Sendemodul.send(FunkEmpfangen,16);
  Serial.println("HI");
   // irsend.sendRaw((unsigned int*)Daten.rawbuf, Daten.rawlen, 38);
    Serial.println(IREmpfangen);
    delay(40);
    
  }
}
