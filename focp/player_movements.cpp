#include <iostream>
#include "player_movements.h"

using namespace std;

bool valid_move(int newRow, int newCol, int rows, int columns)
{
    return (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < columns);
}

void movement(int &player_row, int &player_column, int rows, int columns)
{
    int new_row = player_row, new_column = player_column;
    char move;

    while (true)
    {

        cout << "Use W, A, S, D to move up, down, left, right: " << endl;
        cin >> move;

        switch (move)
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
        default:
            cout << "Invalid Input! use w/a/s/d" << endl;
            continue;
        }
        if (valid_move(new_row, new_column, rows, columns))
        {
            player_row = new_row;
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