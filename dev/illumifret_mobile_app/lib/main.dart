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
    ["Amaj_1.txt", "A Maj - 1"],
    ["Amaj_2.txt", "A Maj - 2"],
    ["Amaj_3.txt", "A Maj - 3"],
    ["Amin_1.txt", "A Min - 1"],
    ["Amin_2.txt", "A Min - 2"],
    ["Amin_3.txt", "A Min - 3"],

    ["Bmaj_1.txt", "B Maj - 1"],
    ["Bmaj_2.txt", "B Maj - 2"],
    ["Bmaj_3.txt", "B Maj - 3"],
    ["Bmin_1.txt", "B Min - 1"],
    ["Bmin_2.txt", "B Min - 2"],

    ["Cmaj_1.txt", "C Maj - 1"],
    ["Cmaj_2.txt", "C Maj - 2"],
    ["Cmaj_3.txt", "C Maj - 3"],
    ["Cmin_1.txt", "C Min - 1"],
    ["Cmin_2.txt", "C Min - 2"],

    ["Dmaj_1.txt", "D Maj - 1"],
    ["Dmaj_2.txt", "D Maj - 2"],
    ["Dmaj_3.txt", "D Maj - 3"],
    ["Dmin_1.txt", "D Min - 1"],
    ["Dmin_2.txt", "D Min - 2"],

    ["Emaj_1.txt", "E Maj - 1"],
    ["Emaj_2.txt", "E Maj - 2"],
    ["Emaj_3.txt", "E Maj - 3"],
    ["Emin_1.txt", "E Min - 1"],
    ["Emin_2.txt", "E Min - 2"],
    ["Emin_3.txt", "E Min - 3"],

    ["Fmaj_1.txt", "F Maj - 1"],
    ["Fmaj_2.txt", "F Maj - 2"],
    ["Fmaj_3.txt", "F Maj - 3"],
    ["Fmin_1.txt", "F Min - 1"],
    ["Fmin_2.txt", "F Min - 2"],

    ["Gmaj_1.txt", "G Maj - 1"],
    ["Gmaj_2.txt", "G Maj - 2"],
    ["Gmaj_3.txt", "G Maj - 3"],
    ["Gmin_1.txt", "G Min - 1"],
    ["Gmin_2.txt", "G Min - 2"],
  ];
}

class ScaleList extends DisplayStrList {
  final String barTitle = "Scales";
  final List<List<String>> itemList = [
    ["Amaj_P.txt", "Amaj_P"],
    ["Amin_P.txt", "Amin_P"],
    ["Bmaj_P.txt", "Bmaj_P"],
    ["Bmin_P.txt", "Bmin_P"],
    ["Cmaj_P.txt", "Cmaj_P"],
    ["Dmaj_P.txt", "Dmaj_P"],
    ["Dmin_P.txt", "Dmin_P"],
    ["Emaj_P.txt", "Emaj_P"],
    ["Fmaj_P.txt", "Fmaj_P"],
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


