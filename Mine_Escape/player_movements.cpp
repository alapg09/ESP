#include <iostream>
#include <limits>
#include <cctype>
#include "player_movements.h"
#include "file_operations.h"
#include "misc.h"
#include "color.h"

using namespace std;

bool valid_move(int newRow, int newCol, int rows, int columns)
{
    return (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < columns); // checking if player is going beyond grid boundaries
}

int movement(int &player_row, int &player_column, int rows, int columns, char **grid, char **displayedGrid) // movemwnt of player
{
    int new_row = player_row, new_column = player_column; // temporary variables that will be validated firsyt
    char move;

    while (true)
    {

        move = get_validated_input("Use W, A, S, D to move up, down, left, right.\nClick 'v' to save and quit the game.\n", "wasdv");

        move = tolower(move);

        if (cin.fail() || cin.peek() != '\n') // input validation for unexpected data types and longer inputs
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << GREEN << "Invalid input! Please enter a single character.\n"
                 << RESET;
            continue;
        }

        switch (move) // movement using increment operators
        {
        case 'w':
            new_row--;
            break;
        case 's':
            new_row++;
            break;
        case 'a':
            new_column--;
            break;
        case 'd':
            new_column++;
            break;
        case 'v':
            saveGame(rows, columns, player_row, player_column, grid, displayedGrid);
            return 0;
        default:
            cout << GREEN << "Invalid Input! use w/a/s/d" << endl
                 << RESET; // input validation
            continue;
        }
        if (valid_move(new_row, new_column, rows, columns)) // checks the validity of move ie it is not crossing the boundary
        {
            player_row = new_row; // now updates the player positions
            player_column = new_column;
            break;
        }
        else
        {
            cout << GREEN << "Invalid move! You can't go outside the grid." << endl
                 << RESET;
            new_row = player_row, new_column = player_column;
        }
    }
    return 1;
}