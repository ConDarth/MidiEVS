#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

Encoder dial1(2, 3) ;
Encoder dial2(4, 3) ;

int counter1 = 0 ;
int counter2 = 0 ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600) ;
}

void loop() {
  // put your main code here, to run repeatedly:
  counter1 = dial1.read()/4 ;
  counter2 = dial2.read()/4 ;
  
  Serial.print(counter1) ;
  Serial.print("\t") ;
  Serial.println(counter2) ;
  delay(100) ;
}


//This works 1000 times better
//never skips 
//nevermisreads 
//no external circuitry
//works with common second pin
//use *this*
