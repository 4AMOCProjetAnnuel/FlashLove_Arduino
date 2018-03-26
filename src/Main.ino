#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include <Wire.h>
#include "SSD1306.h"
#include <qrcode.h>

//21 & 22 are ESP connection pins
//03xc is device I2C address

SSD1306 display(0x3c, 21, 22);
QRcode qrcode (&display);

void setup() {
  Serial.begin(115200);
  WiFiManager wifiManager;

  wifiManager.resetSettings();
  wifiManager.setDebugOutput(true);
  wifiManager.autoConnect("FlashLuv","FlashLuv");
  Serial.println("CONNECTION SUCCESSFULLY DONE");

  display.init();
  display.display();

  qrcode.init();
  qrcode.create("Hello World");

}

void loop() {

  Serial.println("HELLO WORLD");

  delay(2000);
}
