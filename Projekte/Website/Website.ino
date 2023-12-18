#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "MeinAccessPoint"; // SSID für den Access Point
const char* password = "Passwort123"; // Passwort für den Access Point
const IPAddress ip(192, 168, 1, 1); // IP-Adresse für die Website

ESP8266WebServer server(ip, 80);
const int ledPin = D8; // Pin für die LED

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>NodeMCU Website</h1>";
  html += "<button onclick=\"toggleLED()\">LED schalten</button>";
  html += "<script>";
  html += "function toggleLED() {";
  html += "var xhttp = new XMLHttpRequest();";
  html += "xhttp.onreadystatechange = function() {";
  html += "if (this.readyState == 4 && this.status == 200) {";
  html += "console.log(this.responseText);"; // Ausgabe im seriellen Monitor
  html += "}";
  html += "};";
  html += "xhttp.open('GET', '/led', true);";
  html += "xhttp.send();";
  html += "}";
  html += "</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleLED() {
  digitalWrite(ledPin, !digitalRead(ledPin));
  server.send(200, "text/plain", "LED geschaltet");
}

void setup() {
  Serial.begin(115200);

  WiFi.softAPConfig(ip, ip, IPAddress(255, 255, 255, 0)); // IP-Adresse für Access Point festlegen
  WiFi.softAP(ssid, password);

  pinMode(ledPin, OUTPUT);

  server.on("/", handleRoot);
  server.on("/led", handleLED);
  server.begin();
}

void loop() {
  server.handleClient();
}
