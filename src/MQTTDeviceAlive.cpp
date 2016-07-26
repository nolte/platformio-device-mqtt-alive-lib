#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "MQTTDeviceAlive.h"

String DisplayAddress(IPAddress address)
{
  return String(address[0]) + "." +
         String(address[1]) + "." +
         String(address[2]) + "." +
         String(address[3]);
}

MQTTDeviceAlive::MQTTDeviceAlive(String deviceId,IPAddress ip,PubSubClient mqttClient)
{
  _deviceId = deviceId;
  _ip = ip;
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

