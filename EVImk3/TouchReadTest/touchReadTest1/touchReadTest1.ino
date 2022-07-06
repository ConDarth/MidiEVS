unsigned long t0 = 0 ;
int val = 0 ;
unsigned long t = 0 ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600) ;
  while(!Serial) {
    
  }
  Serial.println("Started") ;
}

void loop() {
  // put your main code here, to run repeatedly:
  t0 = micros() ;
  val = touchRead(17) ;
  t = micros() - t0 ;
  
  Serial.print(val) ;
  Serial.print("     ") ;
  Serial.println(t) ;
  
  delay(20) ;
}
