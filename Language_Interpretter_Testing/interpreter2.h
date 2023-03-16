#ifndef INTERPRETER2_H
#define INTERPRETER2_H

#include "Arduino.h"
#include <string>
#include <ctype.h>
#include "ledBoard.h"

class Interpreter2 
{
private:
  LEDBoard board;
  String input;
  int i;
  char ch;
  int red, green, blue;
  char string, fret;

  // Advances to the next character in the input.
  void _nextChar() 
  {
    Serial.print("Consuming '");
    Serial.print(ch);
    i++;
    ch = input[i];
    Serial.print("', loading '");
    Serial.print(ch);
    Serial.println("'");
  }

  // 
  int _readNumber()
  {
    String temp = "";
    while(isdigit(ch))
    {
      temp += ch;
      _nextChar();
    }
    return temp.toInt();
  }

  void _error(String expected, char found)
  {
    Serial.println("Error! Expected '" + String(expected) + "', not '" + String(found) + "'.");
  }

  // Cleans up the input before interpreting.
  void _cleanInput() 
  {
    _removeName();
    _removeWhitespace();
  }

  // Removes the name information from the input.
  void _removeName()
  {
    i = 0;
    ch = input[i];

    // Check if name command exists, return if not.
    if (ch != 'N')
      return;
    _skipPastSemicolon();

    input.remove(0, i);
  }

  // Removes whitespace from the input
  void _removeWhitespace()
  {
    input.replace(" ", ""); // Spaces
    input.replace("\t", ""); // Tabs
    input.replace("\n", ""); // New lines
    input.replace("\r", ""); // Returns
  }

  // Skips the current command and goes to the next line after a semicolon.
  void _skipPastSemicolon()
  {
    while (ch != ';')
      _nextChar();
    _nextChar();
  }

  // Skips the current string until after the next semicolon.
  void _skipPastColon()
  {
    while (ch != ':')
      _nextChar();
    _nextChar();
  }

  // Reads a new frame and displays it on the board.
  // Returns whether the frame was read successfully.
  bool _newFrame()
  {
    int delay, red, green, blue;

    if (!_lineStartFrame(&delay))
      return false;
    
    while (true)
    {
      // Checks for "EndFrame" command
      if(ch == 'E')
        break;

      if(!_lineColor(&red, &green, &blue))
        return false;
      
      if(!_lineLEDS(red, green, blue))
        return false;
    }

    _lineEndFrame(delay);
    return true;
  }

  // Reads in a "StartFrame" line.
  // The time length of the frame is specified after a colon.
  // Returns whether the line was read successfully.
  bool _lineStartFrame(int* delay)
  {
    Serial.println("_lineStartFrame()");
    // Makes current frame empty
    board.newFrame();

    // Checks for "StartFrame".
    // If found, skip past it.
    if (ch != 'S') {_error("S", ch); return false;}
    _skipPastColon();

    // Checks for delay amount
    // If no delay specified, -1 = infinite delay
    if (isdigit(ch))
      *delay = _readNumber();
    else
      *delay = -1;
    _skipPastSemicolon();

    return true;
  }

  // Reads a "Color" line.
  // A color is specified after the colon in 3 values (RGB) between 0 and 100.
  // Returns whether the line was read successfully.
  bool _lineColor(int* red, int* green, int* blue)
  {
    Serial.println("_lineColor()");
    // Checks for "Color".
    // If found, skip past it.
    if (ch != 'C') {_error("C", ch); return false;}
    _skipPastColon();

    // Reads in the red value
    if (isdigit(ch))
      *red = _readNumber();
    else
      return false;
    
    // Skips comma
    if (ch != ',') {_error(",", ch); return false;}
    _nextChar();

    // Reads in the green value
    if (isdigit(ch))
      *green = _readNumber();
    else
      return false;
    
    // Skips comma
    if (ch != ',') {_error(",", ch); return false;}
    _nextChar();

    // Reads in the blue value
    if (isdigit(ch))
      *blue = _readNumber();
    else
      return false;
    
    // Finish line
    _skipPastSemicolon();
    return true;
  }

  // Reads a "LEDS" line.
  // Sets the specified LEDS to the given RGB values.
  // Returns whether the line was read successfully.
  bool _lineLEDS(int red, int green, int blue)
  {
    Serial.println("_lineLEDS()");
    char string, fret;

    // Checks for "Color".
    // If found, skip past it.
    if (ch != 'L') {_error("L", ch); return false;}
    _skipPastColon();

    while(ch != ';')
    {
      // Reads in next two characters as string and fret.
      string = ch;
      _nextChar();
      fret = ch;
      _nextChar();

      // Sets pixel of given string/fret to RGB.
      board.setPixel(string, fret, red, green, blue);
      
      if (ch == ',')
      {
        _nextChar();
        continue;
      }
      if (ch == ';')
        break;
      
      _error(",' or ';", ch); 
      return false;
    }

    _skipPastSemicolon();
    return true;
  }

  // Reads in a "EndFrame" line.
  // Shows the current frame and waits for the given delay in milliseconds.
  // Returns whether the line was read succesfully.
  bool _lineEndFrame(int delayms)
  {
    Serial.println("_lineEndFrame()");
    // Checks for "EndFrame".
    // If found, skip past it.
    if (ch != 'E') {_error("E", ch); return false;}
    _skipPastSemicolon();

    board.showFrame();
    if (delayms == -1)
      while(true) {}
    delay(delayms);
    return true;
  }

public: 

  // Sets and cleans the input.
  void setInput(String newInput) 
  {
    this->input = newInput;
    _cleanInput();
  }
  
  void playInput()
  {
    i = 0;
    ch = input[i];

    while (true)
    {
      // Test for "StartFrame".
      if (ch == 'S')
      {
        _newFrame();
        continue;
      }
      
      // Test for "Repeat"
      if (ch == 'R')
      {
        i = 0;
        ch = input[0];
        continue;
      }

      // Test for "FileEnd"
      if (ch == 'F')
        break;      
    }
  }

};

#endif // INTERPRETER2_H