import 'package:flutter/material.dart';

import 'main.dart';

class DisplayStrList extends StatefulWidget {
  final String barTitle = "";
  final List<List<String>> itemList = [[]];

  DisplayStrList({super.key});

  @override
  State<DisplayStrList> createState() => _DisplayStrListState();
}

class _DisplayStrListState extends State<DisplayStrList> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        centerTitle: true,
        title: Row(
          mainAxisAlignment: MainAxisAlignment.center,
          mainAxisSize: MainAxisSize.min ,
          children: [Text(widget.barTitle)]
        ),
      ),
      body: Container(
        margin: const EdgeInsets.all(10.0),
        child: ListView.separated(
          separatorBuilder: (BuildContext context, int index) {
            return SizedBox(height: 10);
          },
          itemCount: widget.itemList.length,
          itemBuilder: (BuildContext context, int index) {
            return Center(
              child: ElevatedButton(
                style: ElevatedButton.styleFrom(
                  minimumSize: Size.fromHeight(50.0),
                ),
                child: Text(widget.itemList[index][1]),
                onPressed: () {
                  print("selected: ${widget.itemList[index][0]}");
                  blue.sendSong(widget.itemList[index][0]);
                },
              ),
            );
          },
        ),
      ),
    );
  }
}