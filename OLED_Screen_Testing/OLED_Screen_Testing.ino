#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#define PIN_WIRE_SCL D5
#define PIN_WIRE_SDA D4

U8G2_SSD1306_128X64_NONAME_1_HW_I2C oled(
  U8G2_R2, // Rotation
  U8X8_PIN_NONE // Reset
);

#define HEIGHT 64
#define WIDTH 128

void setup(void) {
  oled.begin();
}
 
void loop(void) {
  oled.firstPage();
  do {
    // Writes stuff
    ///*
    int y = 7;
    oled.setFont(u8g2_font_squeezed_r7_tr);
    oled.setCursor(0,y);
    oled.print("We're no strangers to love.");
    y += 8;
    y += 5;
    oled.setCursor(0,y);
    oled.print("You know the rules, and so do I.");
    y += 8;
    y += 5;
    oled.setCursor(0,y);
    oled.print("A full commitment is what");
    y += 8;
    oled.setCursor(0,y);
    oled.print("I'm thinking of.");
    y += 8;
    y += 5;
    oled.setCursor(0,y);
    oled.print("You wouldn't get this");
    y += 8;
    oled.setCursor(0,y);
    oled.print("from any other guy.");
    //*/

    // Creates a 5x5 grid 
    /*
    for(int i = 0; i < WIDTH; i++) {
      for(int j = 0; j < HEIGHT; j++) {
        if(!(i%5) || !(j%5))
          oled.drawPixel(i, j);
      }
    }
    */

    // Draws boxes from screen bounderies to inside.
    /*
    int x = 0, y = 0, w = WIDTH, h = HEIGHT;
    while(w > 0 && h > 0) {
      oled.drawFrame(x, y, w, h);
      x += 3;
      y += 3;
      w -= 6;
      h -= 6;
    }
    */
  } while ( oled.nextPage() );
}