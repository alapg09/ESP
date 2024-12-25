#ifndef FILEOPERATION_H
#define FILEOPERATIONS_H

void saveGame(int rows, int columns, int player_row, int player_column, char **grid, char **displayed_Grid);
void loadGame(int &rows, int &columns, int &player_row, int &player_column, char **&grid, char **&displayed_Grid);

#endif