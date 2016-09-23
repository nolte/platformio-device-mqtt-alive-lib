/**
 * 
 */
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <MqttDeviceAlliveMessage.h>


// MAC Adresse des Ethernet Shields
byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xFF };
// Device IP Address
IPAddress ip(192, 168, 178, 4);
// IP des MQTT Servers
IPAddress mqttBroker(192, 168, 178, 63);
// using build parameter for mqtt device id
char DEVICE_ID[] = "MQTTDEVICEID";

EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

char MQTT_A_LIVE_TOPIC[] = "/iot/devices";
const char *features[] = { "ir-command-receiving" };

MqttDeviceAlliveMessage aliveMessage(mqttClient,MQTT_A_LIVE_TOPIC,DEVICE_ID,features);
const long _interval = 5000;
unsigned long previousMillis = 0;


long lastReconnectAttempt = 0;

boolean reconnect() {
  if (mqttClient.connect()) {
    // Once connected, publish an announcement...
	  aliveMessage.sendAliveMessage(ip);
  }
  return mqttClient.connected();
}

void setup() {
	Serial.begin(9600);

	mqttClient.setServer(mqttBroker, 1883);
	Ethernet.begin(mac, ip);
	// Allow the hardware to sort itself out
	delay(2500);
	Serial.println("Try To Start");
	Serial.println("Start MQTT Alive Check");
	lastReconnectAttempt = 0;
}

void loop() {
	long now = millis();
	if (!mqttClient.connected(DEVICE_ID)) {
		// reconnect to the broker
		if (now - lastReconnectAttempt > 5000) {
			lastReconnectAttempt = now;
			// Attempt to reconnect
			if (reconnect()) {
				lastReconnectAttempt = 0;
			}
		}
	} else {
		
		aliveMessage.sendAliveMessage(ip);
		
		
		mqttClient.loop();
	}
}
