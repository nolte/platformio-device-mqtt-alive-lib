#ifndef MQTTDeviceAlive_h
#define MQTTDeviceAlive_h

#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

class MQTTDeviceAlive
{
  public:
	MQTTDeviceAlive(String deviceId, IPAddress ip, PubSubClient mqttClient);
    void doALiveCheckMessage(long currentMillis);
  private:
    String _deviceId;
    IPAddress _ip;
    PubSubClient _mqttClient;
    long _previousMillis;
    long _interval;
	String DisplayAddress(IPAddress address);
};

#endif
