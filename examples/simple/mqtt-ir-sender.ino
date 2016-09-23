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

MqttDeviceAlliveMessage aliveMessage(mqttClient, MQTT_A_LIVE_TOPIC, DEVICE_ID,
		features);

const long _interval = 5000;
unsigned long previousMillis = 0;

long lastReconnectAttempt = 0;

void reconnect() {
	// Loop until we're reconnected
	while (!mqttClient.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (mqttClient.connect(DEVICE_ID)) {
			Serial.println("connected");
		} else {
			Serial.print("failed, rc=");
			Serial.print(mqttClient.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void setup() {
	Serial.begin(9600);

	mqttClient.setServer(mqttBroker, 1883);
	Ethernet.begin(mac, ip);
	// Allow the hardware to sort itself out
	delay(2500);
	Serial.println("Try To Start");
	Serial.println("Start MQTT Alive Check");
}

void loop() {
	if (!mqttClient.connected()) {
		reconnect();
	}
	mqttClient.loop();
	aliveMessage.sendAliveMessage(ip);
	delay(60000);

}
}
