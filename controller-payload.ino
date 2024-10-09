// THIS IS A WIP
// Use at your own risk :)
// setup for a esp32 vroom


#ifdef ARDUINO_ARCH_ESP32
#include <ESP32Servo.h>
Servo servo;


#define RelayPin1 14  //D1


void toggleActuator(uint8_t brightness)
{
// Simulate press in
  if (brightness == 255)
    {

      servo.write(0);
      delay(1000);
      
      Serial.println("Switch ON");
    }
  else
  {
    servo.write(100);
    delay(1000);
    servo.write(0);
    Serial.println("Switch OFF");
  }
}