#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

void setup() {

  Serial.begin(115200);

  WiFiManager wifiManager;

  wifiManager.resetSettings();

  wifiManager.autoConnect("FlashLoveAutoConnect");

  Serial.println("CONNECTION SUCCESSFULLY DONE");
}

void loop() {

  Serial.println("HELLO WORLD");

  delay(2000);
}
