#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <stdint.h>

#define STM32_ADDRESS 0x33    //address of STM32 Nucleo 

LiquidCrystal_I2C lcd(0x27, 16, 2);   //LCD interface


uint8_t receivedData = 0, sentData = 0;
uint16_t level = 0;

void setup() {
  //setting up i2c
  Wire.begin(STM32_ADDRESS);  
  Wire.onRequest(requestEvent);   //requestEvent is called when data is requested by STM32 
  Wire.onReceive(receiveEvent);   //receiveEvent is called when data is received from STM32

  //lcd setup
  lcd.init(); // initialize the lcd
  lcd.backlight(); // Turn on backlight
  
  Serial.begin(9600);
}

void loop() 
{ 
    lcd.setCursor(0, 0);
    lcd.print("Level: ");
    lcd.print(level);  
}

void requestEvent()   //when data is requested by the STM32
{
  Wire.write(String(sentData).c_str());  
}

void receiveEvent(int howMany)   //when data is received from the STM32
{
  receivedData = Wire.read();

  if (receivedData > 2)
  {
    level = receivedData - 2;
  }
}
