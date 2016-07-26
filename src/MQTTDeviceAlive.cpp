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
  _interval = 30000;
  _mqtt_health_check_path = "/iot/devices";
}

void MQTTDeviceAlive::doALiveCheckMessage(long currentMillis)
{
	 if (currentMillis - _previousMillis >= _interval) {
		 Serial.println("doALiveCheckMessage");
		 _previousMillis = currentMillis;
		 // Length (with one extra character for the null terminator)
		 int str_len = _mqtt_health_check_path.length() + 1;
		 // Prepare the character array (the buffer)
		 char char_array[str_len];
		 // Copy it over
		 _mqtt_health_check_path.toCharArray(char_array, str_len);
		 char* jsonMessage =  _message.toJson();
		 _mqttClient.publish(char_array,jsonMessage);
	 }
}

