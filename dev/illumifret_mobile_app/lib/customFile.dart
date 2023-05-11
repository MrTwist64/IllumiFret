import 'package:flutter/material.dart';

import 'main.dart';

class Custom extends StatefulWidget {
  @override
  State<Custom> createState() => CustomState();
}

class CustomState extends State<Custom> {
  String fileName = "";

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        centerTitle: true,
        title: Row(
            mainAxisAlignment: MainAxisAlignment.center,
            mainAxisSize: MainAxisSize.min ,
            children: [Text("Custom File")]
        ),
      ),
      body: Container(
        margin: const EdgeInsets.all(10.0),
        child: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              const Text('File Name'),
              SizedBox(height: 10),
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 8, vertical: 16),
                child: TextFormField(
                  decoration: const InputDecoration(
                    border: OutlineInputBorder(),
                    labelText: 'Enter your file name'
                  ),
                  onChanged: (text) {
                    fileName = text;
                  },
                ),
              ),
              ElevatedButton(
                child: const Text('Play'),
                onPressed: () {
                  print("selected: ${fileName}");
                  blue.sendSong(fileName);
                },
              ),
            ],
          ),
        ),
      ),
    );
  }
}
