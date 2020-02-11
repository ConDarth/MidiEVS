void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600) ;
  
  pinMode(2, INPUT) ;
  pinMode(3, INPUT) ;
}

void loop() {
  // put your main code here, to run repeatedly:

  /*
  Serial.print(digitalRead(2)) ;
  Serial.print("\t") ;
  Serial.println(digitalRead(3)) ;
  */

  Serial.print(analogRead(A0)) ;
  Serial.print("\t") ;
  Serial.println(analogRead(A1)) ;

  delay(10) ;
}
