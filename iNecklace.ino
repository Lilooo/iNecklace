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
        $('p').on('swipe',function(){\
          $(this).toggleClass('on');\
          var domElement = $(this).get(0);\
          $( 'span:first' ).text( 'swipe on - ' + domElement.className + ' ' + domElement.id);\
          $.get( '/settings' , {id:domElement.id, state:domElement.className});\
          });\
      });\
      </script>\
    </head>\
        <span></span>\
        <p id='led1'>LED 1</p>\
        <p id='led2'>LED 2</p>\
        <p id='led3'>LED 3</p>\
        <p id='led4'>LED 4</p>\
        <p id='led5'>LED 5</p>\
        <p id='led6'>LED 6</p>\
        <p id='led7'>LED 7</p>\
  </html>");
}

/****Manage LEDs****/
void handleLEDs() {
  if (server.hasArg("id") && server.hasArg("state")) {
    Serial.println("id&state");
  }
  else {
    Serial.println("nothing");
  }
}

/****Setups****/
void setupSerial() {
  delay(1000);
  Serial.begin(115200);
}

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
  server.on("/settings", handleLEDs);
  server.begin();
  Serial.println("HTTP server started");
}

void setupPixels() {
  // This initializes the NeoPixel library.
  pixels.begin(); 
}

void setup() {
  setupSerial();
  setupWifi();
  setupServer();
  setupPixels();
}

/****Loop****/
void loop() {
  server.handleClient();
}
