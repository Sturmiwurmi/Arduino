#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

#define DHTPIN D2         // Pin, an dem der DHT22 angeschlossen ist
#define DHTTYPE DHT22     // DHT-Typ (DHT11 oder DHT22)

const char* ssid = "MeinAccessPoint"; // SSID für den Access Point
const char* password = ""; // Passwort für den Access Point

IPAddress ip(192, 168, 1, 1); // IP-Adresse für die Website

ESP8266WebServer server(ip, 80);
const int ledPin = D8; // Pin für die LED

DHT dht(DHTPIN, DHTTYPE);

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>NodeMCU Website</h1>";
  html += "<p id='temperature'></p>";
  html += "<p id='humidity'></p>";
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
  html += "function updateTemperature() {";
  html += "var xhttp = new XMLHttpRequest();";
  html += "xhttp.onreadystatechange = function() {";
  html += "if (this.readyState == 4 && this.status == 200) {";
  html += "document.getElementById('temperature').innerHTML = 'Temperatur: ' + this.responseText + '°C';";
  html += "}";
  html += "};";
  html += "xhttp.open('GET', '/temperature', true);";
  html += "xhttp.send();";
  html += "}";
  html += "function updateHumidity() {";
  html += "var xhttp = new XMLHttpRequest();";
  html += "xhttp.onreadystatechange = function() {";
  html += "if (this.readyState == 4 && this.status == 200) {";
  html += "document.getElementById('humidity').innerHTML = 'Luftfeuchtigkeit: ' + this.responseText + '%';";
  html += "}";
  html += "};";
  html += "xhttp.open('GET', '/humidity', true);";
  html += "xhttp.send();";
  html += "}";
  html += "setInterval(updateTemperature, 2000);"; // Aktualisierung alle 2 Sekunden
  html += "setInterval(updateHumidity, 2000);"; // Aktualisierung alle 2 Sekunden
  html += "</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleLED() {
  digitalWrite(ledPin, !digitalRead(ledPin));
  server.send(200, "text/plain", "LED geschaltet");
}

void handleTemperature() {
  float temperature = dht.readTemperature();
  server.send(200, "text/plain", String(temperature));
}

void handleHumidity() {
  float humidity = dht.readHumidity();
  server.send(200, "text/plain", String(humidity));
}

void setup() {
  Serial.begin(115200);

  dht.begin();

  WiFi.softAPConfig(ip, ip, IPAddress(255, 255, 255, 0)); // IP-Adresse für Access Point festlegen
  WiFi.softAP(ssid, password);

  pinMode(ledPin, OUTPUT);

  server.on("/", handleRoot);
  server.on("/led", handleLED);
  server.on("/temperature", handleTemperature);
  server.on("/humidity", handleHumidity);
  server.begin();
}

void loop() {
  server.handleClient();
}
