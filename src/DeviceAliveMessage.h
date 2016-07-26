#ifndef DeviceAliveMessage_h
#define DeviceAliveMessage_h

#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h>

class DeviceAliveMessage
{
  public:
	DeviceAliveMessage();
	DeviceAliveMessage(String deviceId, IPAddress ip);
	char * toJson();
  private:
    String _deviceId;
    IPAddress _ip;
};

#endif
