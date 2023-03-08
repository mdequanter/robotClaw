/*
*  Source code for uploading to your ESP8266.
*  This program shows will provide a wifi access point and host a simple web page.  
*  When you connect to the accesspoint "clawrobot1" with password "password1", you can surf to the controllers page.
*  Your wifi card will get an IP and a gateway address (ip of the accesspoint).  Browse to http://192.168.4.1 (ip accesspoint)
*  By passing left and right in the URL you can drive 2 servo motors.
*  A standard hobby servo(180 degrees) is used for this claw.
*  example :  http://192.168.1.4/?left=0&right=0 (claw fully open)
*  example :  http://192.168.1.4/?left=180 (claw fully closed)
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "clawrobot1";
const char *password = "password1";

String url;


#include "Servo.h";

int servo_pin1 = 2;  // for ESP8266 microcontroller


Servo myservo1;

int servospeed1 = 0;
String left;


ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
  server.send(200, "text/html", "<h1>Claw Robot</h1><br><a href=?left=0>OPEN</a><br><a href=?left=180>CLOSE</a>");
}

void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");
  //You can remove the password parameter if you want the AP to be open.
  
  WiFi.softAP(ssid,password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);


  /*
   * Use this code to connect to existant network

  //WiFi.mode(WIFI_STA);
  //WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  */
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
  myservo1.attach(servo_pin1);
  myservo1.write(servospeed1);

}

void loop() {
  server.handleClient();
  if (server.hasArg("left")) {
      if (left!=server.arg("left")) {
        left = server.arg("left");
        servospeed1 = left.toInt();
        myservo1.write(servospeed1);
      }     
    }
    delay (15);
}
