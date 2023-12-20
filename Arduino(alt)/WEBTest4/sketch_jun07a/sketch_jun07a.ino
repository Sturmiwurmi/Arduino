#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//ESP Web Server Library to host a web page
#include <ESP8266WebServer.h>

#define LED 2  

String WIU = "TEST";

const char* ssid = "NodeMCU";
const char* password = "12345678";

WiFiServer server(80); 
void setup() {
  Serial.begin(115200);
   WiFi.begin(ssid,password);  
    server.begin(); 
    
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    Serial.println(WiFi.localIP());     
  // put your setup code here, to run once:


}


void handleLEDon() { 
  
 
 digitalWrite(LED,HIGH); //LED off

}


void loop() {
  // put your main code here, to run repeatedly:
WiFiClient client = server.available();  

 while (client.connected() )           
    {
        if (client.available() )
            { 
                
               if (header.indexOf("GET /5/on") >= 0) {
              
              digitalWrite(LED, HIGH);
               }


            
 client.println("HTTP/1.1 200 OK");
 client.println("Content-Type: text/html");
 client.println("Connection: close");
 client.println("Refresh: 2");
 client.println();
 client.println("<html>");
 client.print("Analogert: ");
 client.println(WIU);
 client.println("<br><br>");
 client.println("<a href='?ledOn'>LED ON</a><br>");
 client.println("<br><br>");
 client.println("<a href='?ledOff'>LED OFF</a><br>");
 client.println("</html>"); 
 
 break;
            }
 }
 delay(1);
  client.stop();
}   
