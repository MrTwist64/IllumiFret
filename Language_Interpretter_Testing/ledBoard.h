#ifndef LED_BOARD_H
#define LED_BOARD_H

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include <map>
#include <string>

using namespace std;

#define NUM_LEDS 24
#define DATA_PIN D0
#define MAX_BRIGHTNESS 30

class LEDBoard {
private:
  Adafruit_NeoPixel out = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);
  std::map<char,int> fretValuesMap;

  int _charsToInt(char string, char fret) {
    Serial.print("String: ");
    Serial.print(string);
    Serial.print(" Fret: ");
    Serial.print(fret);
    int stringValue = (string - '0' - 1);
    int fretValue = fretValuesMap[fret];
    Serial.print(" StringVal: ");
    Serial.print(stringValue);
    Serial.print(" FretVal: ");
    Serial.print(fretValue);
    int ledValue = (fretValue * 6) + stringValue;
    Serial.print(" LED: ");
    Serial.println(ledValue);
    return ledValue;
  }

  void _initFretValuesMap() {
    fretValuesMap['0'] = 0;
    fretValuesMap['1'] = 1;
    fretValuesMap['2'] = 2;
    fretValuesMap['3'] = 3;
    fretValuesMap['4'] = 4;
    fretValuesMap['5'] = 5;
    fretValuesMap['6'] = 6;
    fretValuesMap['7'] = 7;
    fretValuesMap['8'] = 8;
    fretValuesMap['9'] = 9;
    fretValuesMap['A'] = 10;
    fretValuesMap['B'] = 11;
    fretValuesMap['C'] = 12;
    fretValuesMap['D'] = 13;
    fretValuesMap['E'] = 14;
    fretValuesMap['F'] = 15;
    fretValuesMap['G'] = 16;
    fretValuesMap['H'] = 17;
    fretValuesMap['I'] = 18;
    fretValuesMap['J'] = 19;
    fretValuesMap['K'] = 20;
    fretValuesMap['L'] = 21;
    fretValuesMap['M'] = 22;
    fretValuesMap['N'] = 23;
  }

  int _percentColorToActualColor(int percentColor) {
    int actualColor = ((double)percentColor / 100) * MAX_BRIGHTNESS;
    return actualColor;
  }

  // Sets the LED to the RGB value given for the next frame.
  // Color values should be the direct values for the LEDs.
  // Functions that call programPixel() should change percentage color 
  // values to actual values before calling this function.
  void _setPixel(int pixelNum, int red, int green, int blue) {
    out.setPixelColor(pixelNum, out.Color(red, green, blue));
    Serial.print(pixelNum);
    Serial.print("(");
    Serial.print(red);
    Serial.print(", ");
    Serial.print(green);
    Serial.print(", ");
    Serial.print(blue);
    Serial.println(")");
  }

public:
  LEDBoard() {
    _initFretValuesMap();
    out.begin();
    out.clear();
  }

  // Displays the currently set frame onto the LED board.
  void showFrame() {
    out.show();
    Serial.println("Show Frame");
  }

  // Clears all pixel values for an empty frame.
  void newFrame() {
    out.clear();
    Serial.println("Clear Frame");
  }

  // Sets the LED to the RGB value given for the next frame.
  // LED number must be decoded based on string and fret chars.
  // Colors should be sent as an int between 0 and 100 to represent 
  // percentage brightness of color. Percents are converted to actual values.
  // Correct values are then passed along to the _setPixel() function.
  void setPixel(char string, char fret, int red, int green, int blue) {
    int pixelNum = _charsToInt(string, fret);
    int redValue = _percentColorToActualColor(red);
    int greenValue = _percentColorToActualColor(green);
    int blueValue = _percentColorToActualColor(blue);
    this->_setPixel(pixelNum, redValue, greenValue, blueValue);
  }

  // Sets the LED to the RGB value given for the next frame.
  // Colors should be sent as an int between 0 and 100 to represent 
  // percentage brightness of color. Percents are converted to actual values.
  // Correct values are then passed along to the _setPixel() function.
  void setPixel(int pixelNum, int red, int green, int blue) {
    int redValue = _percentColorToActualColor(red);
    int greenValue = _percentColorToActualColor(green);
    int blueValue = _percentColorToActualColor(blue);
    this->_setPixel(pixelNum, redValue, greenValue, blueValue);
  }

};

#endif // LED_BOARD_H