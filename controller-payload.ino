// THIS IS A WIP
// Use at your own risk :)
// setup for a esp32 vroom


#ifdef ARDUINO_ARCH_ESP32
#include <ESP32Servo.h>
#include <WiFiClient.h>
#include <Espalexa.h>
Servo servo;
Espalexa espalexa;


#define RelayPin1 14  //D1

// Debugging creds
const char* ssid = "";
const char* password =   "";

void firstLightChanged(uint8_t brightness);


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

void loop()
{
  espalexa.loop();
  delay(1);
}

// bool for wifi state check
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  if (state) {
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}