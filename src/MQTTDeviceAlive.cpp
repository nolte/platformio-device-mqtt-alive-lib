#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "MQTTDeviceAlive.h"
#include <DeviceAliveMessage.h>

#ifndef MQTTALIVETOPIC
	#define MQTTALIVETOPIC "/iot/devices"
#endif

MQTTDeviceAlive::MQTTDeviceAlive(DeviceAliveMessage message, PubSubClient mqttClient )
{
  _message = message;
  _mqttClient = mqttClient;
}

void MQTTDeviceAlive::doALiveCheckMessage()
{
		 // Length (with one extra character for the null terminator)
		 char* jsonMessage =  _message.toJson();
		 char test[] = MQTTALIVETOPIC ;
		 _mqttClient.publish(test,jsonMessage);
}

