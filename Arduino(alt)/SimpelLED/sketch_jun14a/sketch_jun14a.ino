int LED=16; //Das Wort „LED“ steht jetzt für den Wert 9.


void setup()//Hier beginnt das Setup.
{
pinMode(LED, OUTPUT);//Der Pin mit der LED (Pin9) ist ein Ausgang
}

void loop()
{
digitalWrite(LED, HIGH);
}
