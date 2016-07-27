#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h>
#include <DeviceAliveMessage.h>

#if !defined(ARRAY_SIZE)
    #define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

String DisplayAddress(IPAddress address)
{
  return String(address[0]) + "." +
         String(address[1]) + "." +
         String(address[2]) + "." +
         String(address[3]);
}

DeviceAliveMessage::DeviceAliveMessage()
{
	// Serial.println("DeviceAliveMessage default");
}

DeviceAliveMessage::DeviceAliveMessage(String deviceId,IPAddress ip,const char** features, int feature_array_size )
{
  _deviceId = deviceId;
  _ip = ip;
  _features=features;
  _feature_array_size=feature_array_size;
}

char *DeviceAliveMessage::toJson()
{
	//  Serial.println("toJson");
	StaticJsonBuffer<500> jsonBuffer;
	JsonObject& root = jsonBuffer.createObject();
	root["id"] = _deviceId;
	root["ip"] = DisplayAddress(_ip);

	JsonArray& data = root.createNestedArray("features");
	for (int i = 0; i < _feature_array_size ; i++){
		data.add(_features[i]);
	}

	String jsonString = "";
	root.printTo(jsonString);
	int commandLenJson = jsonString.length() + 1;
	char message_buffCommandJson[commandLenJson];
	jsonString.toCharArray(message_buffCommandJson, commandLenJson);
    return message_buffCommandJson;
}

