#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <MLV/MLV_all.h>
#include "../include/sudoku.h"

#define WIDTH 1400
#define HEIGHT 800

/*fonction renvoyant 1 si la grille est valide, 0 sinon*/
int grid_valid(Board grid){
    int x, y;

    for(x=0; x<9; x++){
        for(y=0; y<9; y++){
            if(grid[x][y]==0){
                return 0;
            }
        }
    }

    return 1;
}

/*fonction renvoyant 1 si la valeur se trouve dans la même ligne, 0 sinon*/
int line_valid(Board grid, int x, int value){
    int y;

    for(y=0; y<9; y++){
        if(grid[x][y]==value){
            return 1;
        }
    }

    return 0;
}

/*fonction renvoyant 1 si la valeur se trouve dans la même colonne, 0 sinon*/
int column_valid(Board grid, int y, int value){
    int x;

    for(x=0; x<9; x++){
        if(grid[x][y]==value){
            return 1;
        }
    }

    return 0;
}

/*fonction renvoyant 1 si la valeur se trouve dans la même case, 0 sinon*/
int box_valid(Board grid, int x, int y, int value){
    int line, column;

    for(line=0;line<=2;line++){
        for(column=0;column<=2;column++){
            if(grid[line+3*(x/3)][column+3*(y/3)]==value){
                return 1;
            }
        }
    }

    return 0;
}

/*fonction analysant les cliques de l'utilisateur en fonction des pixels*/
int game_to_px(int x, int y){
    /*grand tableau*/
    int nb_sqr = 9;
    int sqr_size = HEIGHT/(nb_sqr+3);
    int margin = sqr_size/2;

    /*tableau jouable*/
    int nb_sqr_mini = 3;
    int sqr_size_mini = HEIGHT/(nb_sqr_mini*3);
    int margin_top = sqr_size_mini+HEIGHT/4;
    int margin_side = sqr_size_mini*9;

    /*si x et y sont dans la grille alors on retourne 1*/
    if(x>margin+sqr_size && x<margin+(sqr_size*(nb_sqr+1)) && y>margin+sqr_size && y<margin+(sqr_size*(nb_sqr+1))){
        return 1;
    }
    /*si x et y sont dans la grille jouable alors on retourne 2*/
    else if(x>margin_side && x<margin_side+(sqr_size_mini*nb_sqr_mini) && y>margin_top && y<margin_top+(sqr_size_mini*nb_sqr_mini)){
        return 2;
    }

    /*sinon on retourne 0*/
    return 0;    
}

/*fonction affichant la grille des numéros jouables*/
void display_playable_grid(int nb_sqr, int sqr_size, int margin_top, int margin_side){
    int playable_grid[3][3] = {{1,2,3},{4,5,6},{7,8,9}};

    char playable_str[2];

    for(int e=0; e<3; e++){
        for(int i=0; i<3; i++){
            playable_str[0] = playable_grid[e][i] + '0';
            playable_str[1] = '\0';
            MLV_draw_rectangle(margin_side + i*sqr_size, margin_top + e*sqr_size, sqr_size, sqr_size, MLV_rgba(255,255,255,255));
            MLV_draw_text(margin_side + (sqr_size/2) + i*sqr_size, margin_top + (sqr_size/2) + e*sqr_size, playable_str, MLV_rgba(255,255,255,255));
        }
    }
}

/*fonction s'affichant à la fin du jeu (une fois le sudoku completé)*/
void display_end(int margin_side, int margin_top, int sqr_size_mini, int nb_sqr_mini){
    MLV_draw_text(margin_side,margin_top-sqr_size_mini,"SUCCÈS",MLV_rgba(255,255,255,255));
    display_playable_grid(nb_sqr_mini, sqr_size_mini, margin_top, margin_side);
    MLV_actualise_window();
    usleep(10000000);
}

/*affiche les grilles du sudoku*/
void display_game(Board grid, Board ref){
    int x, y;

    /*paramètres de la grille de base*/
    int nb_sqr = 9;
    int sqr_size = HEIGHT/(nb_sqr+3);
    int margin = sqr_size/2;

    /*paramètres de la grille jouable*/
    int nb_sqr_mini = 3;
    int sqr_size_mini = HEIGHT/(nb_sqr_mini*3);
    int margin_top = sqr_size_mini+HEIGHT/4;
    int margin_side = sqr_size_mini*9;  

    /*paramètres de traitement*/
    char str[2];
    int caseI, caseJ;
    int posI, posJ;
    int ligne, colonne;

    MLV_create_window("SUDOKU", NULL, WIDTH, HEIGHT);

    /*affichage de la grille avec ses numéros*/
    for(int e=0; e<nb_sqr; e++){
            for(int i=0; i<nb_sqr; i++){
                str[0] = grid[e][i] + '0';
                str[1] = '\0';
                MLV_draw_rectangle(margin + (i+1) *sqr_size, margin + (e+1) *sqr_size, sqr_size, sqr_size, MLV_rgba(255,255,255,255));

                if(grid[e][i] != 0){
                    MLV_draw_text(margin + (sqr_size/2) + (i+1)*sqr_size, margin + (sqr_size/2) + (e+1)*sqr_size, str, MLV_rgba(255,255,255,255));
                }
            }
    }

    /*traitement des clics*/
    while(1 == 1 && 2 == 2){

        int test;
        test = game_to_px(x,y);

        caseI = (int)((y-margin)/sqr_size) - 1;
        caseJ = (int)((x-margin)/sqr_size) - 1;

        /*si clic dans la grille principale*/
        if(test == 1 && ref[caseI][caseJ] == 0){
            MLV_draw_text(((x-margin)/sqr_size)*sqr_size + margin + sqr_size/2,((y-margin)/sqr_size)*sqr_size + margin + sqr_size/2,"?",MLV_rgba(255,255,255,255));
            posI=((x-margin)/sqr_size)*sqr_size + margin + sqr_size/2;
            ligne = caseI;
            posJ=((y-margin)/sqr_size)*sqr_size + margin + sqr_size/2;
            colonne = caseJ;
        }
        /*si clic dans la grille jouable*/
        else if(test == 2){
            char write[2];
            int value = ((x-margin_side)/(sqr_size_mini)) + ((y-margin_top)/(sqr_size_mini))*3 + 1;
            if(box_valid(grid,ligne,colonne,value)==0 && line_valid(grid,ligne,value)==0 && column_valid(grid,colonne,value)==0){
                grid[ligne][colonne] = value;

                write[0] =  value + '0';
                write[1] = '\0';

                MLV_draw_filled_rectangle(posI-(sqr_size/2) + 1, posJ-(sqr_size/2) + 1, sqr_size-2, sqr_size-2, MLV_rgba(0,0,0,255));

                MLV_draw_text(posI, posJ, write, MLV_rgba(255,255,255,255));
            }
        }

        /*si le sudoku est terminé, on affiche un message de succès*/
        if(grid_valid(grid)){
            display_end(margin_side,margin_top,sqr_size_mini,nb_sqr_mini);
            return;
        }

        display_playable_grid(nb_sqr_mini, sqr_size_mini, margin_top, margin_side);
        MLV_actualise_window();

        MLV_wait_mouse(&x,&y);
        /*on ne rafraîchit pas la fenêtre tant que l'utilisateur n'a pas cliqué*/
    }
}

/*affiche le sudoku dans le terminal, fonction du TP6*/
void print_board(Board grid){
    int i, e;

    for(i=0; i<9; i++){
        printf("-------------------------------------\n");
        for(e=0; e<9; e++){
            if(grid[i][e]==0 && e==0){
                printf("|   |");
            }
            else if(grid[i][e]==0){
                printf("   |");
            }
            else if(e == 0){
                printf("| %d |",grid[i][e]);
            }
            else{
                printf(" %d |",grid[i][e]);
            }
        }
        printf("\n");
    }
    printf("-------------------------------------\n");
}

/*résout le sudoku, fonction du TP6*/
int permutations (Board grid, int ligne, int colonne)
{
    int k;

    /*si on sort du sudoku (il n'y a que 9 lignes)*/
    if (ligne > 8)
        return 1;

    /*la cellule contient une valeur: on passe à la suivante*/
    if (grid[ligne][colonne] != 0) {
        if (colonne == 8)
            return permutations(grid, ligne+1, 0);
        else
            return permutations(grid, ligne, colonne+1);  
    }

    /*la cellule contient un zéro, on doit donc la remplir*/
    for (k=1; k <= 9; k++)
    {
        if (box_valid(grid,ligne,colonne,k)==0 && line_valid(grid,ligne,k)==0 && column_valid(grid,colonne,k)==0)
        {
            grid[ligne][colonne] = k;

            if (colonne==8) {
                if (permutations(grid, ligne+1, 0))
                    return 1;
                    }
            else{
                if (permutations(grid, ligne, colonne+1))
                    return 1;
                    }        
        }
    }
    /*backtracking : on remet la zone à zéro*/
    grid[ligne][colonne] = 0;
    print_board(grid);
    usleep(100000);
    system("clear");
    usleep(100);

    return 0;
}