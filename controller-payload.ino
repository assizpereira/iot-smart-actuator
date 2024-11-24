// THIS IS A WIP
// Use at your own risk :)
// setup for a esp32 vroom

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <WiFiClient.h>
#include <Espalexa.h>
#include <ESP32Servo.h>
Servo servo;


// define the GPIO connected with Relays
#define RelayPin1 14  //D1



// prototypes
boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);
//void secondLightChanged(uint8_t brightness);


// WiFi Credentials
const char* ssid = ""; // type your wifi name
const char* password =   ""; // type your wifi password


// device names
String Device_1_Name = "MCB";


boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  Serial.begin(115200);
  pinMode(RelayPin1, OUTPUT);
 // Serial.begin(115200);
  servo.attach(14);    // ESP32 Pin

  // Initialise wifi connection
  wifiConnected = connectWifi();

  if (wifiConnected)
  {
    // Define your devices here.
    espalexa.addDevice(Device_1_Name, firstLightChanged); //simplest definition, default state off

    

    espalexa.begin();
  }
  else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}

void loop()
{
  espalexa.loop();
  delay(1);
}

//our callback functions
void firstLightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness == 255)
    {

      servo.write(0);
      delay(1000);
      
      Serial.println("MCB ON");
    }
  else
  {
    servo.write(100);
    delay(1000);
    servo.write(0);
    Serial.println("MCB OFF");
  }
}


// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
