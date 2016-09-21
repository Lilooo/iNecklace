# iNecklace

## Dependencies

ESP8266 Arduino:

    https://github.com/esp8266/Arduino

WiFiManager - WiFi Configuration Magic:

    https://github.com/tzapu/WiFiManager

Adafruit NeoPixel:

    https://github.com/adafruit/Adafruit_NeoPixel

Elapsed milliseconds:

    https://github.com/pfeerick/elapsedMillis


## Usage

1st time:
  * program the ESP
  * open the monitor (115220 bauds) and find printed "AP IP address"
  * connect your phone/computer to your ESP (SSID = 'River')
  * put the IP in your browser and set the ESP to connect to your favorite network

The monitor should display:

    "WM: Using last saved values, should be faster..."
    "WM: IP Address:..."

Then:
  * connect your phone/computer back to your favorite network
  * put the IP in your browser
  * in the interface, swipe LEDs to control them

