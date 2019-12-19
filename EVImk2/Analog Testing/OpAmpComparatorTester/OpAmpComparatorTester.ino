/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0 ;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(2, INPUT) ;
  pinMode(3, INPUT) ;
}

// the loop routine runs over and over again forever:
void loop() {
  
  sensorValue1 = analogRead(A0); // output 
  sensorValue2 = digitalRead(2) ; //output from comparator 1
  sensorValue3 = digitalRead(3) ; //output from comparator 2
  
  //print all the values on the same line 
  Serial.print(sensorValue1);
  Serial.print("\t");
  Serial.print(sensorValue2);
  Serial.print("\t");
  Serial.println(sensorValue3);  
  
  delay(2);        
}
