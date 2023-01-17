#include <stdio.h>
#include <stdlib.h>
#include "../include/in_out.h"
#include "../include/sudoku.h"

int main(int argc, char* argv[]){
  Board B, ref;
  int i, j;
  
  fread_board(argv[1], B);
  
  for (i=0 ; i<9 ; i++){
    for (j=0 ; j<9 ; j++){
      ref[i][j] = B[i][j];
    }
  }

  game(B, ref);

  return 0;
}
