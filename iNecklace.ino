#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <Adafruit_NeoPixel.h>

#define PIN   D2
const char *ssid = "River";

/*****Initialization*****/
ESP8266WebServer server(8080);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);


/* Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
  server.send(200, "text/html", "\
  <html>\
    <head>\
      <title>Collier de Paulette</title>\
      <script src='https://code.jquery.com/jquery-1.10.2.js'></script>\
      <script type='text/javascript' charset='utf-8'>\
        $('p').on('click',function(){$(this).hide();});\
      </script>\
    </head>\
      <h1>Paulette's Necklace</h1>\
        <p>Swipe Me !</p>\
  </html>");
}

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

void setup() {
  delay(1000);
  Serial.begin(115200);
  
  //WiFiManager
  WiFiManager wifiManager;
  //reset saved settings -- Flush flash
  //wifiManager.resetSettings();
  //fetches ssid and pass from eeprom and tries to connect
  //if it does not connect it starts an access point with the specified name
  //and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect(ssid);
    
  // This initializes the NeoPixel library.
  pixels.begin(); 
}

void loop() {
  server.handleClient();
  //rainbow(20);
}
