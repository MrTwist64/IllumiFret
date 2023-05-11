#include <ArduinoBLE.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#include "sdAccess.h"
#include "interpreter.h"
#include "ledBoard.h"

#define PIN_WIRE_SCL D5
#define PIN_WIRE_SDA D4
#define HEIGHT 64
#define WIDTH 128

U8G2_SSD1306_128X64_NONAME_1_HW_I2C oled(
  U8G2_R2, // Rotation
  U8X8_PIN_NONE // Reset
);

BLEService fileService("157450a3-e880-42e4-bdda-891b93d852dd");
BLEBoolCharacteristic* requestFilesChar = new BLEBoolCharacteristic("b1e3f114-045f-4c24-b094-c892eb4f3f65", BLERead | BLEWrite); // Used to request and end list of files
BLEStringCharacteristic* filesChar = new BLEStringCharacteristic("e61879ac-f7e1-49d6-bd41-4a1f83a0bab9", BLERead | BLENotify, 20); // List of file names on SD card

BLEService ledService("10903a9d-d7f6-4b24-a3ec-893dde451e07");
BLEStringCharacteristic* stringChar = new BLEStringCharacteristic("cd8bcdb4-7b05-4f11-8495-bb6095b6f286", BLEWrite, 50); // Filename to display on board
BLEIntCharacteristic* brightnessChar = new BLEIntCharacteristic("3606777e-7cdc-418c-ab1e-8be96e84ed6e", BLEWrite); // Brightness for board
BLEBoolCharacteristic* exitFileChar = new BLEBoolCharacteristic("1fee3d71-65b6-4a94-aff8-5bf0a84df477", BLERead | BLEWrite); // Used to request exiting a file to change a setting/file

BLEDevice central;
Interpreter* inter;
LEDBoard* board = new LEDBoard();
SDAccess sd;

void setup() {
  // Clear LEDs 
  LEDBoard* board = new LEDBoard();
  board->showFrame();

  // Connect via serial for debugging
  Serial.begin(9600);
  //while (!Serial);
  
  // Set up on-board LED
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

  // Initialize screen
  oled.begin();
  oled.setFont(u8g2_font_t0_11_mf);
  String toDisplay[6] = {"Waiting for", "connection..."};
  displayStringManual(toDisplay);

  while(true) {
    digitalWrite(LED_BUILTIN, LOW); // Indicates waiting for connection
    central = BLE.central();
    if (central.connected()) {
      digitalWrite(LED_BUILTIN, HIGH); // Indicates connection has been made
      String toDisplay[6] = {"Connected! Waiting", "for input..."};
      displayStringManual(toDisplay);
      break;
    }
  }

  inter = new Interpreter(&central, exitFileChar);
}

void loop() {
  if (central.connected()) {
    board->showFrame();
    if (exitFileChar->value()) {
      exitFileChar->writeValue(false);
      displayString("Waiting for input...");
    }

    if (stringChar->written()) {
      Serial.println(stringChar->value());
      playFile(stringChar->value());
    }

    if (brightnessChar->written()) {
      inter->setBrightness(brightnessChar->value());
      displayString("Brightness: " + String(brightnessChar->value()));
    }

    if (requestFilesChar->written() && requestFilesChar->value() == true) {
      sendFiles();
      delay(1000);
      requestFilesChar->writeValue(false);
    }
  }
}

void playFile(String name) {
  displayString("Loading " + name);
  Serial.println(sd.fileLongName(name));
  String input = sd.fileToString(name);
  inter->setInput(input);
  Serial.println(inter->getInput());
  displayString("Playing:            " + sd.fileLongName(name));
  inter->playInput();
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

int yLineStart[] = {8, 19, 30, 41, 52, 63};
int widthLimit = 20;

void displayString(String str) {
  oled.firstPage();
  do {
    int line = 0;
    for(int i = 0; i < str.length(); i += widthLimit) {
      oled.setCursor(0, yLineStart[line]);
      oled.print(str.substring(i, i + widthLimit));
      line++;
    }
  } while ( oled.nextPage() );
}

void displayStringManual(String str[6]) {
  oled.firstPage();
  do {
    for (int i = 0; i < 6; i++) {
      oled.setCursor(0, yLineStart[i]);
      oled.print(str[i]);
    }
  } while ( oled.nextPage() );
}