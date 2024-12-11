#ifndef PLAYERMOVEMENT_H
#define PLAYERMOVEMENT_H

bool valid_move(int newRow, int newCol, int rows, int columns);
int movement(int &player_row, int &player_column, int rows, int columns, char **grid, char **displayedGrid);

#endif
