int pitchBendValue = 0 ;
unsigned long lastPbTime = 0 ;
boolean pbInterruptToggle = true ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400) ;
  pinMode(2, OUTPUT) ;
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( ((micros() - lastPbTime) > 1000 ) && (pbInterruptToggle == true) ) {
    lastPbTime = micros() ;
    pitchBendValue = analogRead(A0) ;
    digitalWrite(2, HIGH) ;
    pbInterruptToggle = false ;

    Serial.println(pitchBendValue) ;
  } else if ( ((micros() - lastPbTime) > 200 ) && (pbInterruptToggle == false) ) {
    digitalWrite(2, LOW) ;
    pbInterruptToggle = true ;
  }
}

//test failed 
//interrupt driven pitch bend is not viable option for pb
//needs so quick of a loop to be going on in the background 
//capacitance nature to complicated to make work simply 
//the library is much better
