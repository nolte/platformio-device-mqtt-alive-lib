#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h>
#include <DeviceAliveMessage.h>

String DisplayAddress(IPAddress address)
{
  return String(address[0]) + "." +
         String(address[1]) + "." +
         String(address[2]) + "." +
         String(address[3]);
}

DeviceAliveMessage::DeviceAliveMessage()
{
	Serial.println("DeviceAliveMessage default");
}

DeviceAliveMessage::DeviceAliveMessage(String deviceId,IPAddress ip, char *features[])
{
  _deviceId = deviceId;
  _ip = ip;
  *_features = *features;
}

char *DeviceAliveMessage::toJson()
{
	Serial.println("toJson");
	StaticJsonBuffer<200> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();
	root["id"] = _deviceId;
	root["ip"] = DisplayAddress(_ip);
	String jsonString = "";
	root.printTo(jsonString);
	int commandLenJson = jsonString.length() + 1;
	char message_buffCommandJson[commandLenJson];
	jsonString.toCharArray(message_buffCommandJson, commandLenJson);

	//result message ->>>> message_buffCommandJson

}

