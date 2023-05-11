#include <ArduinoBLE.h>
#include <Seeed_Arduino_FreeRTOS.h>

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Bluetooth® Low Energy LED Service

// Bluetooth® Low Energy LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEStringCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite, 100);

const int ledPin = LED_BUILTIN; // pin to use for the LED

void setup() {
  Serial.begin(9600);
  // while (!Serial);

  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("AaronsTest");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characeristic:
  switchCharacteristic.setValue("OFF");

  // start advertising
  BLE.advertise();

  Serial.println("BLE LED Peripheral");

  // Create Thread
  xTaskCreate(ThreadB, "Task B", 256, NULL, tskIDLE_PRIORITY + 2, &Handle_bTask);
  
  // Start RTOS
  vTaskStartScheduler();
}

TaskHandle_t Handle_aTask;
TaskHandle_t Handle_bTask;

static void ThreadA(){
  Serial.println("Start of Thread A "); 
  while(1){
    digitalWrite(ledPin, HIGH); 
    delay(1000); 
    digitalWrite(ledPin, LOW); 
    delay(1000); 
  }
}

// digitalWrite(ledPin, LOW); // changed from HIGH to LOW   
// digitalWrite(ledPin, HIGH); // changed from LOW to HIGH 

static void ThreadB() {
  while(true) {
    // listen for Bluetooth® Low Energy peripherals to connect:
    BLEDevice central = BLE.central();

    // if a central is connected to peripheral:
    if (central) {
      Serial.print("Connected to central: ");
      // print the central's MAC address:
      Serial.println(central.address());

      // while the central is still connected to peripheral:
    while (central.connected()) {
      //Serial.println(myStr);
      if (switchCharacteristic.written()) {
        //Serial.println(switchCharacteristic.value());
        if (switchCharacteristic.value() == "ON") {
          Serial.println("Turning on Task A");
          xTaskCreate(ThreadA, "Task A", 256, NULL, tskIDLE_PRIORITY + 1, &Handle_aTask);    
        } 
        else if (switchCharacteristic.value() == "OFF") {     
          Serial.println("Turning off Task A");                         
          vTaskDelete(Handle_aTask);  
        }
      }
    }

    // when the central disconnects, print it out:
    Serial.print(("Disconnected from central: "));
    Serial.println(central.address());
    }
  }
}

void loop() {
  
}