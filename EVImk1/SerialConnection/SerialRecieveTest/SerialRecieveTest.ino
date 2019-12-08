boolean recievingData = false ;
int newDataNum = 0 ;
int recievedDataSize = 4 ;
byte newData[4] ;

int data1 = 0 ;
int data2 = 0 ;

byte lastByte = 0 ;

long lastTime = 0 ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200) ;
  Serial2.begin(115200) ;
}

void loop() {
  getData() ;
  
  Serial.print(data1) ;
  Serial.print("\t") ;
  Serial.print(data2) ;
  Serial.print("\t") ;
}

void getData() {
  while (Serial2.available() > 0) {
    //Serial.println(Serial2.peek()) ;
    byte newByte = Serial2.read() ;

    if (recievingData) {
      newData[newDataNum] = newByte ;
      newDataNum ++ ;
      if (newDataNum >= recievedDataSize) {
        recievingData = false ;
        formatData() ;
      }
    } else if ((newByte == 0xff) && (lastByte == 0xff)) {
      //Serial.println("new message") ;
      recievingData = true ;
      newDataNum = 0 ;
    }

    lastByte = newByte ;
  } 
}

void formatData() {
  data1 = newData[0] ;
  data1 += newData[1]<<8 ;
  data2 = newData[2] ;
  data2 += newData[3]<<8 ;
}
