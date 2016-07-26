/**
 Receiving IR Commands and send the Command to a MQTT Topic
 */
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <DeviceAliveMessage.h>
#include <MQTTDeviceAlive.h>

// MAC Adresse des Ethernet Shields
byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xFF };

IPAddress ip(192, 168, 178, 75);

// IP des MQTT Servers
char server[] = "maxchen";
char DEVICE_ID[] = "ir-sender-livingroom";

// Callback function header
void callback(char* topic, byte* payload, unsigned int length);
EthernetClient apiClient;
PubSubClient mqttClient(server, 1883, callback, apiClient);

// char *features[] = { "testmessage", "testmessage2",  "testmessage3"};
DeviceAliveMessage deviceAliveMessage(String(DEVICE_ID), ip);
MQTTDeviceAlive mqttDeviceAlive(deviceAliveMessage, mqttClient);

void setup() {
	Serial.begin(9600);
	Ethernet.begin(mac, ip);
	// Allow the hardware to sort itself out
	delay(2500);
	if (mqttClient.connect(DEVICE_ID)) {
		Serial.println("Connected");
	} else {
		Serial.println("Not Connected");
	}
	Serial.println("Start MQTT Alive Check");
	unsigned long currentMillis = millis();
	mqttDeviceAlive.doALiveCheckMessage(currentMillis);
}

void loop() {
	unsigned long currentMillis = millis();
	mqttDeviceAlive.doALiveCheckMessage(currentMillis);
	mqttClient.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
	Serial.println("Start MQTT IR Sender Hub");
}

