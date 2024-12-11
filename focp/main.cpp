#include <iostream>
#include <ctime>   //time function
#include <cstdlib> //rand
#include <string>
#include <cctype> //for tolower function
#include <limits>
#include "Grid.h"             //for grid related functions like initialization, displaying and freeing
#include "mine_layouts.h"     //for placement of mines
#include "player_movements.h" //for player movements and mine detections
#include "file_operations.h"  //for saving and loading grid states;

using namespace std;

char getValidatedInput(const string &prompt, const string &validOptions); // modularizing repetitive input validations

int main()
{
    char answer, restart = 'y';
    char **grid = nullptr; // grid will be dynamically allocated using pointers
    char **displayed_Grid = nullptr;
    int rows, columns, player_row, player_column;
    srand(time(0));

    // main menu

    do // game will run untill the user decides to quit
    {

        cout << "***********************************************" << endl
             << "*                                             *" << endl
             << "*               Welcome to MINE MAZE          *" << endl
             << "*                                             *" << endl
             << "*            Please Select an Option          *" << endl
             << "*                                             *" << endl
             << "*         'l' to load previous game           *" << endl
             << "*    'e; for Easy      |    'h' for Hard      *" << endl
             << "*    'q' to quit       |    'r' for Rules     *" << endl
             << "*                                             *" << endl
             << "***********************************************" << endl;
        answer = getValidatedInput("", "lehqr");

        if (answer == 'q') // quitting
        {
            cout << "***********************************************" << endl
                 << "*                                             *" << endl
                 << "*          GoodBye! Quitting Now              *" << endl
                 << "*                                             *" << endl
                 << "***********************************************" << endl;

            return 0;
        }
        else if (answer == 'e') // easy level initialization
        {
            grid = initializeGrid(5, 5);
            placeMines(5, 5, 'e', grid);
            rows = 5, columns = 5;
        }
        else if (answer == 'h') // hard level initialization
        {
            grid = initializeGrid(8, 8);
            placeMines(8, 8, 'h', grid);
            rows = 8, columns = 8;
        }
        else if (answer == 'r')
        {
            cout << "\n*************************************************************\n"
                 << "*                           RULES                             *\n"
                 << "***************************************************************\n"
                 << "* 1. Use W (up), A (left), S (down), and D (right) to move.   *\n"
                 << "* 2. The game ends if you step on a mine ('*').               *\n"
                 << "* 3. Reach the bottom-right corner to win the game.           *\n"
                 << "* 4. The number displayed on a cell shows adjacent mines.     *\n"
                 << "* 5. Moves outside the grid are not allowed.                  *\n"
                 << "* 6. If you choose 'r' from the menu, these rules will show.  *\n"
                 << "* 7. You can save the game during any move by clicking 's'.   *\n"
                 << "***************************************************************\n"
                 << "Going back to the main menu" << endl;
            continue;
        }
        else
        {
            loadGame(rows, columns, player_row, player_column, grid, displayed_Grid);
            cout << "Game loaded successfully!" << endl;
        }

        // player movement
        if (answer != 'l') // making sure that displayed grid is not re initialised in the case of load game
        {

            displayed_Grid = initializeGrid(rows, columns); // the grid that will be shown to the player
            displayed_Grid[0][0] = 'P';                     // initial position

            player_row = 0, player_column = 0; // for keeping track of player positions
        }

        while (true) // gameloop
        {

            displayGrid(rows, columns, displayed_Grid); // displaying the grid
            int save;
            save = movement(player_row, player_column, rows, columns, grid, displayed_Grid); // movement
            if (save == 0)
            {
                cout << "Successfully saved the game." << endl;
                break;
            }

            if (grid[player_row][player_column] == '*') // checking if the player hit a mine
            {
                cout << "***********************************************" << endl
                     << "*                                             *" << endl
                     << "*          OOPS!!! You hit a mine!            *" << endl
                     << "*                GAME OVER!                   *" << endl
                     << "*                                             *" << endl
                     << "***********************************************" << endl;
                cout << "Here is the grid: " << endl;
                displayGrid(rows, columns, grid);
                break;
            }

            if (player_row == rows - 1 && player_column == columns - 1) // checking for last cell
            {
                cout << "***********************************************" << endl
                     << "*                                             *" << endl
                     << "*          Congratulations! You reached       *" << endl
                     << "*                the goal.                    *" << endl
                     << "*                                             *" << endl
                     << "***********************************************" << endl;

                cout << "Here is the grid: " << endl;
                displayGrid(rows, columns, grid);
                break;
            }

            // calculating the adjacent mines for providing the hint
            int adj_mines = count_adjacentMines(player_row, player_column, rows, columns, grid);

            // converting int to string and displaying the character
            string count = to_string(adj_mines);
            displayed_Grid[player_row][player_column] = count[0];
        }

        freeGrid(rows, displayed_Grid);
        freeGrid(rows, grid);

        restart = getValidatedInput("Do you want to go back to the main menu? (Y/y for yes and N/n for quitting) ", "yn");

    } while (restart == 'y');

    cout << "***********************************************" << endl
         << "*                                             *" << endl
         << "*          GoodBye! Quitting Now              *" << endl
         << "*                                             *" << endl
         << "***********************************************" << endl;

    return 0;
}

char getValidatedInput(const string &prompt, const string &validOptions)
{
    char input;
    while (true)
    {
        cout << prompt;
        cin >> input;

        // validates only single characteredi innputs
        if (cin.fail() || (cin.peek() != '\n' && cin.peek() != EOF))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a single character." << endl;
            continue;
        }

        input = tolower(input);

        // Check against valid options
        if (validOptions.find(input) != string::npos) // checks if entered options are among the ones allowed
        {
            return input;
        }

        cout << "Invalid input! Please enter one of the following: " << validOptions << endl;
    }
}
