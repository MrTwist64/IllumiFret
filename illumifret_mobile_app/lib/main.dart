import 'package:flutter/material.dart';
import 'displayStrList.dart';
import 'ble.dart';
import 'bleTest.dart';

Blue blue = Blue();

void main() {
  runApp(MaterialApp(
    title: 'Illumifret App',
    theme: ThemeData(
      colorSchemeSeed: Colors.pink,
      elevatedButtonTheme: ElevatedButtonThemeData(
        style: ElevatedButton.styleFrom(
          backgroundColor: Colors.pink[100],
          foregroundColor: Colors.black,
          textStyle: TextStyle(
            fontWeight: FontWeight.bold,
            fontSize: 20.0,
          ),
        ),
      ),
    ),
    home: const MainMenu(),
  ));
}

class MainMenu extends StatelessWidget {
  const MainMenu({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Center(child: Text('Illumifret')),
      ),
      body: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              SizedBox(
                height: 150,
                width: 150,
                child: ElevatedButton(
                  child: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: const [
                      Icon(
                        Icons.music_note_rounded,
                        size: 70,
                      ),
                      SizedBox(
                        height: 15,
                      ),
                      Text("Chords"),
                    ],
                  ),
                  onPressed: () {
                    Navigator.push(context,
                        MaterialPageRoute(builder: (context) => ChordList()));
                  },
                ),
              ),
              const SizedBox(
                width: 15,
              ),
              SizedBox(
                height: 150,
                width: 150,
                child: ElevatedButton(
                  child: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: const [
                      Icon(
                        Icons.stacked_line_chart_rounded,
                        size: 70,
                      ),
                      SizedBox(
                        height: 15,
                      ),
                      Text("Scales"),
                    ],
                  ),
                  onPressed: () {
                    Navigator.push(context,
                        MaterialPageRoute(builder: (context) => ScaleList()));
                  },
                ),
              ),
            ],
          ),
          const SizedBox(
            height: 15,
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              SizedBox(
                height: 150,
                width: 150,
                child: ElevatedButton(
                  child: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: const [
                      Icon(
                        Icons.play_arrow_rounded,
                        size: 70,
                      ),
                      SizedBox(
                        height: 15,
                      ),
                      Text("Exercises"),
                    ],
                  ),
                  onPressed: () {
                    Navigator.push(context,
                        MaterialPageRoute(builder: (context) => ExerciseList()));
                  },
                ),
              ),
              const SizedBox(
                width: 15,
              ),
              SizedBox(
                height: 150,
                width: 150,
                child: ElevatedButton(
                  child: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: const [
                      Icon(
                        Icons.library_music_rounded,
                        size: 70,
                      ),
                      SizedBox(
                        height: 15,
                      ),
                      Text("Songs"),
                    ],
                  ),
                  onPressed: () {
                    Navigator.push(context,
                        MaterialPageRoute(builder: (context) => SongList()));
                  },
                ),
              ),
            ],
          ),
          const SizedBox(
            height: 15,
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              SizedBox(
                height: 75,
                width: 315,
                child: ElevatedButton(
                  child: const Text("Settings"),
                  onPressed: () {
                  },
                ),
              ),
            ],
          ),
        ],
      ),
    );
  }
}

class ChordList extends DisplayStrList {
  final String barTitle = "Chords";
  final List<List<String>> itemList = [
    ["A.txt", "A"],
    ["ASharp.txt", "A# / Bb"],
    ["B.txt", "B"],
    ["C.txt", "C"],
    ["CSharp.txt", "C# / Db"],
    ["D.txt", "D"],
    ["DSharp.txt", "D# / Eb"],
    ["E.txt", "E"],
  ];
}

class ScaleList extends DisplayStrList {
  final String barTitle = "Scales";
  final List<List<String>> itemList = [
    [".txt", "I Pentatonic"],
    [".txt", "II Ionian"],
    [".txt", "III Minor Pentatonic"],
    [".txt", "IV Minor Ionian"],
  ];
}

class ExerciseList extends DisplayStrList {
  final String barTitle = "Exercises";
  final List<List<String>> itemList = [
    //[".txt", ""],
  ];
}

class SongList extends DisplayStrList {
  final String barTitle = "Songs";
  final List<List<String>> itemList = [
    ["newTest1.txt", "newTest1"],
    ["newTest2.txt", "newTest2"],
  ];
}