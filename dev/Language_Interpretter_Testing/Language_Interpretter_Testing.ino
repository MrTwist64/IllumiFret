#include <ArduinoBLE.h>

#include "sdAccess.h"
#include "interpreter.h"
#include "interpreter2.h"
#include "ledBoard.h"

BLEService fileService("157450a3-e880-42e4-bdda-891b93d852dd");
BLEBoolCharacteristic* requestFilesChar = new BLEBoolCharacteristic("b1e3f114-045f-4c24-b094-c892eb4f3f65", BLERead | BLEWrite); // Used to request and end list of files
BLEStringCharacteristic* filesChar = new BLEStringCharacteristic("e61879ac-f7e1-49d6-bd41-4a1f83a0bab9", BLERead | BLENotify, 20); // List of file names on SD card

BLEService ledService("10903a9d-d7f6-4b24-a3ec-893dde451e07");
BLEStringCharacteristic* stringChar = new BLEStringCharacteristic("cd8bcdb4-7b05-4f11-8495-bb6095b6f286", BLEWrite, 50); // Filename to display on board
BLEIntCharacteristic* brightnessChar = new BLEIntCharacteristic("3606777e-7cdc-418c-ab1e-8be96e84ed6e", BLEWrite); // Brightness for board
BLEBoolCharacteristic* exitFileChar = new BLEBoolCharacteristic("1fee3d71-65b6-4a94-aff8-5bf0a84df477", BLERead | BLEWrite); // Used to request exiting a file to change a setting/file

BLEDevice central;
Interpreter2* inter;
LEDBoard* board = new LEDBoard();
SDAccess sd;

void setup() {
  // Clear LEDs 
  LEDBoard* board = new LEDBoard();
  board->showFrame();

  // Connect via serial for debugging
  Serial.begin(9600);
  //while (!Serial);
  
  pinMode(LED_BUILTIN, OUTPUT);

  // Set up BLE
  if (!BLE.begin()) {while (1);}
  BLE.setLocalName("Illumifret");

  BLE.setAdvertisedService(fileService);
  ledService.addCharacteristic(*requestFilesChar);
  ledService.addCharacteristic(*filesChar);
  BLE.addService(fileService);

  BLE.setAdvertisedService(ledService);
  ledService.addCharacteristic(*stringChar);
  ledService.addCharacteristic(*brightnessChar);
  ledService.addCharacteristic(*exitFileChar);
  BLE.addService(ledService);

  BLE.advertise();

  // Initialize sd card
  sd.init();

  while(true) {
    digitalWrite(LED_BUILTIN, LOW); // Indicates waiting for connection
    central = BLE.central();
    if (central.connected()) {
      digitalWrite(LED_BUILTIN, HIGH); // Indicates connection has been made
      break;
    }
  }

  inter = new Interpreter2(&central, exitFileChar);
  //inter->setBrightness(10);
}

void loop() {
  if (central.connected()) {
    board->showFrame();
    exitFileChar->writeValue(false);

    if (stringChar->written()) {
      Serial.println(stringChar->value());
      playFile(stringChar->value());
    }

    if (brightnessChar->written()) {
      inter->setBrightness(brightnessChar->value());
    }

    if (requestFilesChar->written() && requestFilesChar->value() == true) {
      sendFiles();
      delay(1000);
      requestFilesChar->writeValue(false);
    }
  }
}

void playFile(String name) {
  Serial.println(sd.fileLongName(name));
  String input = sd.fileToString(name); // "newTest2.txt"
  // String input = sd.fileToString("cPenta.txt");
  inter->setInput(input);
  Serial.println(inter->getInput());
  inter->playInput(); // Plays animation, does NOT return
}

void sendFiles() {
  String files = "";
  String f;
  sd.openDir("/");
  for(int i = 0; i < sd.getFileArrayLen(); i++) {
    f = sd.getFileName(i);
    files += f;
    files += ":";
    files += sd.fileLongName(f);
    files += ";";
  }
  
  for(int i = 0; i < files.length(); i += 20) {
    filesChar->writeValue(files.substring(i, i + 20));
    Serial.print("Sent: ");
    Serial.println(files.substring(i, i + 20));
  }
    
  Serial.println(files);
}