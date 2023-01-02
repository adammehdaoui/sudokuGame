#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "in_out.h"

int fread_board(const char *file, Board board){
  FILE* f;
  int i,j;
  int entry;
  const char *path = "data/";
  char *full_path;
  full_path = malloc(strlen(file)+5);
  strcpy(full_path, path);
  strcat(full_path, file);

  f = fopen(full_path, "r");
  if (f == NULL){
    fprintf(stderr, "Erreur d'ouverture du fichier %s\n", file);
    return 0;
  }

  for (i=0 ; i<9 ; i++){
    for (j=0 ; j<9 ; j++){
      fscanf(f, "%d", &entry);
      board[i][j] = entry;
    }
  }

  fclose(f);

  return 1;
}
