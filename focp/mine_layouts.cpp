#include "mine_layouts.h"
#include <cstdlib>

void placeMines(int rows, int columns, char difficulty, char **grid)
{
    char layouts_easy[10][5][5] = {// different grid positions for easy level
                                   {{'.', '.', '.', '*', '*'},
                                    {'.', '.', '.', '*', '.'},
                                    {'.', '.', '.', '*', '.'},
                                    {'.', '*', '.', '.', '.'},
                                    {'*', '*', '*', '*', '.'}},
                                   {{'.', '.', '*', '*', '.'},
                                    {'.', '.', '.', '.', '.'},
                                    {'*', '.', '*', '*', '.'},
                                    {'.', '.', '.', '*', '.'},
                                    {'.', '*', '.', '.', '.'}},
                                   {{'.', '.', '*', '*', '.'},
                                    {'.', '.', '.', '*', '*'},
                                    {'.', '.', '*', '.', '.'},
                                    {'*', '.', '.', '*', '*'},
                                    {'.', '*', '.', '.', '.'}},
                                   {{'.', '.', '*', '.', '.'},
                                    {'.', '.', '.', '.', '*'},
                                    {'*', '.', '*', '*', '.'},
                                    {'.', '.', '.', '.', '.'},
                                    {'*', '*', '.', '*', '.'}},
                                   {{'.', '.', '.', '.', '.'},
                                    {'.', '.', '*', '*', '.'},
                                    {'*', '.', '.', '*', '*'},
                                    {'*', '.', '.', '.', '*'},
                                    {'.', '.', '*', '.', '.'}},
                                   {{'.', '.', '.', '*', '.'},
                                    {'.', '.', '.', '.', '*'},
                                    {'.', '.', '*', '*', '*'},
                                    {'*', '.', '.', '.', '.'},
                                    {'.', '.', '.', '*', '.'}},
                                   {{'.', '.', '.', '.', '*'},
                                    {'.', '.', '*', '.', '.'},
                                    {'*', '.', '.', '*', '*'},
                                    {'.', '.', '.', '*', '.'},
                                    {'.', '*', '.', '.', '.'}},
                                   {{'.', '.', '*', '.', '.'},
                                    {'.', '.', '.', '.', '*'},
                                    {'*', '.', '*', '.', '.'},
                                    {'.', '.', '.', '*', '.'},
                                    {'.', '*', '.', '.', '*'}},
                                   {{'.', '.', '.', '*', '.'},
                                    {'.', '.', '*', '.', '.'},
                                    {'.', '.', '.', '*', '*'},
                                    {'*', '.', '.', '.', '.'},
                                    {'.', '.', '*', '*', '.'}},
                                   {{'.', '.', '*', '*', '.'},
                                    {'.', '.', '.', '.', '*'},
                                    {'*', '.', '*', '.', '.'},
                                    {'.', '.', '.', '*', '*'},
                                    {'*', '*', '.', '.', '.'}}};

    char layouts_hard[5][8][8] = {// different grid positions for hard level
                                  {{'.', '.', '*', '.', '.', '.', '.', '.'},
                                   {'.', '.', '.', '*', '.', '*', '.', '.'},
                                   {'*', '*', '.', '.', '.', '.', '*', '.'},
                                   {'.', '.', '.', '*', '.', '.', '.', '*'},
                                   {'.', '.', '*', '.', '*', '.', '.', '.'},
                                   {'*', '.', '.', '.', '.', '*', '.', '.'},
                                   {'.', '*', '.', '*', '.', '.', '.', '.'},
                                   {'.', '.', '.', '.', '*', '.', '.', '.'}},
                                  {{'.', '.', '.', '*', '.', '.', '*', '.'},
                                   {'*', '.', '*', '.', '.', '.', '.', '.'},
                                   {'.', '.', '.', '.', '*', '.', '.', '.'},
                                   {'*', '.', '*', '.', '.', '*', '.', '.'},
                                   {'.', '.', '.', '.', '*', '.', '.', '*'},
                                   {'*', '.', '.', '*', '.', '.', '.', '.'},
                                   {'.', '.', '*', '.', '*', '.', '.', '.'},
                                   {'.', '.', '.', '.', '.', '*', '.', '*'}},
                                  {{'.', '*', '.', '.', '.', '*', '.', '.'},
                                   {'.', '.', '.', '*', '.', '.', '.', '.'},
                                   {'.', '.', '*', '.', '.', '*', '.', '*'},
                                   {'*', '.', '.', '.', '.', '.', '.', '.'},
                                   {'.', '.', '*', '.', '*', '.', '.', '*'},
                                   {'.', '*', '.', '.', '.', '.', '*', '.'},
                                   {'.', '.', '.', '.', '.', '*', '.', '.'},
                                   {'*', '.', '.', '*', '.', '.', '.', '.'}},
                                  {{'.', '.', '.', '.', '*', '.', '.', '*'},
                                   {'.', '*', '.', '.', '.', '*', '.', '.'},
                                   {'*', '.', '.', '*', '.', '.', '.', '.'},
                                   {'.', '.', '*', '.', '.', '*', '.', '.'},
                                   {'.', '*', '.', '.', '.', '.', '*', '.'},
                                   {'.', '.', '.', '.', '*', '.', '.', '*'},
                                   {'*', '.', '.', '.', '.', '.', '*', '.'},
                                   {'.', '.', '*', '.', '.', '.', '.', '.'}},
                                  {{'*', '.', '.', '.', '.', '.', '*', '.'},
                                   {'.', '.', '.', '*', '.', '.', '.', '.'},
                                   {'.', '*', '.', '.', '.', '*', '.', '.'},
                                   {'.', '.', '.', '.', '.', '.', '*', '.'},
                                   {'.', '.', '*', '.', '*', '.', '.', '*'},
                                   {'*', '.', '.', '*', '.', '.', '.', '.'},
                                   {'.', '.', '.', '.', '.', '.', '*', '.'},
                                   {'*', '.', '.', '.', '*', '.', '.', '.'}}};

    // populating the original grid with the layouts
    if (difficulty == 'e')
    {
        int randomE = rand() % 10; // random choice
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                grid[i][j] = layouts_easy[randomE][i][j];
            }
        }
    }
    else
    {
        int randomH = rand() % 5; // random choice
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                grid[i][j] = layouts_hard[randomH][i][j];
            }
        }
    }
}
