/**
 * 
 */
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <DeviceAliveMessage.h>
#include <MQTTDeviceAlive.h>

// fall back for missing build attributes
#ifndef MQTTDEVICEID
	#define MQTTDEVICEID "id-not-set"
#endif

#ifndef MQTTHOST
	#define MQTTHOST "dummyMQTTHost"
#endif

// MAC Adresse des Ethernet Shields
byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xFF };

IPAddress ip(192, 168, 178, 4);

char DEVICE_ID[] = MQTTDEVICEID;

// Callback function header
void callback(char* topic, byte* payload, unsigned int length);
EthernetClient ethClient;
PubSubClient mqttClient(ethClient);


const char *features[] = { "featureA", "featureB", "featureC" };
DeviceAliveMessage deviceAliveMessage(String(DEVICE_ID), ip,features);
MQTTDeviceAlive mqttDeviceAlive(deviceAliveMessage, mqttClient);

const long _interval = 10000;
unsigned long previousMillis = 0;


long lastReconnectAttempt = 0;

boolean reconnect() {
  if (mqttClient.connect(DEVICE_ID)) {
    // Once connected, publish an announcement...
	  mqttDeviceAlive.doALiveCheckMessage();
  }
  return mqttClient.connected();
}

void setup() {
	Serial.begin(9600);

	mqttClient.setServer(MQTTHOST, 1883);
	Ethernet.begin(mac, ip);
	// Allow the hardware to sort itself out
	delay(2500);
	Serial.println("Try To Start");
	Serial.println("Start MQTT Alive Check");
	lastReconnectAttempt = 0;
}

void loop() {
	long now = millis();
	if (!mqttClient.connected()) {
		// reconnect to the broker
		if (now - lastReconnectAttempt > 5000) {
			lastReconnectAttempt = now;
			// Attempt to reconnect
			if (reconnect()) {
				lastReconnectAttempt = 0;
			}
		}
	} else {
		// Client connected
		if (now - previousMillis > _interval) {
			previousMillis = now;
			// Attempt to reconnect
			mqttDeviceAlive.doALiveCheckMessage();
		}
		
		
		mqttClient.loop();
	}
}
