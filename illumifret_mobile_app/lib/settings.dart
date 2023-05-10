import 'package:flutter/material.dart';

import 'main.dart';

class Settings extends StatefulWidget {
  @override
  State<Settings> createState() => SettingsState();
}

class SettingsState extends State<Settings> {
  double sliderValue = settingMaxBrightness.toDouble();
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        centerTitle: true,
        title: Row(
            mainAxisAlignment: MainAxisAlignment.center,
            mainAxisSize: MainAxisSize.min ,
            children: [Text('Settings')]
        ),
      ),
      body: Container(
        margin: const EdgeInsets.all(10.0),
        child: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Divider(color: Colors.black),
              const Text(
                'Brightness',
              ),
              SizedBox(height: 10),
              Slider(
                value: sliderValue,
                max: 100,
                divisions: 10,
                label: sliderValue.round().toString(),
                onChanged: (double value) {
                  setState(() {
                    sliderValue = value;
                  });
                },
              ),
              ElevatedButton(
                child: const Text('Save'),
                onPressed: () {
                  settingMaxBrightness = sliderValue.round();
                  blue.sendBrightness(settingMaxBrightness);
                },
              ),
              Divider(color: Colors.black),
              ElevatedButton(
                child: const Text('Stop IllumiFret'),
                onPressed: () {
                  blue.stop();
                },
              ),
              // Divider(color: Colors.black),
              // ElevatedButton(
              //   child: const Text('Update Files'),
              //   onPressed: () {
              //     blue.updateFiles();
              //   },
              // ),
              // Divider(color: Colors.black),
              // ElevatedButton(
              //   child: const Text('Print fileListStr'),
              //   onPressed: () {
              //     print(fileListStr);
              //   },
              // ),
            ],
          ),
        ),
      ),
    );
  }
}
