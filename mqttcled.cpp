/*
  SimpleMQTTClient.ino
  The purpose of this exemple is to illustrate a simple handling of MQTT and Wifi connection.
  Once it connects successfully to a Wifi network and a MQTT broker, it subscribe to a topic and send a message to it.
  It will also send a message delayed 5 seconds later.
*/
 
#include "EspMQTTClient.h"
 
#define TOPIC_DEFAULT "eia/test_2"
 
String myTopic = (String)TOPIC_DEFAULT;
unsigned long int lastTime = 0;
 
EspMQTTClient client(
  "PruebasHW",
  "Smt2017*",
  "iottest45.cloud.shiftr.io", // MQTT Broker server ip
  "iottest45",                 // Can be omitted if not needed
  "nFkl77W5JqpvzAXg",                      // Can be omitted if not needed
  "ESP32",                        // Client name that uniquely identify your device
  1883                                     // The MQTT port, default to 1883. this line can be omitted
);
 
void setup()
{
  Serial.begin(115200);
  pinMode(2, OUTPUT);
 
  // Optional functionalities of EspMQTTClient
  client.enableDebuggingMessages();                                    // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater();                                       // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA();                                                  // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  // client.enableLastWillMessage(myTopic.c_str(), "I am going offline"); // You can activate the retain flag by setting the third parameter to true
}
 
// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{
 
  client.subscribe("led", [](const String & topic, const String & payload)
  {
    Serial.println("topic: " + topic + ", payload: " + payload);
    if (payload.equals("ON"))
    {
      Serial.print("Power ON, ");
      digitalWrite(2, HIGH);
    }
    else if (payload.equals("OFF"))
    {
      Serial.print("Power OFF, ");
      digitalWrite(2, LOW);
    }
  });
 
  // Publish a message to "mytopic/test"
  // client.publish(myTopic.c_str(), "This is a message"); // You can activate the retain flag by setting the third parameter to true
}
 
void loop()
{
  client.loop();
  //  if (millis() - lastTime > 10000 && client.isConnected())
  //  {
  //    client.publish(myTopic.c_str(), "{\"temperature\":25, \"humidity\":\"80%\"}");
  //    lastTime = millis();
  //  }
}