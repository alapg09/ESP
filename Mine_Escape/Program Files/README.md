MINE ESCAPE

Project Files
1. main.cpp: Main game loop and functionality.
2. grid.cpp: Functions for grid initialization, display, and mine detection.
3. mine_layouts.cpp: Responsible for mine placement.
4. player_movements.cpp: Handles player movement validation and execution.
5. file_operations.cpp: Future functionality for saving and loading the game.
6. misc.cpp: Utility functions, including input validation.

A compile.bat file is provided for easy compilation and running of the program.

How to Run
> Make sure all files are in the same directory and you are in the "Progam Files" directory. If not, use the command cd '.\Program Files\' to go to the directory
> Run compile.bat using the command :
    .\compile.bat 
to compile the game.
> Finally, run the game 
    .\Mine_Escape.exe
and enjoy!


Contents of compile.bat:

g++ -o Mine_Escape main.cpp misc.cpp grid.cpp player_movements.cpp mine_layouts.cpp file_operations.cpp


Game instructions and rules are mentioned inside the game!

Credits
Developers: Alap Gohar, Abdullah Khalil, Sikandar Hussain
Language: C++
