#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Grid.h"             //for grid related functions like initialization, displaying and freeing
#include "mine_layouts.h"     //for placement of mines
#include "player_movements.h" //for player movements

using namespace std;

int main()
{
    int answer;
    char **grid;
    int rows, columns;
    srand(time(0));

    // main menu
    cout << "Welcome to MINE MAZE" << endl
         << "Please Select a difficulty level" << endl // getting the difficulty
         << "1 for easy, 2 for hard" << endl
         << "0 to quit" << endl;
    cin >> answer;

    while (!((answer == 0) || (answer == 1) || (answer == 2))) // input validation
    {
        cout << "Invalid Input. Please enter a number (0-2)";
        cin >> answer;
    }
    if (answer == 0) // quitting
    {
        cout << "GoodBye!";
        return 0;
    }
    else if (answer == 1) // easy level initialization
    {
        grid = initializeGrid(5, 5);
        placeMines(5, 5, 'e', grid);
        rows = 5, columns = 5;
        // displayGrid(5, 5, grid);
    }
    else // hard level initialization
    {
        grid = initializeGrid(8, 8);
        placeMines(8, 8, 'h', grid);
        rows = 8, columns = 8;
        // displayGrid(8, 8, grid);
    }

    // player movement

    char **displayed_Grid = initializeGrid(rows, columns);
    displayed_Grid[0][0] = 'P';

    int player_row = 0, player_column = 0;

    while (true)
    {

        displayGrid(rows, columns, displayed_Grid);

        movement(player_row, player_column, rows, columns);

        if (grid[player_row][player_column] == '*')
        {
            cout << "You hit a mine! Game over." << endl;
            cout << "Here is the grid: " << endl;
            displayGrid(rows, columns, grid);
            break;
        }

        if (player_row == rows - 1 && player_column == columns - 1)
        {
            cout << "Congratulations! You reached the goal." << endl;
            break;
        }
    }

    freeGrid(rows, displayed_Grid);
    freeGrid(rows, grid);
    return 0;
}
