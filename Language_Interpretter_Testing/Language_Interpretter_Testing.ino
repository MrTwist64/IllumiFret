#include "sdAccess.h"
#include "interpreter.h"
#include "ledBoard.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing port...");
  while(!Serial) { ; }; // Waits for the serial port to connect

  SDAccess sd;
  sd.init();
  sd.openDir("/");
  Interpreter inter;

  String input = sd.fileToString("TEST2.TXT");
  Serial.println(input);
  inter.setInput(input);
  inter.playInput();
}

void loop() {

}



//   String myFiles[30];
//   int myFilesLen = dirToArray(SD.open("/"), myFiles, 30);

//   Serial.println();
//   Serial.println("Print File Array:");
//   for(int i = 0; i < myFilesLen; i++) {
//     Serial.print(i);
//     Serial.print(": ");
//     Serial.println(myFiles[i]);
//   }

//   Serial.println();
//   Serial.println("Printing test.txt:");
//   printFile("test.txt");

//   //printDirectory(SD.open("/"), 0);