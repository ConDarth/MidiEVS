#define PIN_A 2
#define PIN_B 3
#define PIN_C 4

int counter1 = 0 ;
boolean encoderFlag1 = false ;
int counter2 = 0 ;
boolean encoderFlag2 = false ;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600) ;

  pinMode(PIN_A, INPUT_PULLUP) ;
  pinMode(PIN_B, INPUT_PULLUP) ;
  pinMode(PIN_C, INPUT_PULLUP) ;
  attachInterrupt(PIN_A, encoder1, FALLING) ;
  attachInterrupt(PIN_C, encoder2, FALLING) ;
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((encoderFlag1 == true) || (encoderFlag2 == true)) {
    Serial.print(counter1) ;
    Serial.print("\t") ;
    Serial.println(counter2) ;

    encoderFlag1 = false ;
    encoderFlag2 = false ;
  }
}

void encoder1() {
  boolean state = digitalRead(PIN_B) ;
  if (state == 0) {
    counter1 -- ;
  }

  if (state == 1) {
    counter1 ++ ;
  }

  encoderFlag1 = true ;
}

void encoder2() {
  boolean state = digitalRead(PIN_B) ;
  if (state == 0) {
    counter2 -- ;
  }

  if (state == 1) {
    counter2 ++ ;
  }

  encoderFlag2 = true ;
}


//Very successful!!!!
//can use a common second pin easily
//need a resistor and cap pulled down to deal with bounce
//47 Ohm and 0.22 microfarad works well
//skips some clicks when turning fast, and adds extra steps everyonce and a while
