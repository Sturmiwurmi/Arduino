#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <IRsend.h> // Hinzugefügt für den IR-Sender

const char* ssid = "MeinAccessPoint"; // SSID für den Access Point
const char* password = ""; // Passwort für den Access Point

IPAddress ip(192, 168, 1, 1); // IP-Adresse für die Website

ESP8266WebServer server(ip, 80);
IRrecv irReceiver(D3); // Pin, an dem der IR-Empfänger angeschlossen ist
IRsend irSender(D2); // Pin, an dem der IR-Sender angeschlossen ist

decode_results results; // Speichert die zuletzt empfangenen IR-Daten
bool isButtonPressed = false; // Zwischengespeicherter Zustand des Knopfes
String storedValue = ""; // Zwischengespeicherter Wert
unsigned int IREmpfangen;



void handleRoot() {
  String html = "<html><body>";
  html += "<h1>NodeMCU Website</h1>";
  html += "<p id='irData'></p>";
  html += "<p id='storedValue'></p>";
  html += "<button onclick=\"storeValue()\">Wert speichern</button>";
  html += "<button onclick=\"sendValue()\">Gespeicherten Wert senden</button>"; // Button zum Senden des gespeicherten Werts hinzugefügt
  html += "<script>";
  html += "function updateIRData() {";
  html += "var xhttp = new XMLHttpRequest();";
  html += "xhttp.onreadystatechange = function() {";
  html += "if (this.readyState == 4 && this.status == 200) {";
  html += "document.getElementById('irData').innerHTML = 'Empfangene IR-Daten: ' + this.responseText;";
  html += "}";
  html += "};";
  html += "xhttp.open('GET', '/irdata', true);";
  html += "xhttp.send();";
  html += "}";
  html += "function storeValue() {";
  html += "var xhttp = new XMLHttpRequest();";
  html += "xhttp.onreadystatechange = function() {";
  html += "if (this.readyState == 4 && this.status == 200) {";
  html += "console.log(this.responseText);"; // Ausgabe im seriellen Monitor
  html += "}";
  html += "};";
  html += "xhttp.open('GET', '/storevalue', true);";
  html += "xhttp.send();";
  html += "}";
  html += "function sendValue() {";
  html += "var xhttp = new XMLHttpRequest();";
  html += "xhttp.onreadystatechange = function() {";
  html += "if (this.readyState == 4 && this.status == 200) {";
  html += "console.log(this.responseText);"; // Ausgabe im seriellen Monitor
  html += "}";
  html += "};";
  html += "xhttp.open('GET', '/sendvalue', true);"; // Neue Route zum Senden des gespeicherten Werts
  html += "xhttp.send();";
  html += "}";
  html += "function updateStoredValue() {";
  html += "var xhttp = new XMLHttpRequest();";
  html += "xhttp.onreadystatechange = function() {";
  html += "if (this.readyState == 4 && this.status == 200) {";
  html += "document.getElementById('storedValue').innerHTML = 'Gespeicherter Wert: ' + this.responseText;";
  html += "}";
  html += "};";
  html += "xhttp.open('GET', '/storedvalue', true);";
  html += "xhttp.send();";
  html += "}";
  html += "setInterval(updateIRData, 2000);"; // Aktualisierung alle 2 Sekunden
  html += "setInterval(updateStoredValue, 2000);"; // Aktualisierung alle 2 Sekunden
  html += "</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleIRData() {
  if (irReceiver.decode(&results)) {
    IREmpfangen = results.value,HEX;
    String irData = results.value == 0xFFFFFFFF ? "Keine Daten" : String(results.value, HEX);
    server.send(200, "text/plain", irData);
    irReceiver.resume();
    Serial.println("Empfangene IR-Daten: " + irData);
  } else {
    server.send(200, "text/plain", "Keine Daten");
  }
}

void handleStoreValue() {
  isButtonPressed = true;
  storedValue = results.value == 0xFFFFFFFF ? "Keine Daten" : String(results.value, HEX);
  server.send(200, "text/plain", "Wert gespeichert");
  Serial.println("Wert gespeichert: " + storedValue);
}

void handleSendValue() {
  if (isButtonPressed) {
    unsigned long value = strtoul(storedValue.c_str(), nullptr, 16);
    irSender.sendNEC(value, 32);
    server.send(200, "text/plain", "Gespeicherter Wert gesendet");
    Serial.println("Gespeicherter Wert gesendet: " + storedValue);
  } else {
    server.send(200, "text/plain", "Kein Wert gespeichert");
  }
}


void handleStoredValue() {
  server.send(200, "text/plain", storedValue);
}

void setup() {
  Serial.begin(115200);

  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW);

  irReceiver.enableIRIn();

  WiFi.softAPConfig(ip, ip, IPAddress(255, 255, 255, 0)); // IP-Adresse für Access Point festlegen
  WiFi.softAP(ssid, password);

  server.on("/", handleRoot);
  server.on("/irdata", handleIRData);
  server.on("/storevalue", handleStoreValue);
  server.on("/sendvalue", handleSendValue); // Neue Route zum Senden des gespeicherten Werts
  server.on("/storedvalue", handleStoredValue);
  server.begin();
}

void loop() {
  server.handleClient();
}
