#include<SoftwareSerial.h>

int ledPin =   13; 

int buttonPin = 14;
int buttonState = 0;
int data;
void setup() {
  // put your setup code here, to run once:
pinMode(ledPin, OUTPUT);
pinMode(buttonPin, INPUT);

 Serial.begin(9600);
 digitalWrite(ledPin, HIGH);
 
 Serial.print("COM4");
 Serial.println("TEST"); 
}

void loop() {

  /**
   * 
  
  buttonState = digitalRead(buttonPin);
  
  if(buttonState == HIGH){
   // digitalWrite(ledPin, HIGH);
   Serial.println(10);
     delay(500);
   
    //Serial.write(33);
    data = Serial.read(); //Read the serial data and store it
    Serial.println(data);
  
    
  } else {
    //digitalWrite(ledPin, LOW);
  }

 */
 
 buttonState = digitalRead(buttonPin);
  
  if(buttonState == HIGH){
    digitalWrite(ledPin, HIGH);
    
    Serial.write(123);
    
    delay(500);
  }
    else {
    digitalWrite(ledPin, LOW);
  }
  
}
