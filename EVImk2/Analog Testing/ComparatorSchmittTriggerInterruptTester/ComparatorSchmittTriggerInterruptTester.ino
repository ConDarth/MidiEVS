/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

int sensorValue1 = 0;
boolean sensorValue2 = 0;
boolean sensorValue3 = 0 ;
boolean sensorValue4 = 0;
boolean sensorValue5 = 0 ;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(38400);
  pinMode(2, INPUT) ;
  pinMode(3, INPUT) ;
  pinMode(4, INPUT) ;
  pinMode(5, OUTPUT) ;
  pinMode(6, OUTPUT) ;
  pinMode(7, INPUT) ;

  attachInterrupt(digitalPinToInterrupt(2), trigger, CHANGE) ;
}

// the loop routine runs over and over again forever:
void loop() {
  
  sensorValue1 = analogRead(A0); // output 
  sensorValue2 = digitalRead(4) ; //output from comparator 1
  sensorValue3 = digitalRead(3) ; //output from comparator 2
  sensorValue4 = digitalRead(2) ; 
  sensorValue5 = digitalRead(7) ; 

  digitalWrite(5, sensorValue2) ;
  digitalWrite(6, sensorValue3) ;

  
  //print all the values on the same line 
  /*
  Serial.print("Raw Data ");
  Serial.print(sensorValue1);
  Serial.print("\t");
  Serial.print("Comp Low ");
  Serial.print(sensorValue2);
  Serial.print("\t");
  Serial.print("Comp High ");
  Serial.print(sensorValue3);  
  Serial.print("\t");
  Serial.print("Result ");
  Serial.print(sensorValue4);  
  Serial.print("\t");
  Serial.print("Test ");
  Serial.println(sensorValue5);  
  */
  

  delay(0);        
}

void trigger() {
  boolean state = digitalRead(2) ;
  int val = analogRead(A0) ;
  Serial.print("CHANGED STATE TO ") ;
  if (state == 0) {
    Serial.print("LOW");  
  } else if (state == 1) {
    Serial.print("HIGH");     
  }
  Serial.print(" AT ") ;
  Serial.println(val) ;
}
