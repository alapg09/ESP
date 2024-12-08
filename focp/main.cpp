#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include "Grid.h"             //for grid related functions like initialization, displaying and freeing
#include "mine_layouts.h"     //for placement of mines
#include "player_movements.h" //for player movements and mine detections

using namespace std;

int count_adjacentMines(int player_row, int player_column, char **grid);

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

    char **displayed_Grid = initializeGrid(rows, columns); // the grid that will be shown to the player
    displayed_Grid[0][0] = 'P';

    int player_row = 0, player_column = 0; // for keeping track of player positions

    while (true) // gameloop
    {

        displayGrid(rows, columns, displayed_Grid); // displaying the grid

        movement(player_row, player_column, rows, columns); // movement

        if (grid[player_row][player_column] == '*') // checking if the player hit a mine
        {
            cout << "You hit a mine! Game over." << endl;
            cout << "Here is the grid: " << endl;
            displayGrid(rows, columns, grid);
            break;
        }

        if (player_row == rows - 1 && player_column == columns - 1) // checking for last cell
        {
            cout << "Congratulations! You reached the goal." << endl;
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
    return 0;
}
