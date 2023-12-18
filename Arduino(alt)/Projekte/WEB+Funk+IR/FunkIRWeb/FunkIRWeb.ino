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

//IR
#include "IRremote.h" // IR
unsigned int IREmpfangen; 
IRsend irsend(12);
IRrecv Empfaenger(16);
decode_results Daten; // IR
 //IR

 //WEB
#include <ESP8266WiFi.h>
// Hier geben wir den WLAN Namen (SSID) und den Zugansschlüssel ein
const char* ssid     = "NodeMCU";
const char* password = "12345678";
// Wir setzen den Webserver auf Port 80
WiFiServer server(80);
// Eine Variable um den HTTP Request zu speichern
String header;
// Hier wird der aktuelle Status des Relais festgehalten
String output5State = "off";

 //WEB
 
 int button = 14; 
int button2 = 10;  
int buttonState = 0; 
int buttonState2 = 0; 




void setup() {

  
Serial.begin(115200);
  pinMode(button, INPUT); 
  pinMode(button2, INPUT);

 

 
//Funk
 Serial.begin(115200);
  Sendemodul.enableTransmit(15); //D8
  Empfangsmodul.enableReceive(13);
//Funk


// IR
Empfaenger.enableIRIn(); 
// IR

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
  /**delay(1000);
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
    delay(1);
    }
    display.clearDisplay();
  display.display(); 
 **/  
// OLED 

 //WEB
display.setCursor(0,3);
   pinMode(LED_BUILTIN, OUTPUT);
   digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.print(".");
    display.display();
  }
  display.clearDisplay();
  display.display();
   Serial.println(WiFi.localIP());
   
   display.setCursor(0,0);
    display.println("IP: ");
    display.println(WiFi.localIP());
    display.display();
  server.begin();
  //WEB

delay(5000);
  display.clearDisplay();
  display.println(WiFi.localIP());
    
  display.display();
}


void Web(){
  WiFiClient client = server.available();

         if (client) {                       // Falls sich ein neuer Client verbindet,
    Serial.println("Neuer Client.");          // Ausgabe auf den seriellen Monitor
    String currentLine = "";                // erstelle einen String mit den eingehenden Daten vom Client
    while (client.connected()) {  // wiederholen so lange der Client verbunden ist     
      if (client.available()) {             // Fall ein Byte zum lesen da ist,
        char c = client.read();             // lese das Byte, und dann
        Serial.write(c);                    // gebe es auf dem seriellen Monitor aus
        header += c;
        if (c == '\n') {                    // wenn das Byte eine Neue-Zeile Char ist
          // wenn die aktuelle Zeile leer ist, kamen 2 in folge.
          // dies ist das Ende der HTTP-Anfrage vom Client, also senden wir eine Antwort:
          if (currentLine.length() == 0) {
            // HTTP-Header fangen immer mit einem Response-Code an (z.B. HTTP/1.1 200 OK)
            // gefolgt vom Content-Type damit der Client weiss was folgt, gefolgt von einer Leerzeile:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Hier werden die GPIO Pins ein- oder ausgeschaltet
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(LED_BUILTIN, LOW);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(LED_BUILTIN, HIGH);     
           }  //  else if (header.indexOf("GET /4/on") >= 0) {
     
            
            // Hier wird nun die HTML Seite angezeigt:
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // Es folgen der CSS-Code um die Ein/Aus Buttons zu gestalten
            // Hier können Sie die Hintergrundfarge (background-color) und Schriftgröße (font-size) anpassen
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #333344; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #888899;}</style></head>");
            
            // Webseiten-Überschrift
            client.println("<body><h1>Gulli stinkt</h1>");
            
            // Zeige den aktuellen Status, und AN/AUS Buttons for GPIO 5  
            client.println("<p>GPIO 5 - State " + output5State + "</p>");
            // wenn output5State = off, zeige den EIN Button       
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">EIN</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">AUS</button></a></p>");
            } 
            if (1==1) {
              client.println(Daten.value);   
           
            }
       
            client.println("</body></html>");


            
            // Die HTTP-Antwort wird mit einer Leerzeile beendet
            client.println();
            // und wir verlassen mit einem break die Schleife
            break;
          } else { // falls eine neue Zeile kommt, lösche die aktuelle Zeile
            currentLine = "";
          }
        } else if (c != '\r') {  // wenn etwas kommt was kein Zeilenumbruch ist,
          currentLine += c;      // füge es am Ende von currentLine an
        }

        
    

     
      }
         // kein WEB
     if(1==1){

 keinWeb();

  
/**  Empfangsmodul.resetAvailable();
  
(Empfaenger.decode(&Daten));   
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
*/
}

     
   
    //kein WEB
    }
    // Die Header-Variable für den nächsten Durchlauf löschen
    header = "";
    // Die Verbindung schließen
    client.stop();
    Serial.println("Client getrennt.");
    Serial.println("");
   }
  }
 
void keinWeb(){
    
 delay(100);
 
 int Empfangswert = Empfangsmodul.getReceivedValue();
  buttonState = digitalRead(button);
   buttonState2 = digitalRead(button2);
  // put your main code here, to run repeatedly:



display.clearDisplay();
display.display();

display.setCursor(0,0);
  
  display.println("Funk: "); 
  display.print("Empfangen: "); 
  display.println(Empfangswert); 
  display.print("Gespeichert: "); 
  display.println(FunkEmpfangen); 
  display.println(""); 
   display.println("Infrarot: "); 
   display.print("Empf. : "); 
   display.println(Daten.value);
   display.print("Gesp. : "); 
   display.println(IREmpfangen); 
   display.print(WiFi.localIP());
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
     irsend.sendNEC(IREmpfangen,32);
      irsend.sendNEC(IREmpfangen,32);
       irsend.sendNEC(IREmpfangen,16);
       irsend.sendNEC(IREmpfangen,64);
    Sendemodul.send(FunkEmpfangen,16);
     Sendemodul.send(FunkEmpfangen,16);
      Sendemodul.send(FunkEmpfangen,16);
  Serial.println("HI");
   // irsend.sendRaw((unsigned int*)Daten.rawbuf, Daten.rawlen, 38);
    Serial.println(IREmpfangen);
    delay(40);
  }

if(buttonState2 == HIGH){
  FunkEmpfangen = Empfangswert; 
  IREmpfangen = Daten.value,HEX; 
}



  
  }

void loop() {
keinWeb(); 
Web();


  
}
