#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <LEDMatrixDriver.hpp>

#include <Wire.h>
#include "SSD1306.h"
#include <qrcode.h>

//LED HEART
const uint8_t LEDMATRIX_CS_PIN = 15;
const int LEDMATRIX_WIDTH = 31;
const int LEDMATRIX_HEIGHT = 7;
const int LEDMATRIX_SEGMENTS = 4;
LEDMatrixDriver lmd(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN);
int values[LEDMATRIX_WIDTH];

//OLED QrCode
//21 & 22 are ESP connection pins
//03xc is device I2C address
SSD1306 display(0x3c, 21, 22);
QRcode qrcode (&display);

//Pulse sensor
int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13;   //  The on-board Arduion LED
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore.


void setup() {
  Serial.begin(115200);

  //Wifi Manager
  /*
  WiFiManager wifiManager;
  wifiManager.resetSettings();
  wifiManager.setDebugOutput(true);
  wifiManager.autoConnect("FlashLuv","FlashLuv");
  Serial.println("CONNECTION SUCCESSFULLY DONE");
  */

  //OLED QrCode
  /*
  dispaly.init();
  display.display();
  qrcode.init();
  qrcode.create("Hello World");
  */

  //pulse sensor
  /*
    pinMode(LED13,OUTPUT);                      // pin that will blink to your heartbeat!
  */

  //LEAD HEART
  lmd.setEnabled(true);
  lmd.setIntensity(2);

  for(int i=0; i<LEDMATRIX_WIDTH; i++){
     values[i] = 1;
  }

}

void loop() {

  Serial.println("HELLO WORLD");

  //pulse Sensor
  /*
  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.

    //Call insert newVal here

  Serial.println(Signal);                    // Send the Signal value to Serial Plotter.
  if(Signal > Threshold){                          // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
     digitalWrite(LED13,HIGH);
  } else {
     digitalWrite(LED13,LOW);                //  Else, the sigal must be below "550", so "turn-off" this LED.
  }
  */


  //led panels
  /* insertNewVal( random(100,999) ); */

  delay(100);

}

void insertNewVal(int newVal){
    int cast_ = newVal/100;
    if (cast_ > LEDMATRIX_HEIGHT ){
      cast_ = LEDMATRIX_HEIGHT;
      }

    for(int i= LEDMATRIX_WIDTH ; i > 0; i--) {
         values[i] =  values[i-1];
     }

    values[0] = cast_;

     setGraph();
 }

void setGraph(){
    for(int i=0; i<LEDMATRIX_WIDTH; i++) {
      delay(10);
      turnOn(i,i,values[i]);
      delay(10);
    }
 }

void turnOn(int x, int y, int h){

   for(int i=0; i<LEDMATRIX_HEIGHT; i++){
     lmd.setPixel(x, i, false);
     lmd.display();
    }

    for (int i = 0; i < h; i++){
      lmd.setPixel(x, i, true);
      lmd.display();
    }

 }
