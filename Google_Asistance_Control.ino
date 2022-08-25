
#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>


#define Relay1      D1
#define Relay2      D2
#define Relay3      D3
#define Relay4      D4

#define WLAN_SSID "YOUR_SSID"    //my SSID
#define WLAN_PASS "YOUR_PASS"    // my Password

/************************ Adafruit.io Setup**********************/

#define IO_SERVER "io.adafruit.com" // Adafruit Server
#define IO_SERVERPORT 1883
#define IO_USERNAME  "ManishIOT"
#define IO_KEY       "aio_bLjj00zQ04jLWgE6HddX8ckeo5Wb"

//WIFI CLIENT

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, IO_SERVER,IO_SERVERPORT,IO_USERNAME,IO_KEY);

Adafruit_MQTT_Subscribe Light1 = Adafruit_MQTT_Subscribe(&mqtt, IO_USERNAME"/feeds/Relay1");    // Feeds name should be same everywhere
Adafruit_MQTT_Subscribe Light2 = Adafruit_MQTT_Subscribe(&mqtt, IO_USERNAME"/feeds/Relay2");
Adafruit_MQTT_Subscribe Light3 = Adafruit_MQTT_Subscribe(&mqtt, IO_USERNAME"/feeds/Relay3");
Adafruit_MQTT_Subscribe Light4 = Adafruit_MQTT_Subscribe(&mqtt, IO_USERNAME"/feeds/Relay4");

void MQTT_connect();

void setup(){
  
Serial.begin(115200);

pinMode(Relay1, OUTPUT);
pinMode(Relay2, OUTPUT);
pinMode(Relay3, OUTPUT);
pinMode(Relay4, OUTPUT);

// Connect WiFi access point.

Serial.println();Serial.println();
Serial.print("Connecting to");
Serial.println(WLAN_SSID);

WiFi.begin(WLAN_SSID, WLAN_PASS);
while(WiFi.status() !=WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
Serial.println();

Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());

mqtt.subscribe(&Light1);
mqtt.subscribe(&Light2);
mqtt.subscribe(&Light3);
mqtt.subscribe(&Light4);
}

void loop()
{
 MQTT_connect();

 Adafruit_MQTT_Subscribe *subscription;
 while ((subscription = mqtt.readSubscription(20000))) {
if (subscription == &Light1){
Serial.print(F("Got: "));
Serial.println((char *)Light1.lastread);
int Light1_State = atoi((char *)Light1.lastread);
digitalWrite(Relay1, Light1_State);
  
}

if (subscription == &Light2){
Serial.print(F("Got: "));
Serial.println((char *)Light2.lastread);
int Light2_State = atoi((char *)Light2.lastread);
digitalWrite(Relay2, Light2_State);
  
}

if (subscription == &Light3){
Serial.print(F("Got: "));
Serial.println((char *)Light3.lastread);
int Light3_State = atoi((char *)Light3.lastread);
digitalWrite(Relay3, Light3_State);
  
}

if (subscription == &Light4){
Serial.print(F("Got: "));
Serial.println((char *)Light4.lastread);
int Light4_State = atoi((char *)Light4.lastread);
digitalWrite(Relay4, Light4_State);
  
}
 }}

void MQTT_connect(){
  int8_t ret;

  if (mqtt.connected()){
    return;
  }
Serial.print("connecting to MQTT... ");

uint8_t retries = 3;

while((ret = mqtt.connect()) != 0){
  Serial.println(mqtt.connectErrorString(ret));
  Serial.println("Retrying MQTT connection in 5 second... ");
mqtt.disconnect();
delay(5000);
retries--;
if(retries == 0) {
  while(1);
}
while(1);

}
Serial.println("MQIT Connected!");
}
