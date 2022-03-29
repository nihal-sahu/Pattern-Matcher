#include <Wire.h> 

#define DEVICE_ID 0x33 
int counter = 0;

void setup() {
  Wire.begin(DEVICE_ID);  
  Wire.onRequest(requestEvent); 

  Serial.begin(9600);
}

void loop() { }

void requestEvent()
{
  counter++;
  String data = "Counter from Arduino: " + String(counter);
  Serial.println(data);
  Wire.write(data.c_str());  
}
