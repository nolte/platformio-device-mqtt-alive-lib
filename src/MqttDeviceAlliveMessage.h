#ifndef MqttDeviceAlliveMessage_h
#define MqttDeviceAlliveMessage_h

#include "Arduino.h"

class MqttDeviceAlliveMessage
{
	public:
	  MqttDeviceAlliveMessage(PubSubClient client,const char* mqtt_topic,char* device_id);
	  MqttDeviceAlliveMessage(PubSubClient client,const char* mqtt_topic,char* device_id,const char** features);
	  void sendAliveMessage(IPAddress ip,boolean state);
	  void sendAliveMessage(IPAddress ip);
	private:
	  PubSubClient _client;
	  const char* _mqtt_topic;
	  char* _device_id;
	  const char** _features;
	  int _feature_array_size;
	  void publishMessage(String jsonString);
};

#endif