/*
*  Source code for uploading to your ESP8266.
*  This programm will connect to an MQTT broker (mqtt_broker) and drive a servo
*  in this example the esp is listening on topic : topic
*  and publishing on topicpub
*  You can connect by installing MQTT explorer or any other MQTT client.
*  If you setup your own broker, you will have to set it up and also set the username and password.
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "Servo.h";
Servo myservo1;

int servospeed1 = 0;
String left;
int servo_pin1 = 2;  // for ESP8266 microcontroller


// WiFi
const char *ssid = "xxxx"; // Enter your WiFi name
const char *password = "xxx";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "robotclaw/pos";
const char *topicpub = "robotclaw/pospub";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // Set software serial baud to 115200;
  Serial.begin(115200);
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
      String client_id = "esp8266-client-";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
      if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
          Serial.println("Public emqx mqtt broker connected");
      } else {
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  }
  // publish and subscribe

  myservo1.attach(servo_pin1);
  myservo1.write(servospeed1);
  
  client.publish(topic, "hello emqx");
  client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  if ((char) payload[0] == '1') {
    myservo1.write(0);
    Serial.println("open");
    client.publish(topicpub, "Claw open");
  }
  if ((char) payload[0] == '2') {
    myservo1.write(90);
    Serial.println("middle");
    client.publish(topicpub, "Claw middle");
  }
  if ((char) payload[0] == '3') {
    myservo1.write(180);
    Serial.println("close");
    client.publish(topicpub, "Claw closed");
  }

  
  for (int i = 0; i < length; i++) {
      Serial.print((char) payload[i]);
  }
  
  Serial.println();
  Serial.println("-----------------------");
}

void loop() {
  client.loop();
}
