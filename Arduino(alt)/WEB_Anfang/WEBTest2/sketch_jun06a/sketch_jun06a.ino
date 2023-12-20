#include <ESP8266WiFi.h>
 
const char* ssid = "NodeMCU"; //SSID aus dem Router
const char* password = "12345678"; //Passwort für den Zugang zum WLAN
WiFiServer server(80); //Port auf welchem der Server laufen soll.
 
void setup() {
  Serial.begin(9600);
   
  Serial.print("Aufbau der Verbindung zu: "); //Ausgabe der SSID auf der Seriellen Schnittstelle.
  Serial.println(ssid);
  
  WiFi.begin(ssid, password); //Initialisieren der Wifi Verbindung.
 
  while (WiFi.status() != WL_CONNECTED) { //Warten bis die Verbindung aufgebaut wurde.
    delay(500);
    //Einen Punkt auf der Seriellen Schnittstelle ausgeben so das der Benutzer erkennt dass, das Sketch noch läuft.
    Serial.print("."); 
  }
  Serial.println("");
  
  //Bei erfolgreicher Verbindung wird der folgende Text ausgeben.
  Serial.print("Mit ");
  Serial.print(ssid);
  Serial.print(" erfolgreich verbunden!");
  server.begin(); // Starten des Servers.
  Serial.println("Server gestartet"); //Ausgabe auf der Seriellen Schnittstelle das der Server gestartet wurde.
 
  // Ausgabe der IP Adresse 
  Serial.print("Adresse : http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
/**
 * Die Funktion gibt den HTML Kopf auf dem Client aus.
 * Dieses wird für jeden Respond verwendet.
 **/
void writeResponse(WiFiClient client){  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>"); 
  client.println("<body>"); 
  client.println("Hello fromm NodeMCU Dev Kit");  
  client.println("</body>"); 
  client.println("</html>"); 
}
void loop() {
  //Prüfen ob sich ein Client verbunden hat, wenn nicht die Loop "verlassen"
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wenn sich ein Client verbunden hat solange warten bis Daten gesendet werden.
  Serial.println("Neuer Client verbunden.");
  while(!client.available()){
    delay(1);
  }
 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush(); 
  writeResponse(client);
  
  delay(1); //1ms. Pause
}
