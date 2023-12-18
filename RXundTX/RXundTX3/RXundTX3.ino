#include<SoftwareSerial.h>
int ledPin =  12; 

int buttonPin = 2;
int buttonState = 0;

int data;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
pinMode(ledPin, OUTPUT);
pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

 while(Serial.available()){
  data = Serial.read(); //Read the serial data and store it
  Serial.println(data);
  }
  
  if(buttonState == HIGH){
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  delay(1);
}
