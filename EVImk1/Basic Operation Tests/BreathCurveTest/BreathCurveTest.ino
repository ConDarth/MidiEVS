int breathCurveRates[5] = { 3, 6, 20, 80, 400} ;

//slope for each quantized section [0,1]
float breathCurveSlope[4][10] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //constant slope
                                  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},   //linear slope
                                  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //logarithmic slope
                                  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} } ;//exponential slope

//intercept for each quantized section [0,16383]
int breathCurveIntercept[4][10] = { { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},   //constant intercept
                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //linear intercept
                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //logarithmic intercept
                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} } ;//exponential intercept


int pressure = 10500 ;

boolean breathPrint = true ;
unsigned long lastTime = 0 ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400) ;
  
  breathLogCurve(0) ;
  breathExpCurve(0) ;
}

void loop() {
  // put your main code here, to run repeatedly
  if (breathPrint) {
    breathPrint = false ;

    lastTime = micros() ;
    pressure = processBreathData(2, pressure) ;
    Serial.println(micros() - lastTime) ;
    Serial.println() ;
    Serial.println(pressure) ;
  }
}

int processBreathData(int bcNum, int rawData) {
  int quanta = 0;
  int raw = rawData ;
  
  if (rawData > 14745) {
    quanta = 9 ;
  } else if (rawData > 13106) {
    quanta = 8 ;
  } else if (rawData > 11468) {
    quanta = 7 ;
  } else if (rawData > 9830) {
    quanta = 6 ;
  } else if (rawData > 8192) {
    quanta = 5 ;
  } else if (rawData > 6553) {
    quanta = 4 ;
  } else if (rawData > 4915) {
    quanta = 3 ;
  } else if (rawData > 3277) {
    quanta = 2 ;
  } else if (rawData > 1638) {
    quanta = 1 ;
  } else {
    quanta = 0 ;
  }
  
  int processedData = breathCurveSlope[bcNum][quanta]*rawData + breathCurveIntercept[bcNum][quanta] ;
  return processedData ;
}

void breathLogCurve(int rate) {
  float bcValue[11] ;
  for (int i=0; i<=10; i++) {
    bcValue[i] = -breathCurveRates[rate]*( pow(breathCurveRates[rate], (float) -i/10) - 1) / (breathCurveRates[rate] - 1) ;
  }
  for (int i=0; i<10; i++) {
    breathCurveSlope[2][i] = 10*(bcValue[i+1] - bcValue[i]) ;
  }
  for (int i=0; i<10; i++) {
    breathCurveIntercept[2][i] = 16383*(bcValue[i] - (breathCurveSlope[2][i]*i/10)) ;
  }  
}

void breathExpCurve(int rate) {
  float bcValue[11] ;
  for (int i=0; i<=10; i++) {
    bcValue[i] =(pow(breathCurveRates[rate], (float) i/10) - 1) / (breathCurveRates[rate] - 1) ;
  }
  for (int i=0; i<10; i++) {
    breathCurveSlope[3][i] = 10*(bcValue[i+1] - bcValue[i]) ;
  }
  for (int i=0; i<10; i++) {
    breathCurveIntercept[3][i] = 16383*(bcValue[i] - (breathCurveSlope[3][i]*i/10)) ;
  }
}
