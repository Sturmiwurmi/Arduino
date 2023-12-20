#include<SoftwareSerial.h>
int data;


 
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  while(Serial.available()){
  data = Serial.read(); //Read the serial data and store it
  Serial.println(data);
  }

}
