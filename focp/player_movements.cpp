#include <iostream>
#include <limits>
#include "player_movements.h"

using namespace std;

bool valid_move(int newRow, int newCol, int rows, int columns)
{
    return (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < columns); // checking if player is going beyond grid boundaries
}

void movement(int &player_row, int &player_column, int rows, int columns) // movemwnt of player
{
    int new_row = player_row, new_column = player_column; // temporary variables that will be validated firsyt
    char move;

    while (true)
    {

        cout << "Use W, A, S, D to move up, down, left, right: " << endl;
        cin >> move;

        if (cin.fail() || cin.peek() != '\n') // input validation for unexpected data types and longer inputs
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a single character.\n";
            continue;
        }

        switch (move)
        {
        case 'w':
        case 'W':
            new_row--;
            break;
        case 's':
        case 'S':
            new_row++;
            break;
        case 'a':
        case 'A':
            new_column--;
            break;
        case 'd':
        case 'D':
            new_column++;
            break;
        default:
            cout << "Invalid Input! use w/a/s/d" << endl; // input validation
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
            cout << "Invalid move! You can't go outside the grid." << endl;
            new_row = player_row, new_column = player_column;
        }
    }
}