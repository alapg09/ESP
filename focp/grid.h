#ifndef GRID_H
#define GRID_H

char **initializeGrid(int rows, int columns);
void displayGrid(int rows, int columns, char **grid, int player_row, int player_column);
void freeGrid(int rows, char **grid);
int count_adjacentMines(int player_row, int player_column, int rows, int columns, char **grid);

#endif