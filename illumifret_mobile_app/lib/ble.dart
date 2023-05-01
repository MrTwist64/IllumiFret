import 'dart:convert' show utf8;
import 'dart:async';

import 'package:flutter_reactive_ble/flutter_reactive_ble.dart';

class Blue {
  final flutterReactiveBle = FlutterReactiveBle();

  final deviceName = "Illumifret";
  final Uuid serviceUuid = Uuid.parse("cd8bcdb4-7b05-4f11-8495-bb6095b6f286");
  final Uuid characteristicUuid = Uuid.parse("cd8bcdb4-7b05-4f11-8495-bb6095b6f286");

  late StreamSubscription<DiscoveredDevice> scanStream;
  late DiscoveredDevice device;

  void sendSong(String fileName) {
    while(_scan(deviceName)){}
    _connect();
    _sendStringData(fileName);
  }

  bool _scan(String name) {
    bool returnVar = false;
    scanStream = flutterReactiveBle.scanForDevices(
      withServices: [serviceUuid],
      scanMode: ScanMode.lowLatency,
    ).listen(
      (device) {
        if (device.name == name) {
          this.device = device;
          returnVar = true;
          scanStream.cancel();
        }
      }
    );
    return returnVar;
  }

  void _connect() {
    flutterReactiveBle.connectToDevice(
      id: device.id,
      servicesWithCharacteristicsToDiscover: {serviceUuid: [characteristicUuid]},
      connectionTimeout: const Duration(seconds: 2),
    ).listen((connectionState) {});
  }

  Future<void> _sendStringData(String fileName) async {
    final characteristic = QualifiedCharacteristic(serviceId: serviceUuid, characteristicId: characteristicUuid, deviceId: device.id);
    await flutterReactiveBle.writeCharacteristicWithResponse(characteristic, value: utf8.encode(fileName));
  }
}

