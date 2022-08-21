#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define SSID "WIFI_SSID"
#define PASS "WIFI_PASSWORD"

int pin = D1;
ESP8266WebServer webserver(80);

void unlock(){
    if(webserver.hasArg("secretPhrase")){
      digitalWrite(pin,HIGH);
      delay(1750);
      digitalWrite(pin,LOW);
    }
  webserver.send(200, "text/html", "Door has been opened (?)"); 
}

void setup() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);

  WiFi.begin(SSID,PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  
  // to unlock door, goto http://ipaddress/unlock?secretPhrase
  webserver.on("/unlock", unlock);
  webserver.begin();
}

void loop() {
  webserver.handleClient();
}
