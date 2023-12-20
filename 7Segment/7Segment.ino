#define PIN_SHIFT 12   // connected to SHCP  = D6
#define PIN_STORE 4   // connected to STCP   = D2
#define PIN_DATA  5  // connected to DS      = D1 

#define D2 0 // Digit 2
#define D3 13 //Digit 3
#define D1 15 //Digit 1

//Schieberegisterpin      0 1 2 3  4 5 6 7
//Segmentanschlusspin     e d c dp g f a b

         int eins[8] =   {0,0,1,1 ,0,0,0,1};
         int zwei[8] =   {1,1,0,1 ,1,0,1,1};
         int drei[8] =   {0,1,1,1 ,1,0,1,1};
         int vier[8] =   {0,0,1,1 ,1,1,0,1};
         int fuenf[8] =  {0,1,1,1 ,1,1,1,0};
         int sechs[8] =  {1,1,1,1 ,1,1,0,0};
         int sieben[8]=  {0,0,1,1 ,0,0,1,1};
         int acht[8] =   {1,1,1,1 ,1,1,1,1};
         int neun[8] =   {0,1,1,1 ,1,1,1,1};

void setup()
{
  pinMode(PIN_STORE, OUTPUT);
  pinMode(PIN_SHIFT, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
  
  pinMode(D1, OUTPUT);
  digitalWrite(D1,HIGH);
  pinMode(D2, OUTPUT);
  digitalWrite(D2,HIGH);
  pinMode(D3, OUTPUT);
  digitalWrite(D3,HIGH);
  
  Serial.begin(9600);

for(int i = 10; i>=0; i--){
  Serial.println(i);
  
  }
 
segmentX(2);
delay(500);
segmentX(7);
}

void loop ()
{
  if(Serial.available()){
  int Data = Serial.read(); 
  switch(Data){
    case 49:
    Data = 1; 
    break;
    case 50:
    Data = 2; 
    break;
    case 51:
    Data = 3; 
    break;
    case 52:
    Data = 4; 
    break;
    case 53:
    Data = 5; 
    break;
    case 54:
    Data = 6; 
    break;
    case 55:
    Data = 7; 
    break;
    case 56:
    Data = 8; 
    break;
    case 57:
    Data = 9; 
    break;
    }
    
   Serial.println(Data);
   if(Data != 10){
   segmentX(Data);
   }
   else
   {
    digitalWrite(D3,LOW);
    delay(50);
    digitalWrite(D2,LOW);
    delay(50);
    digitalWrite(D1,LOW);
    delay(50);
    
    delay(1000);
    digitalWrite(D3,HIGH);
    delay(50);
    digitalWrite(D2,HIGH);
    delay(50);
    digitalWrite(D1,HIGH);
    delay(50);
    }
delay(500);
  }
  /*
for(int i = 0; i<10; i++){
  segmentX(i);
delay(500);
  }*/
}

void segmentX(int pZahl) {
    switch(pZahl){
      case 1:

       
  for (int i=(sizeof(eins)/2)-1; i>=0; i--) { // sizeof/2-1 = höchster Index des Arrays und das Array muss runter zählen damit hier "eins[i]" (das Array) in der richtigen Richtung in das Schieberegister rein kommt
    // set shift pin to "wait"
      //Register pin grounden und low halten, solange übertragen wird
    digitalWrite(PIN_SHIFT, LOW);
    // writing to data pin
    digitalWrite(PIN_DATA, eins[i]);
    // rising slope -> shifting data in the register
    digitalWrite(PIN_SHIFT, HIGH);
    
  }
  // write whole register to output
  digitalWrite(PIN_STORE, HIGH);
  digitalWrite(PIN_STORE, LOW);
  
  break;
  
case 2:
  for (int i=(sizeof(zwei)/2)-1; i>=0; i--) {   
    digitalWrite(PIN_SHIFT, LOW);  
    digitalWrite(PIN_DATA, zwei[i]);
    digitalWrite(PIN_SHIFT, HIGH);
   
  }
  digitalWrite(PIN_STORE, HIGH);
  digitalWrite(PIN_STORE, LOW);
  
break;
case 3:
  for (int i=(sizeof(drei)/2)-1; i>=0; i--) {   
    digitalWrite(PIN_SHIFT, LOW);  
    digitalWrite(PIN_DATA, drei[i]);
    digitalWrite(PIN_SHIFT, HIGH);
    
  }
  digitalWrite(PIN_STORE, HIGH);
  digitalWrite(PIN_STORE, LOW);
  
break;
case 4:
  for (int i=(sizeof(vier)/2)-1; i>=0; i--) {   
    digitalWrite(PIN_SHIFT, LOW);  
    digitalWrite(PIN_DATA, vier[i]);
    digitalWrite(PIN_SHIFT, HIGH);
   
  }
  digitalWrite(PIN_STORE, HIGH);
  digitalWrite(PIN_STORE, LOW);
  
break;
case 5:
  for (int i=(sizeof(fuenf)/2)-1; i>=0; i--) {   
    digitalWrite(PIN_SHIFT, LOW);  
    digitalWrite(PIN_DATA, fuenf[i]);
    digitalWrite(PIN_SHIFT, HIGH);
    
  }
  digitalWrite(PIN_STORE, HIGH);
  digitalWrite(PIN_STORE, LOW);
  
break;

case 6:
  for (int i=(sizeof(sechs)/2)-1; i>=0; i--) {   
    digitalWrite(PIN_SHIFT, LOW);  
    digitalWrite(PIN_DATA, sechs[i]);
    digitalWrite(PIN_SHIFT, HIGH);
    
  }
  digitalWrite(PIN_STORE, HIGH);
  digitalWrite(PIN_STORE, LOW);
 
break;

case 7:
  for (int i=(sizeof(sieben)/2)-1; i>=0; i--) {   
    digitalWrite(PIN_SHIFT, LOW);  
    digitalWrite(PIN_DATA, sieben[i]);
    digitalWrite(PIN_SHIFT, HIGH);
    
  }
  digitalWrite(PIN_STORE, HIGH);
  digitalWrite(PIN_STORE, LOW);
 
break;

case 8:
  for (int i=(sizeof(acht)/2)-1; i>=0; i--) {   
    digitalWrite(PIN_SHIFT, LOW);  
    digitalWrite(PIN_DATA, acht[i]);
    digitalWrite(PIN_SHIFT, HIGH);
    
  }
  digitalWrite(PIN_STORE, HIGH);
  digitalWrite(PIN_STORE, LOW);
 
break;

case 9:
  for (int i=(sizeof(neun)/2)-1; i>=0; i--) {   
    digitalWrite(PIN_SHIFT, LOW);  
    digitalWrite(PIN_DATA, neun[i]);
    digitalWrite(PIN_SHIFT, HIGH);
    
  }
  digitalWrite(PIN_STORE, HIGH);
  digitalWrite(PIN_STORE, LOW);
  
break;
}
      
      }
