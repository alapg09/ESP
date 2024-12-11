#include <iostream>
#include <fstream> //file i/o
#include "file_operations.h"
#include "grid.h"

using namespace std;

void saveGame(int rows, int columns, int player_row, int player_column, char **grid, char **displayed_Grid)
{
    ofstream outFile("save_game.txt");
    if (!outFile)
    {
        cout << "Error opening file for loading!" << endl;
        return;
    }

    outFile << rows << " " << columns << " " << player_row << " " << player_column << "\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            outFile << grid[i][j] << " ";
        }
        outFile << "\n";
    }
    outFile << "DISPLAYED\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            outFile << displayed_Grid[i][j] << " ";
        }
        outFile << "\n";
    }
    outFile.close();
}

void loadGame(int &rows, int &columns, int &player_row, int &player_column, char **&grid, char **&displayed_Grid)
{
    ifstream inFile("save_game.txt");
    if (!inFile)
    {
        cout << "Error opening file for loading!" << endl;
        return;
    }
    inFile >> rows >> columns >> player_row >> player_column;

    grid = initializeGrid(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            inFile >> grid[i][j];
        }
    }

    string line;
    inFile >> line; // Skips the "DISPLAYED" line
    displayed_Grid = initializeGrid(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            inFile >> displayed_Grid[i][j];
        }
    }
    inFile.close();
}
