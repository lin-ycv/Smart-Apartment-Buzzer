#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define SSID "WIFI_SSID"
#define PASS "WIFI_PASSWORD"

const pin = D5;
ESP8266WebServer webserver(80);
const secret = "someSecretPhrase"

void unlock(){
    if(webserver.hasArg(secret)){
      digitalWrite(pin,HIGH);
      delay(1000);
      digitalWrite(pin,LOW);
    }
  webserver.send(200, "text/html", "Not found: /return"); 
}

void setup() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(SSID,PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  
  // to unlock door, goto http://ipaddress/unlock?secretPhrase
  webserver.on("/unlock", unlock);
  webserver.begin();
}

void loop() {
  webserver.handleClient();
}
