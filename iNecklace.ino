/****Includes****/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <Adafruit_NeoPixel.h>

/****Config****/
#define PIN   D2
const char *ssid = "River";

/*****Initialization*****/
ESP8266WebServer server(80);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

/*****WebPage*****/
void handleRoot() {
  server.send(200, "text/html", "\
  <html>\
    <head>\
      <title>Paulette' Necklace</title>\
      <link rel='stylesheet' href='http://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.css'>\
      <script src='http://code.jquery.com/jquery-1.11.3.min.js'></script>\
      <script src='http://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.js'></script>\
      <script type='text/javascript' charset='utf-8'>\
      $(document).ready(function(){\
        $('p').on('swipe',function(){$(this).toggleClass('on');});\
      });\
      </script>\
    </head>\
        <p class='led'>LED 1</p>\
        <p class='led'>LED 2</p>\
        <p class='led'>LED 3</p>\
        <p class='led'>LED 4</p>\
        <p class='led'>LED 5</p>\
        <p class='led'>LED 6</p>\
        <p class='led'>LED 7</p>\
  </html>");
}

/****Setups****/
void setupWifi() {
  //WiFiManager
  WiFiManager wifiManager;
  //reset saved settings -- Flush flash
  //wifiManager.resetSettings();
  //fetches ssid and pass from eeprom and tries to connect
  //if it does not connect it starts an access point with the specified name
  //and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect(ssid);
  Serial.println("local ip");
  Serial.println(WiFi.localIP());
}

void setupServer() {
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  
  setupWifi();
  setupServer();
  
  // This initializes the NeoPixel library.
  pixels.begin(); 
}

/****Loop****/
void loop() {
  server.handleClient();
  //rainbow(20);
}

/****Neopixels****/
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
