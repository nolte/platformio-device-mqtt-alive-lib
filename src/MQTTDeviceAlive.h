#ifndef MQTTDeviceAlive_h
#define MQTTDeviceAlive_h

#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <DeviceAliveMessage.h>

class MQTTDeviceAlive
{
  public:
	MQTTDeviceAlive(DeviceAliveMessage message, PubSubClient mqttClient);
    void doALiveCheckMessage(long currentMillis);
  private:
    DeviceAliveMessage _message;
    PubSubClient _mqttClient;
    long _previousMillis;
    long _interval;
};

#endif
