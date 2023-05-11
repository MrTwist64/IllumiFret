import 'dart:convert' show utf8;
import 'dart:async';

import 'package:flutter_reactive_ble/flutter_reactive_ble.dart';

import 'main.dart';

class Blue {
  final flutterReactiveBle = FlutterReactiveBle();

  final deviceName = "Illumifret";
  final Uuid fileServUuid = Uuid.parse("157450a3-e880-42e4-bdda-891b93d852dd");
  final Uuid requestFilesCharUuid = Uuid.parse("b1e3f114-045f-4c24-b094-c892eb4f3f65");
  final Uuid filesCharUuid = Uuid.parse("e61879ac-f7e1-49d6-bd41-4a1f83a0bab9");
  final Uuid ledServUuid = Uuid.parse("10903a9d-d7f6-4b24-a3ec-893dde451e07");
  final Uuid fileNameCharUuid = Uuid.parse("cd8bcdb4-7b05-4f11-8495-bb6095b6f286");
  final Uuid brightnessCharUuid = Uuid.parse("3606777e-7cdc-418c-ab1e-8be96e84ed6e");
  final Uuid exitFileCharUuid = Uuid.parse("1fee3d71-65b6-4a94-aff8-5bf0a84df477");

  bool connected = false;
  bool filesCharSubscribed = false;
  bool requestFilesCharSubscribed = false;
  late StreamSubscription<DiscoveredDevice> scanStream;
  late DiscoveredDevice device;

  void connect() async {
    _scan(deviceName);
    await Future.delayed(const Duration(seconds: 1));
    _connect();
  }

  Future<void> sendSong(String fileName) async {
    _sendExitFile();
    _sendStringData(fileName);
  }

  Future<void> sendBrightness(int brightness) async {
    _sendExitFile();
    _sendBrightnessData(brightness);
  }

  Future<void> stop() async {
    _sendExitFile();
  }

  // Future<void> updateFiles() async {
  //   fileListStr = "";
  //   await _subscribeFileChar();
  //   _sendExitFile();
  //   _sendFileRequest();
  //   await _readFiles();
  //   print("Data: ${fileListStr}");
  //   _parseFileListStr();
  // }

  Future _scan(String name) async {
    scanStream = flutterReactiveBle.scanForDevices(
      withServices: [fileServUuid, ledServUuid],
      scanMode: ScanMode.lowLatency,
    ).listen(
      (device) {
        if (device.name == name || device.name == "Arduino") {
          this.device = device;
          scanStream.cancel();
          return;
        }
      }
    );
    return;
  }

  Future<void> _connect() async {
    flutterReactiveBle.connectToDevice(
      id: device.id,
      servicesWithCharacteristicsToDiscover: {ledServUuid: [fileNameCharUuid]},
      connectionTimeout: const Duration(seconds: 2),
    ).listen((connectionState) {
      if (connectionState.connectionState == DeviceConnectionState.connected) {
        connected = true;
        return;
      }
    });
  }

  // Future<void> _subscribeFileChar() async {
  //   final filesChar = QualifiedCharacteristic(serviceId: fileServUuid, characteristicId: filesCharUuid, deviceId: device.id);
  //   final fileRequestChar = QualifiedCharacteristic(serviceId: fileServUuid, characteristicId: requestFilesCharUuid, deviceId: device.id);
  //
  //   int i = 0;
  //   String newData = "";
  //   String prevData = "";
  //
  //   if (!filesCharSubscribed) {
  //     print("Subscribing to file char");
  //     await flutterReactiveBle.subscribeToCharacteristic(filesChar).listen((data) {
  //       newData = utf8.decode(data);
  //       if (prevData != newData) {
  //         fileListStr += newData;
  //         print("(${i})Read \"${newData}\"");
  //         prevData = newData;
  //         i++;
  //       }
  //     });
  //     filesCharSubscribed = true;
  //   }
  // }

  // Future<void> _subscribeRequestFiles() async {
  //   final fileRequestChar = QualifiedCharacteristic(serviceId: fileServUuid, characteristicId: requestFilesCharUuid, deviceId: device.id);
  //
  //   if (!requestFilesCharSubscribed) {
  //     print("Subscribing to file char");
  //     await flutterReactiveBle.subscribeToCharacteristic(fileRequestChar).listen((data) {
  //
  //     });
  //     requestFilesCharSubscribed = true;
  //   }
  // }

  void _sendStringData(String fileName) async {
    final characteristic = QualifiedCharacteristic(serviceId: ledServUuid, characteristicId: fileNameCharUuid, deviceId: device.id);
    await flutterReactiveBle.writeCharacteristicWithResponse(characteristic, value: utf8.encode(fileName));
    print("\"${fileName}\" sent to device");
  }

  Future<void> _sendBrightnessData(int brightness) async {
    final characteristic = QualifiedCharacteristic(serviceId: ledServUuid, characteristicId: brightnessCharUuid, deviceId: device.id);
    await flutterReactiveBle.writeCharacteristicWithResponse(characteristic, value: [brightness]);
    print("\"${brightness}\" sent to device");
  }

  Future<void> _sendExitFile() async {
    final characteristic = QualifiedCharacteristic(serviceId: ledServUuid, characteristicId: exitFileCharUuid, deviceId: device.id);
    await flutterReactiveBle.writeCharacteristicWithResponse(characteristic, value: [1]);
    print("Exit file request sent to device");
  }

  // Future<void> _sendFileRequest() async {
  //   final characteristic = QualifiedCharacteristic(serviceId: fileServUuid, characteristicId: requestFilesCharUuid, deviceId: device.id);
  //   await flutterReactiveBle.writeCharacteristicWithResponse(characteristic, value: [1]);
  //   final response = await flutterReactiveBle.readCharacteristic(characteristic);
  //   print("Response: ${response.first}");
  //   print("File list request sent to device");
  // }
  //
  // // Pauses until requestBool is turned off, meaning the subscribed char above read all files
  // Future<void> _readFiles() async {
  //   final fileRequestChar = QualifiedCharacteristic(serviceId: fileServUuid, characteristicId: requestFilesCharUuid, deviceId: device.id);
  //
  //   var response = await flutterReactiveBle.readCharacteristic(fileRequestChar);
  //   while(response.first == 1) {
  //     response = await flutterReactiveBle.readCharacteristic(fileRequestChar);
  //   }
  // }
  //
  // void _parseFileListStr () {
  //   String temp;
  //   var split1 = fileListStr.split(";");
  //   var split2;
  //   var fileList = [];
  //   for(int i = 0; i < split1.length - 1; i++) {
  //     split2 = split1[i].split(":");
  //     fileList.add([split2[0], split2[1]]);
  //   }
  //   print(fileList);
  //
  // }
}

