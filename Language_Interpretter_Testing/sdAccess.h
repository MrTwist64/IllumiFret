#ifndef SD_ACCESS_H
#define SD_ACCESS_H

#include "Arduino.h"
#include <SPI.h>
#include <SD.h>

#define CS D2 // Pin 2 is the chip select for the SD Card
#define MAX_FILES 50

File f;

class SDAccess {
private: 
  String fileArray[MAX_FILES];
  int fileArrayLen = 0;
  String currDir = "";

public:
  // Getters
  String getFileName(int i) { return fileArray[i]; };
  int getFileArrayLen() { return fileArrayLen; };
  String getCurrDir() { return currDir; };
  
  // Initializes SD card and returns a boolean for success/failure.
  bool init() {
    Serial.print("Initializing SD card...");
    if (!SD.begin(CS)) {
      Serial.println("initialization failed!");
      return false;
    }
    Serial.println("initialization done.");
    return true;
  }

  // Same as init(), but without print statements.
  bool initQuiet() {
    if (!SD.begin(CS))
      return false;
    return true;
  }

  // Reads the files out of a given directory and puts their names into the given array.
  // This function ignores the "SYSTEM~1" directory, which is a hidden directory.
  void openDir(String dirName) {
    File dir = SD.open(dirName);

    int i;
    for (i = 0; i < MAX_FILES; i++) {
      File entry = dir.openNextFile();
      
      // Ends if no more files are found
      if (!entry)
        break; // no more files

      // Ignores a hidden directory that we don't need/want to display
      String ignoreDir = "SYSTEM~1";
      if(ignoreDir.compareTo(entry.name()) == 0)
      {
        i--;
        continue;
      }

      fileArray[i] = entry.name();
      if (entry.isDirectory())
        fileArray[i] += "/";
      
      entry.close();
    }

    currDir = dirName;
    fileArrayLen = i;
  }

  // Returns the array location of the file in the array.
  // If file is not found, returns -1.
  int findFile(String fileName) {
    for(int i = 0; i < MAX_FILES; i++)
      if (fileArray[i] == fileName)
        return i;
    return -1;
  }

  // Reads a file and returns its contents as a string.
  String fileToString(String fileName) {
    File f = SD.open(fileName);

    if (!f)
    {
      Serial.print("Error opening ");
      Serial.println(fileName);
      return "";
    }

    String contents = "";
    while (f.available())
      contents += f.readStringUntil('\n');
    f.close();
    return contents;
  }

  // Reads a file and returns the first line as a string.
  String fileFirstLine(String fileName) {
    File f = SD.open(fileName);

    if (!f)
    {
      Serial.print("Error opening ");
      Serial.println(fileName);
      return "";
    }

    if (!f.available())
    {
      Serial.print("Error empty file ");
      Serial.println(fileName);
      return "";
    }

    String contents = f.readStringUntil('\n');
    f.close();
    return contents;
  }
};

#endif // SD_ACCESS_H