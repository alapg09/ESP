#include <iostream>
#include "Grid.h"
#include "color.h"

using namespace std;

char **initializeGrid(int rows, int columns) // creates a 2d array dynamically
{
    char **grid = new char *[rows]; // initializes the grid

    for (int i = 0; i < rows; i++)
    {
        grid[i] = new char[columns]; // initialized the columns
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            grid[i][j] = '.';
        }
    }

    return grid;
}

void displayGrid(int rows, int columns, char **grid, int player_row, int player_column) // showing the grid
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (grid[i][j] == '*')
            {
                cout << RED << grid[i][j] << ' ' << RESET;
            }
            else if (grid[i][j] == '.')
            {
                cout << GREEN << grid[i][j] << ' ' << RESET;
            }
            else
            {
                if (i == player_row && j == player_column)
                {
                    cout << YELLOW << grid[i][j] << ' ' << RESET;
                }
                else
                {
                    cout << WHITE << grid[i][j] << ' ' << RESET;
                }
            }
        }
        cout << endl;
    }
}

void freeGrid(int rows, char **grid) // deallocating the memory
{
    for (int i = 0; i < rows; i++)
    {
        delete[] grid[i];
    }
    delete[] grid;
}

int count_adjacentMines(int player_row, int player_column, int rows, int columns, char **grid)
{
    int adj_mines = 0;

    // check the top cell if it's within bounds
    if (player_row - 1 >= 0 && grid[player_row - 1][player_column] == '*')
    {
        adj_mines++;
    }

    // bottom cell
    if (player_row + 1 < rows && grid[player_row + 1][player_column] == '*')
    {
        adj_mines++;
    }

    // left cell
    if (player_column - 1 >= 0 && grid[player_row][player_column - 1] == '*')
    {
        adj_mines++;
    }

    // right cell
    if (player_column + 1 < columns && grid[player_row][player_column + 1] == '*')
    {
        adj_mines++;
    }

    return adj_mines;
}