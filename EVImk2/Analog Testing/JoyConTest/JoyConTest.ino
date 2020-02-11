#define JOYSTICK_X_PIN A0
#define JOYSTICK_Y_PIN A1
#define JOYSTICK_BUTTON 2 

int xVal = 0 ;
int yVal = 0 ;
boolean buttonVal = 1 ; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600) ;
  
  pinMode(JOYSTICK_BUTTON, INPUT_PULLUP) ;
}

void loop() {
  // put your main code here, to run repeatedly:
  xVal = analogRead(JOYSTICK_X_PIN) ;
  yVal = analogRead(JOYSTICK_Y_PIN) ;
  buttonVal = digitalRead(JOYSTICK_BUTTON) ;

  Serial.print(xVal) ;
  Serial.print("\t") ;
  Serial.print(yVal) ;
  Serial.print("\t") ;
  Serial.println(buttonVal) ;
  
}
