#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

char **initializeGrid(int rows, int columns);
void placeMines(int rows, int columns, int number, char **grid);
void displayGrid(int rows, int columns, char **grid);
void freeGrid(int rows, char **grid);

int main()
{
    int answer;
    char **grid;
    srand(time(0));

    cout << "Welcome to MINE MAZE" << endl
         << "Please Select a difficulty level" << endl
         << "1 for easy, 2 for hard" << endl
         << "0 to quit" << endl;
    cin >> answer;

    while (!((answer == 0) || (answer == 1) || (answer == 2)))
    {
        cout << "Invalid Input. Please enter a number (0-2)";
        cin >> answer;
    }
    if (answer == 0)
    {
        cout << "GoodBye!";
        return 0;
    }
    else if (answer == 1)
    {
        grid = initializeGrid(5, 5);
        placeMines(5, 5, 8, grid);
        displayGrid(5, 5, grid);
    }
    else
    {
        grid = initializeGrid(8, 8);
        placeMines(8, 8, 15, grid);
        displayGrid(8, 8, grid);
    }

    freeGrid(5, grid);
    return 0;
}

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

void placeMines(int rows, int columns, int number, char **grid)
{

    int r, c; // for random column and row coordinate
    int placedMines = 0;
    while (placedMines < number) // ensuring that required amount of mines are placed after skipping the repititions and restricted cells
    {
        do
        {
            r = rand() % rows; // random number in the range
            c = rand() % columns;

        } while ((grid[r][c] == '*')); // ensuring that the cell is empty

        if ((r >= 0 && r <= 1 && c >= 0 && c <= 1) ||                                 // ensuring that starting point and adjacent cells are free of mines
            (r >= rows - 2 && r <= rows - 1 && c >= columns - 2 && c <= columns - 1)) // ensuring that ending point and adjacent cells are free of mines
        {
            continue;
        }
        grid[r][c] = '*'; // placement of mine
        placedMines++;
    }
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