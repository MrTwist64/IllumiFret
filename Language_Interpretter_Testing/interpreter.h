#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Arduino.h"
#include <string>
#include <ctype.h>
#include "ledBoard.h"

class Interpreter {
private:
  LEDBoard board;
  String input;
  char ch;
  int i;
  int red, green, blue;
  char string, fret;

  String _errorUnexpectedChar(char expected, char actual) {
    String ret = "Error! Expected '";
    ret += expected;
    ret += "', found '";
    ret += actual;
    return ret;
  }

  void _nextChar() {
    Serial.print("Consuming '");
    Serial.print(ch);
    Serial.print("', loading '");
    i++;
    ch = input[i];
    Serial.print(ch);
    Serial.println("'");
  }

  int _parseNumber() {
    String temp = "";
    while (isdigit(ch)) {
        temp += ch;
        _nextChar();
      }
    int num = temp.toInt();
    return num;
  }

  bool _ignoreFileName() {
    if (ch != '{') {
      Serial.println(_errorUnexpectedChar('{', ch));
      return false;
    }
    _nextChar();

    while (ch != '}')
      _nextChar();
    _nextChar();
    
    return true;
  }

  int _parseFrame() {
    board.newFrame();

    String temp;
    _nextChar(); // TEMP - SKIPS A BLANK CHAR THAT I SOMEHOW CANT GET RID OF BECAUSE OF NEW LINE

    int delayms = 0;
    if (ch == '#') {
      _nextChar();
      delayms = _parseNumber();
    }

    while(ch == '$') {
      _parseColor();

      if (ch != ':') {
        Serial.println(_errorUnexpectedChar(':', ch));
        return false;
      }
      _nextChar();

      while(ch != ':') {
        string = ch;
        _nextChar();
        fret = ch;
        _nextChar();
        board.setPixel(string, fret, red, blue, green);
      }
      _nextChar();
    }

    return delayms;
  }

  bool _parseColor() {
    if (ch != '$') {
      Serial.println(_errorUnexpectedChar('$', ch));
      return false;
    }
    _nextChar();

    red = _parseNumber();

    if (ch != ',') {
      Serial.println(_errorUnexpectedChar(',', ch));
      return false;
    }
    _nextChar();

    green = _parseNumber();

    if (ch != ',') {
      Serial.println(_errorUnexpectedChar(',', ch));
      return false;
    }
    _nextChar();

    blue = _parseNumber();
  }

public: 
  Interpreter() {

  }

  void setInput(String newInput) { this->input = newInput; }

  bool playInput() {
    do {
      i = 0;
      ch = input[i];

      if (!_ignoreFileName())
        return false;
      
      int i = 1;
      int delayms;
      while (ch != 'E')
      {
        delayms = _parseFrame();
        board.showFrame();
        delay(delayms);
      }
    } while (ch = 'R');
    
      
    Serial.println("End Of File Found");
  }

};

#endif // INTERPRETER_H