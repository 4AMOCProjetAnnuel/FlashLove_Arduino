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

  dispaly.init();
  display.display();

  qrcode.init();
  qrcode.create("Hello World");

  //LEAD HEART
  lmd.setEnabled(true);
  lmd.setIntensity(2);
  
  for(int i=0; i<LEDMATRIX_WIDTH; i++){
     values[i] = 1;
  }
  
}

void loop() {

  Serial.println("HELLO WORLD");
  
  insertNewVal( random(100,999) );
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






