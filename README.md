# robotClaw
Multiple ways to program an ESP8266 driven robotic claw



# MQTT

*  Source code for uploading to your ESP8266.
*  This programm will connect to an MQTT broker (mqtt_broker) and drive a servo
*  in this example the esp is listening on topic : topic
*  and publishing on topicpub
*  You can connect by installing MQTT explorer or any other MQTT client.
*  If you setup your own broker, you will have to set it up and also set the username and password.

# Workshopclaw

*  Source code for uploading to your ESP8266.
*  This program shows will provide a wifi access point and host a simple web page.  
*  When you connect to the accesspoint "clawrobot1" with password "password1", you can surf to the controllers page.
*  Your wifi card will get an IP and a gateway address (ip of the accesspoint).  Browse to http://192.168.4.1 (ip accesspoint)
*  By passing left and right in the URL you can drive 2 servo motors.
*  A standard hobby servo(180 degrees) is used for this claw.
*  example :  http://192.168.1.4/?left=0&right=0 (claw fully open)
*  example :  http://192.168.1.4/?left=180 (claw fully closed)