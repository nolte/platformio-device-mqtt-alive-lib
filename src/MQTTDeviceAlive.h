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
    void doALiveCheckMessage();
  private:
    DeviceAliveMessage _message;
    PubSubClient _mqttClient;
    String _mqtt_health_check_path;
};

#endif
