import 'package:flutter/material.dart';
import 'displayStrList.dart';
import 'settings.dart';
import 'customFile.dart';
import 'ble.dart';

const buttonHeight = 125.0;
const buttonWidth = 150.0;
const dividerHeight = 12.5;
const dividerWidth = 12.5;

Blue blue = Blue();
int settingMaxBrightness = 30;
String fileListStr = "";

void main() {
  runApp(MaterialApp(
    title: 'Illumifret App',
    theme: ThemeData(
      colorSchemeSeed: Colors.pink,
      textTheme: const TextTheme(
        bodyMedium: TextStyle(fontSize: 20.0),
      ),
      elevatedButtonTheme: ElevatedButtonThemeData(
        style: ElevatedButton.styleFrom(
          backgroundColor: Colors.pink[100],
          foregroundColor: Colors.black,
          textStyle: const TextStyle(
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
                height: buttonHeight,
                width: buttonWidth,
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
                width: dividerWidth,
              ),
              SizedBox(
                height: buttonHeight,
                width: buttonWidth,
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
            height: dividerHeight,
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              SizedBox(
                height: buttonHeight,
                width: buttonWidth,
                child: ElevatedButton(
                  child: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: const [
                      Icon(
                        Icons.fitness_center_rounded,
                        size: 70,
                      ),
                      SizedBox(
                        height: 15,
                      ),
                      Text("Exercises"),
                    ],
                  ),
                  onPressed: () {
                    Navigator.push(
                        context,
                        MaterialPageRoute(
                            builder: (context) => ExerciseList()));
                  },
                ),
              ),
              const SizedBox(
                width: dividerWidth,
              ),
              SizedBox(
                height: buttonHeight,
                width: buttonWidth,
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
            height: dividerHeight,
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              SizedBox(
                height: buttonHeight,
                width: buttonWidth,
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
                      Text("Animations"),
                    ],
                  ),
                  onPressed: () {
                    Navigator.push(context,
                        MaterialPageRoute(builder: (context) => AnimationList()));
                  },
                ),
              ),
              const SizedBox(
                width: dividerWidth,
              ),
              SizedBox(
                height: buttonHeight,
                width: buttonWidth,
                child: ElevatedButton(
                  child: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: const [
                      Icon(
                        Icons.manage_search_rounded,
                        size: 70,
                      ),
                      SizedBox(
                        height: 15,
                      ),
                      Text("Custom"),
                    ],
                  ),
                  onPressed: () {
                    Navigator.push(
                      context,
                      MaterialPageRoute(builder: (context) => Custom())
                    );
                  },
                ),
              ),
            ],
          ),
          const SizedBox(
            height: dividerHeight,
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              SizedBox(
                height: buttonHeight,
                width: (buttonWidth*2 + dividerWidth),
                child: ElevatedButton(
                  child: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: const [
                      Icon(
                        Icons.settings_rounded,
                        size: 70,
                      ),
                      SizedBox(
                        height: 15,
                      ),
                      Text("Settings"),
                    ],
                  ),
                  onPressed: () {
                    Navigator.push(
                        context,
                        MaterialPageRoute(builder: (context) => Settings())
                    );
                  },
                ),
              ),
            ],
          ),
          const SizedBox(
            height: dividerHeight,
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              SizedBox(
                height: (buttonHeight/2),
                width: (buttonWidth*2 + dividerWidth),
                child: ElevatedButton(
                  child: const Text("Connect To Illumifret"),
                  onPressed: () {
                    blue.connect();
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
    //[".txt", ""],
  ];
}

class AnimationList extends DisplayStrList {
  final String barTitle = "Songs";
  final List<List<String>> itemList = [
    ["newTest1.txt", "newTest1"],
    ["newTest2.txt", "newTest2"],
  ];
}


