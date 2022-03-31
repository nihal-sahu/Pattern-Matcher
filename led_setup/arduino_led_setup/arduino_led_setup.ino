#include <Wire.h> 
#include <stdint.h>

#define STM32_ADDRESS 0x33    //address of STM32 Nucleo 
int counter = 0;

uint8_t receivedData = 0, sentData = 0;
uint16_t level = 0;
uint8_t *led_pattern;

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
  Wire.write(sentData);  
}

void receiveEvent(int howMany)   //when data is received from the STM32
{
  receivedData = Wire.read();

  if (receivedData > 2)
  {
    led_pattern = new uint8_t[receivedData]; 
    level = receivedData;
    counter = receivedData;
  }
  else 
  {
    led_pattern[counter-1] = receivedData;
    counter--;
    
    if (counter < 0)
    {
      sentData = 3;
    }
  }
}
