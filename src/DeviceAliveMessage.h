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
	DeviceAliveMessage(String deviceId, IPAddress ip,const char** features );
	char * toJson();
  private:
    String _deviceId;
    IPAddress _ip;
    const char ** _features;
};

#endif
