#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "MQTTDeviceAlive.h"
#include <DeviceAliveMessage.h>

MQTTDeviceAlive::MQTTDeviceAlive(DeviceAliveMessage message, PubSubClient mqttClient )
{
  _message = message;
  _mqttClient = mqttClient;
  _interval = 3000;
}

void MQTTDeviceAlive::doALiveCheckMessage(long currentMillis)
{
	 if (currentMillis - _previousMillis >= _interval) {
		 _previousMillis = currentMillis;
		 Serial.println("doALiveCheckMessage");
	 }
}

