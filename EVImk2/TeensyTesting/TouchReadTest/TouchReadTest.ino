#define TOUCH_PIN 23

int touchData = 0 ;
unsigned long touchTimer = 0 ;
unsigned long touchDiff = 0 ;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(38400) ;
}

// the loop function runs over and over again forever
void loop() {
  touchTimer = micros() ;
  touchData = touchRead(TOUCH_PIN) ;
  touchDiff = micros() - touchTimer ;

  Serial.print(touchDiff) ;
  Serial.print("\t") ;  
  Serial.println(touchData) ;
  delay(100) ;
}

//Success 
//the touch read function takes between 200 - 700 useconds to read
