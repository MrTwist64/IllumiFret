#include <Adafruit_NeoPixel.h>
//#define NUM_LEDS 24
#define NUM_LEDS 138
#define DATA_PIN D0
#define BRIGHTNESS 30

Adafruit_NeoPixel pixels(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  pixels.clear();
}

void loop() {
  for(int i = 0; i < NUM_LEDS + 1; i++)
  {
    pixels.setPixelColor(i, pixels.Color(BRIGHTNESS, 0, 0));
  }
  pixels.show();

  // for(int i = 0; i < NUM_LEDS + 1; i++)
  // {
  //   pixels.setPixelColor(i, pixels.Color(BRIGHTNESS, 0, 0));
  //   pixels.show();
  //   pixels.clear();
  //   delay(50);
  // }
  
  // delay(250);

  // for(int i = 0; i < NUM_LEDS + 1; i++)
  // {
  //   pixels.setPixelColor(i, pixels.Color(0, BRIGHTNESS, 0));
  //   pixels.show();
  //   pixels.clear();
  //   delay(50);
  // }
  
  // delay(250);

  // for(int i = 0; i < NUM_LEDS + 1; i++)
  // {
  //   pixels.setPixelColor(i, pixels.Color(0, 0, BRIGHTNESS));
  //   pixels.show();
  //   pixels.clear();
  //   delay(50);
  // }

  // delay(250);
}