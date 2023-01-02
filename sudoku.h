#ifndef __SUDOKU__
#define __SUDOKU__

typedef int Board[9][9];

void print_board(Board grid);
void display_game(Board grid, Board ref);
// void line_valid(Board grid, int x, int value);
// void column_valid(Board grid, int y, int value);
// void box_valid(Board grid, int x, int y, int value);
int permutations (Board grid, int ligne, int colonne);

#endif
