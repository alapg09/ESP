#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cctype> //for tolower function
#include <limits>
#include "Grid.h"             //for grid related functions like initialization, displaying and freeing
#include "mine_layouts.h"     //for placement of mines
#include "player_movements.h" //for player movements and mine detections

using namespace std;

int main()
{
    char answer, restart = 'y';
    char **grid = nullptr; // grid will be dynamically allocated using pointers
    int rows, columns;
    srand(time(0));

    // main menu

    do // game will run untill the user decides to quit
    {

        cout << "***********************************************" << endl
             << "*                                             *" << endl
             << "*               Welcome to MINE MAZE          *" << endl
             << "*                                             *" << endl
             << "*        Please Select a difficulty level     *" << endl
             << "*                                             *" << endl
             << "*    E/e for Easy      |    H/h for Hard      *" << endl
             << "*    Q/q to Quit       |    R/r for Rules     *" << endl
             << "*                                             *" << endl
             << "***********************************************" << endl;
        cin >> answer;

        //  validation for unexpected data types and extra characters
        while (cin.fail() || (cin.peek() != '\n' && cin.peek() != EOF))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a single character." << endl;
            cin >> answer;
        }

        answer = tolower(answer); // converting to lowercase

        // validating the input against allowed options
        while (answer != 'e' && answer != 'h' && answer != 'q' && answer != 'r')
        {
            cout << "Invalid input! Please enter E/e, H/h, or Q/q: ";
            cin >> answer;
            answer = tolower(answer);
            //  validation for unexpected data types and extra characters
            while (cin.fail() || (cin.peek() != '\n' && cin.peek() != EOF))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a single character." << endl;
                cin >> answer;
            }
        }

        if (answer == 'Q' || answer == 'q') // quitting
        {
            cout << "***********************************************" << endl
                 << "*                                             *" << endl
                 << "*          GoodBye! Quitting Now              *" << endl
                 << "*                                             *" << endl
                 << "***********************************************" << endl;

            return 0;
        }
        else if (answer == 'E' || answer == 'e') // easy level initialization
        {
            grid = initializeGrid(5, 5);
            placeMines(5, 5, 'e', grid);
            rows = 5, columns = 5;
        }
        else if (answer == 'H' || answer == 'h') // hard level initialization
        {
            grid = initializeGrid(8, 8);
            placeMines(8, 8, 'h', grid);
            rows = 8, columns = 8;
        }
        else
        {
            cout << "\n*************************************************************\n"
                 << "*                           RULES                             *\n"
                 << "***************************************************************\n"
                 << "* 1. Use W (up), A (left), S (down), and D (right) to move.   *\n"
                 << "* 2. The game ends if you step on a mine ('*').               *\n"
                 << "* 3. Reach the bottom-right corner to win the game.           *\n"
                 << "* 4. The number displayed on a cell shows adjacent mines.     *\n"
                 << "* 5. Moves outside the grid are not allowed.                  *\n"
                 << "* 6. If you choose 'R/r' from the menu, these rules will show.*\n"
                 << "***************************************************************\n"
                 << "Going back to the main menu";
            continue;
        }

        // player movement

        char **displayed_Grid = initializeGrid(rows, columns); // the grid that will be shown to the player
        displayed_Grid[0][0] = 'P';                            // initial position

        int player_row = 0, player_column = 0; // for keeping track of player positions

        while (true) // gameloop
        {

            displayGrid(rows, columns, displayed_Grid); // displaying the grid

            movement(player_row, player_column, rows, columns); // movement

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

        cout << "Do you want to go back to the main menu? (Y/y for yes and N/n for quitting) ";
        cin >> restart;

        // input validations
        while (cin.fail() || (cin.peek() != '\n' && cin.peek() != EOF))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input. Please enter Y/y for returning to main menu and N/n for Quitting" << endl;
            cin >> restart;
        }

        restart = tolower(restart);

        while (restart != 'y' && restart != 'n')
        {
            cout << "Invalid Input. Please enter Y/y for returning to main menu and N/n for Quitting";
            cin >> restart;
        }

    } while (restart == 'y');

    cout << "***********************************************" << endl
         << "*                                             *" << endl
         << "*          GoodBye! Quitting Now              *" << endl
         << "*                                             *" << endl
         << "***********************************************" << endl;

    return 0;
}
