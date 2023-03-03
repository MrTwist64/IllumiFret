#include <Adafruit_NeoPixel.h>
#define NUM_LEDS 24
#define DATA_PIN D0
#define BRIGHTNESS 24

Adafruit_NeoPixel pixels(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  pixels.clear();
}

//int redLEDs[][];

void loop() {
  for(int i = 0; i < NUM_LEDS + 1; i++)
  {
    for(int j = 0; j < i; j++)
      pixels.setPixelColor(j, pixels.Color(BRIGHTNESS-j, j, 0));
    pixels.show();
    delay(200);
  }
  //delay(100);
  
  /*
  pixels.setPixelColor(1, pixels.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));
  pixels.setPixelColor(2, pixels.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));
  pixels.setPixelColor(15, pixels.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));
  pixels.setPixelColor(17, pixels.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));
  pixels.setPixelColor(22, pixels.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));
  pixels.show();
  */
  
  pixels.clear();
}