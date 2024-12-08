#include <iostream>
#include "Grid.h"

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

void displayGrid(int rows, int columns, char **grid) // showing the grid
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << grid[i][j] << ' ';
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
