# SuperMario

Super Mario is a project for my Semester 2 Assessment for my Games Engine Creation Module

The game is made using SDL2 found here -> [https://www.libsdl.org/](https://www.libsdl.org/)

The game is based off of Super Mario, and I used a emulated version on a [website](https://supermarioemulator.com/mario.php) as my inspiration. The whole point of the project was to make the original mario with no screen scrolling however I wanted to challenge myself further.

###Extra Features
1. Changing Window icon  
   The icon is assigned randomly when the window is created.
2. Map Generation From Txt files
   The map and its assets are all loaded in from a txt file in the MapLoader.cpp file
3. Title Screen
   I created a title screen as i have also made multiplayer allowing the user to select the amount of players they want for the game
4. Multiplayer
   I created multiplayer which also means the score and lives are shared.
5. New Lives
   A life is only lost when both the characters die in a level, if one completes the level the level will still be completed for both players
