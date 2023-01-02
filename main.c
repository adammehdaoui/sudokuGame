#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "sudoku.h"
#include "in_out.h"

int main(int argc, char* argv[]){
  Board B, ref;
  int i, j;
  
  fread_board(argv[1], B);
  
  for (i=0 ; i<9 ; i++){
    for (j=0 ; j<9 ; j++){
      ref[i][j] = B[i][j];
    }
  }

  display_game(B, ref);

  return 0;
}
