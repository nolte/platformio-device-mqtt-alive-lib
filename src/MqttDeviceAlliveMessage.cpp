
#include "Arduino.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "MqttDeviceAlliveMessage.h"

String DisplayAddress(IPAddress address)
{
  return String(address[0]) + "." +
         String(address[1]) + "." +
         String(address[2]) + "." +
         String(address[3]);
}



MqttDeviceAlliveMessage::MqttDeviceAlliveMessage(PubSubClient client,const char* mqtt_topic,char* device_id)
{
  _client = client;
  _mqtt_topic = mqtt_topic;
  _device_id = device_id;
}

MqttDeviceAlliveMessage::MqttDeviceAlliveMessage(PubSubClient client,const char* mqtt_topic,char* device_id,const char** features,int feature_array_size)
{
  _client = client;
  _mqtt_topic = mqtt_topic;
  _device_id = device_id;
  _features = features;
  _feature_array_size = feature_array_size;
}

void MqttDeviceAlliveMessage::sendAliveMessage(IPAddress ip,boolean state)
{
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["id"] = _device_id;
  root["ip"] = DisplayAddress(ip);
  if(state){
    root["running"] = state;
  }

  if(_features){
  JsonArray& data = root.createNestedArray("features");
	  for (int i = 0; i < _feature_array_size ; i++){
		data.add(_features[i]);
	  }
  }

  String jsonString = "";
  root.printTo(jsonString);
  Serial.println(jsonString);
  publishMessage(jsonString);

}
void MqttDeviceAlliveMessage::sendAliveMessage(IPAddress ip)
{
 sendAliveMessage(ip,NULL);

}



void MqttDeviceAlliveMessage::publishMessage(String jsonString)
{
  int commandLenJson = jsonString.length()  + 1;
  char message_buffCommandJson[commandLenJson];
  jsonString.toCharArray(message_buffCommandJson, commandLenJson);
  _client.publish(_mqtt_topic, message_buffCommandJson);
}
