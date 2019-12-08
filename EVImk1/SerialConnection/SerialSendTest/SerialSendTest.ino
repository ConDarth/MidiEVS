
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600) ;
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=16380; i<16400; i++) {
    sendData(0, i) ;
    delay(500) ;
  }
}

void sendData(int dataType, int data) {
  int dataSize = 0 ;
  if (data < 128) {
    dataSize = 1 ;
  } else if (data < 16384) {
    dataSize = 2 ;
  } else {
    dataSize = 3 ;
  }
  int commandByte = 128 ;
  commandByte += dataSize<<4 ;
  commandByte += dataType ;
  int dataByte[dataSize] ;
  for (int i=0; i<dataSize; i++) {
    dataByte[i] = (data>>(i*7)) ;
    dataByte[i] = dataByte[i]&127 ;
  }  

  Serial.write(commandByte) ;
  for (int i=0; i<dataSize; i++) {
    Serial.write(dataByte[i]) ;
  }  
}
