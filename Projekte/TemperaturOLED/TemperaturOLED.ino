#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2 //Der Sensor wird an PIN 2 angeschlossen    

#define DHTTYPE DHT22
// Es handelt sich um den DHT11 / DHT22 Sensor

DHT dht(DHTPIN, DHTTYPE); //Der Sensor wird ab jetzt mit „dth“ angesprochen



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



void setup() {
  Serial.begin(9600); //Serielle Verbindung starten

  dht.begin(); //DHT11 Sensor starten


if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(500);
  display.clearDisplay();

  display.drawPixel(10, 10, WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(500);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(30,25);
  //display.println("Das ist ein");
  //display.setCursor(30,35);
  //display.println("zwei Zeiler"); 
  display.display();


}

void loop() {
  
  
  
  float Luftfeuchtigkeit = dht.readHumidity(); //die Luftfeuchtigkeit auslesen und unter „Luftfeutchtigkeit“ speichern
  
  float Temperatur = dht.readTemperature();//die Temperatur auslesen und unter „Temperatur“ speichern


  display.setCursor(00,00);
  display.print("Luftfeuchtigkeit:");
  display.printf("%.1f",Luftfeuchtigkeit);
  display.setCursor(00,10);
  display.print("Temperatur: ");
  display.println(Temperatur); 
  display.display();
  delay(500);
  display.clearDisplay();

  /*
   * 
   
  Serial.print("Luftfeuchtigkeit: "); //Im seriellen Monitor den Text und 
  Serial.print(Luftfeuchtigkeit); //die Dazugehörigen Werte anzeigen
  Serial.println(" %");
  Serial.print("Temperatur: ");
  Serial.print(Temperatur);
  Serial.println(" Grad Celsius");
*/



}
