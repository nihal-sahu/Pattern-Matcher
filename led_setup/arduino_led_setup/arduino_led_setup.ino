#include <Wire.h> 
#include <stdint.h>

#define STM32_ADDRESS 0x33    //address of STM32 Nucleo 
int counter = 0;

uint8_t receivedData, sentData;

void setup() {
  //setting up i2c
  Wire.begin(STM32_ADDRESS);  
  Wire.onRequest(requestEvent);   //requestEvent is called when data is requested by STM32 
  Wire.onReceive(receiveEvent);   //receiveEvent is called when data is received from STM32
  
  Serial.begin(9600);
}

void loop() { }

void requestEvent()   //when data is requested by the STM32
{
  counter++;

  if (counter > 9)
    counter = 0;
  String data = "Counter from Arduino: " + String(counter);
  Serial.println(data);
  Wire.write(data.c_str());  
}

void receiveEvent(int howMany)   //when data is received from the STM32
{
  receivedData = Wire.read();
  Serial.println(int(receivedData));
  delay(1000);
}
