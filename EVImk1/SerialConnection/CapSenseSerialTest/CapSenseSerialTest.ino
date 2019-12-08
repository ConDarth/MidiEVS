#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */
int pBUp = 0 ;
int pBDown = 0 ;

CapacitiveSensor   pBUpSensor = CapacitiveSensor(2, 3);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   pBDownSensor = CapacitiveSensor(2, 4);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

void setup() {
   Serial.begin(115200);
}

void loop() {
  pBUp = pBUpSensor.capacitiveSensor(30);
  pBDown = pBDownSensor.capacitiveSensor(30);
  sendData(pBUp, pBDown) ;
}

void sendData(int data1, int data2) {
  int commandByte = 0xff ;
  int dataByte[4] ;
  dataByte[0] = data1&255 ;
  dataByte[1] = data1>>8 ;
  dataByte[2] = data2&255 ;
  dataByte[3] = data2>>8 ;

  Serial.write(commandByte) ;
  Serial.write(commandByte) ;
  Serial.write(dataByte[0]) ;
  Serial.write(dataByte[1]) ;
  Serial.write(dataByte[2]) ;
  Serial.write(dataByte[3]) ;
}
