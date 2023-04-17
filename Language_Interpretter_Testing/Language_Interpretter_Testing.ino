#include "sdAccess.h"
#include "interpreter.h"
#include "interpreter2.h"
#include "ledBoard.h"

void setup() {
  Serial.begin(9600);
  //Serial.println("Initializing port...");
  //while(!Serial) { ; }; // Waits for the serial port to connect

  SDAccess sd;
  sd.init();
  sd.openDir("/");
  
  Interpreter inter;
  String input = sd.fileToString("TEST2.TXT");
  //String input = "{Test Program for Prototype}#1000$50,0,0:102030405060:$0,50,0:113151:#1000$50,0,0:122232425262:$0,50,0:214161:ER";
  Serial.println(input);
  inter.setInput(input);
  inter.playInput();

  
  Interpreter2 inter;
  //String input = sd.fileToString("TEST2.TXT");
  //String input = "Name:Test Program for Prototype;StartFrame:1000;Color:50,0,0;LEDS:10,20,30,40,50,60;Color:0,50,0;LEDS:11,31,51;EndFrame;StartFrame:1000;Color:50,0,0;LEDS:12,22,32,42,52,62;Color:0,50,0;LEDS:21,41,61;EndFrame;Repeat;";
  String input = "Name:Test Program for Prototype;StartFrame:50;Color:100,0,0;LEDS:10;EndFrame;StartFrame:50;Color:50,50,0;LEDS:10;Color:100,0,0;LEDS:11,20;EndFrame;StartFrame:50;Color:0,100,0;LEDS:10;Color:50,50,0;LEDS:11,20;Color:100,0,0;LEDS:12,21,30;EndFrame;StartFrame:50;Color:0,50,50;LEDS:10;Color:0,100,0;LEDS:11,20;Color:50,50,0;LEDS:12,21,30;Color:100,0,0;LEDS:13,22,31,40;EndFrame;StartFrame:50;Color:50,0,50;LEDS:10;Color:0,50,50;LEDS:11,20;Color:0,100,0;LEDS:12,21,30;Color:50,50,0;LEDS:13,22,31,40;Color:100,0,0;LEDS:23,32,41,50;EndFrame;StartFrame:50;Color:50,0,50;LEDS:11,20;Color:0,50,50;LEDS:12,21,30;Color:0,100,0;LEDS:13,22,31,40;Color:50,50,0;LEDS:23,32,41,50;Color:100,0,0;LEDS:33,42,51,60;EndFrame;StartFrame:50;Color:50,0,50;LEDS:12,21,30;Color:0,50,50;LEDS:13,22,31,40;Color:0,100,0;LEDS:23,32,41,50;Color:50,50,0;LEDS:33,42,51,60;Color:100,0,0;LEDS:43,52,61;EndFrame;StartFrame:50;Color:50,0,50;LEDS:13,22,31,40;Color:0,50,50;LEDS:23,32,41,50;Color:0,100,0;LEDS:33,42,51,60;Color:50,50,0;LEDS:43,52,61;Color:100,0,0;LEDS:53,62;EndFrame;StartFrame:50;Color:50,0,50;LEDS:23,32,41,50;Color:0,50,50;LEDS:33,42,51,60;Color:0,100,0;LEDS:43,52,61;Color:50,50,0;LEDS:53,62;Color:100,0,0;LEDS:63;EndFrame;StartFrame:50;Color:50,0,50;LEDS:33,42,51,60;Color:0,50,50;LEDS:43,52,61;Color:0,100,0;LEDS:53,62;Color:50,50,0;LEDS:63;EndFrame;StartFrame:50;Color:50,0,50;LEDS:43,52,61;Color:0,50,50;LEDS:53,62;Color:0,100,0;LEDS:63;EndFrame;StartFrame:50;Color:50,0,50;LEDS:53,62;Color:0,50,50;LEDS:63;EndFrame;StartFrame:50;Color:50,0,50;LEDS:63;EndFrame;Repeat;";
  //Serial.println(input);
  inter.setInput(input);
  inter.playInput();
}

void loop() {

}