#include <SPI.h>
#include <SD.h>

#define CS D2 // Pin 2 is the chip select for the SD Card

File f;

void setup() {
  Serial.begin(9600);

  Serial.println("Initializing port...");

  // Waits for the serial port to connect
  while(!Serial) { ; }; 

  initializeSDCard();

  String myFiles[30];
  int myFilesLen = dirToArray(SD.open("/"), myFiles, 30);

  Serial.println();
  Serial.println("Print File Array:");
  for(int i = 0; i < myFilesLen; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(myFiles[i]);
  }

  Serial.println();
  Serial.println("Printing test.txt:");
  printFile("test.txt");

  //printDirectory(SD.open("/"), 0);

  /*
  
  */
}

void loop() 
{
  
}

void initializeSDCard() {
  Serial.print("Initializing SD card...");
  if (!SD.begin(CS)) {
    Serial.println("initialization failed!");
    while (1); // Loop infinitely
  }
  Serial.println("initialization done.");
}

int dirToArray(File dir, String* arr, int maxLen) {
  int i;
  
  for (i = 0; i < maxLen; i++) {
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

    arr[i] = entry.name();
    if (entry.isDirectory())
      arr[i] += "/";
    
    entry.close();
  }

  return i;
}

void printFile(String fileName) {
  File f = SD.open(fileName);

  if (f) 
  {
    while (f.available()) 
      Serial.write(f.read());
    f.close();
  } 
  else 
  {
    Serial.print("Error Opening ");
    Serial.println(fileName);
  }
}