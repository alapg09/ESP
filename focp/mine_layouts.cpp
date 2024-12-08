#include "mine_layouts.h"
#include <cstdlib>

void placeMines(int rows, int columns, char difficulty, char **grid)
{
    char layouts_easy[5][5][5] = {// different grid positions for easy level
                                  {{'.', '.', '.', '.', '*'},
                                   {'.', '*', '.', '*', '.'},
                                   {'.', '.', '.', '*', '.'},
                                   {'.', '*', '.', '.', '.'},
                                   {'*', '*', '*', '*', '.'}},
                                  {{'.', '.', '*', '*', '.'},
                                   {'.', '.', '.', '.', '.'},
                                   {'*', '.', '*', '*', '.'},
                                   {'.', '.', '.', '*', '.'},
                                   {'.', '*', '.', '.', '.'}},
                                  {{'.', '.', '.', '*', '.'},
                                   {'.', '*', '.', '*', '*'},
                                   {'.', '.', '*', '.', '.'},
                                   {'*', '.', '.', '*', '*'},
                                   {'.', '*', '.', '.', '.'}},
                                  {{'.', '.', '*', '.', '.'},
                                   {'.', '.', '.', '.', '*'},
                                   {'*', '.', '*', '*', '.'},
                                   {'.', '.', '.', '.', '.'},
                                   {'*', '*', '.', '*', '.'}},
                                  {{'.', '.', '.', '.', '.'},
                                   {'.', '*', '*', '*', '.'},
                                   {'.', '.', '.', '*', '*'},
                                   {'*', '.', '.', '.', '*'},
                                   {'.', '.', '*', '.', '.'}}

    };

    char layouts_hard[5][8][8] = {// different grid positions for hard level
                                  {{'.', '.', '*', '.', '.', '.', '.', '.'},
                                   {'*', '.', '.', '*', '.', '*', '.', '.'},
                                   {'.', '*', '.', '.', '.', '.', '*', '.'},
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

    int random = rand() % 5; // random choice

    // populating the original grid with the layouts
    if (difficulty == 'e')
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                grid[i][j] = layouts_easy[random][i][j];
            }
        }
    }
    else
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                grid[i][j] = layouts_hard[random][i][j];
            }
        }
    }
}
