# Illumifret


## App
- After installing app, you must enable location permissions manually
- Uses Flutter Reactive BLE 5.0.3
- main.dart is the main file where the program is built and contains all of the widgets which create the menus within the application
  - If using Android Studio, once the flutter SDK has been established in the project the program can be built by making a Run/Debug configuration that uses main.dart as the Dart entrypoint
- dispalyStrList.dart gives a widget that can display a list of a list of strings. This data structure stores a list of pairs of strings, such as the Chord title and its corresponding file in the SD card
- ble.dart contains the functions necessary for communication with the microcontroller via bluetooth

## MicroController Program
- Relies on three libraries in Arduino IDE
  - ArduinoBLE
  - u8g2
  - Adafruit_Neopixel
- IllumiFret.ino acts as the main program and establishes the Bluetooth connection as well as initialization of program
  - Once the three libraries above have been installed, simply compile this and program the board to build the program
- sdAcces.h provides the functions needed for accessing files on the SD card
- ledBoard.h serves as the interface to Adafruit's library and provides the function required for creating frames and pushing them to the board
- interpreter.h takes the files on the SD card written in our language and breaks them down into the functions that utilize Adafruit's library
