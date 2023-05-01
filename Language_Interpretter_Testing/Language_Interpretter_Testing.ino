#include <ArduinoBLE.h>

#include "sdAccess.h"
#include "interpreter.h"
#include "interpreter2.h"
#include "ledBoard.h"

BLEService ledService("cd8bcdb4-7b05-4f11-8495-bb6095b6f286");
BLEStringCharacteristic* stringChar = new BLEStringCharacteristic("cd8bcdb4-7b05-4f11-8495-bb6095b6f286", BLERead | BLEWrite, 100);
BLEIntCharacteristic* brightnessChar = new BLEIntCharacteristic("0bf58e4c-83dd-4b13-8640-b9fc4eb6d56b", BLERead);

Interpreter2* inter;
LEDBoard* board = new LEDBoard();

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
  BLE.setAdvertisedService(ledService);
  ledService.addCharacteristic(*stringChar);
  ledService.addCharacteristic(*brightnessChar);
  BLE.addService(ledService);
  //stringChar->writeValue("test");
  BLE.advertise();
}

void loop() {
  bool dataSent = false;
  BLEDevice central;

  while(!nameChosen) {
    central = BLE.central();
    digitalWrite(LED_BUILTIN, HIGH); // Indicates waiting for connection/data

    // If connected to device
    if (central) {
      // Loop while connected waiting for data
      while (central.connected()) {
        if (stringChar->written()) {
          Serial.println(stringChar->value());
          dataSent = true;
          digitalWrite(LED_BUILTIN, LOW); // Indicates data has been sent
          break;
        }
      }
    }
  }

  inter = new Interpreter2(stringChar);

  SDAccess sd;
  sd.init();
  sd.openDir("/");
  
  String input = sd.fileToString(stringChar->value()); // "newTest2.txt"
  inter->setInput(input);
  Serial.println(inter->getInput());
  inter->playInput(); // Plays animation, does NOT return
}