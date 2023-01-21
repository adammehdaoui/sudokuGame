#include <unistd.h>
#include "../include/sudoku.h"
#include "../include/display.h"

#define WIDTH 1400
#define HEIGHT 800
#define FONT 20

/**
 * @brief Fonction testant si une grille est complétée et valide
 * 
 * @param grid 
 * @return int Retourne 1 si la grille est complétée et valide, 0 sinon
 */
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

/**
 * @brief Fonction testant si un chiffre est plaçable en fonction de sa ligne
 * 
 * @param grid 
 * @param x 
 * @param value 
 * @return int Retourne 1 si le chiffre est plaçable en fonction de sa ligne, 0 sinon
 */
int line_valid(Board grid, int x, int value){
    int y;

    for(y=0; y<9; y++){
        if(grid[x][y]==value){
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Fonction testant si un chiffre est plaçable en fonction de sa colonne
 * 
 * @param grid 
 * @param x 
 * @param value 
 * @return int Retourne 1 si le chiffre est plaçable en fonction de sa colonne, 0 sinon
 */
int column_valid(Board grid, int y, int value){
    int x;

    for(x=0; x<9; x++){
        if(grid[x][y]==value){
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Fonction testant si un chiffre est plaçable en fonction de sa box (ici 3x3)
 * 
 * @param grid 
 * @param x 
 * @param value 
 * @return int Retourne 1 si le chiffre est plaçable en fonction de sa box, 0 sinon
 */
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

/**
 * @brief Fonction analysant les clics de l'utilateur
 * 
 * @param x 
 * @param y 
 * @param nb_sqr 
 * @param sqr_size 
 * @param margin 
 * @param nb_sqr_mini 
 * @param sqr_size_mini 
 * @param margin_top 
 * @param margin_side 
 * @return int Retourne 1 si le clic est dans la grille à compléter ou retourne 2 si le clic
 est dans la grille des numéros jouables, 0 sinon
 */
int game_to_px(int x, int y, int nb_sqr, int sqr_size, int margin, int nb_sqr_mini, int sqr_size_mini, int margin_top, int margin_side){
    
    if(x>margin+sqr_size && x<margin+(sqr_size*(nb_sqr+1)) && y>margin+sqr_size && y<margin+(sqr_size*(nb_sqr+1))){
        return 1;
    }

    else if(x>margin_side && x<margin_side+(sqr_size_mini*nb_sqr_mini) && y>margin_top && y<margin_top+(sqr_size_mini*nb_sqr_mini)){
        return 2;
    }

    return 0;    
}

/**
 * @brief Fonction principale contenant la plupart des appels de fonctions dans le cadre du 
 jeu
 * 
 * @param grid Paramètre correspondant à la grille à compléter (sera modifié au cours du jeu)
 * @param ref Paramètre correspondant à la grille à compléter au départ 
 (ne sera pas modifié au cours du jeu)
 */
void game(Board grid, Board ref){
    int x = 0;
    int y = 0;

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
    int test;
    int lastWasQM = 0;
    int caseI, caseJ;
    int posI = 0; 
    int posJ = 0;
    int ligne, colonne;

    /*initialise le jeu*/
    MLV_Font* font = display_init(WIDTH, HEIGHT, FONT);

    /*affichage de la grille avec ses numéros*/
    display_base_grid(nb_sqr, sqr_size, margin, grid, ref, str, font);

    /*affichage de la grille de numéros jouables*/
    display_playable_grid(nb_sqr_mini, sqr_size_mini, margin_top, margin_side, font);

    /*traitement des clics*/
    while(1){

        /*nettoie les messages précédents pour ne pas polluer le jeu*/
        clear_message(margin_side, margin_top, sqr_size_mini, FONT);

        /*analyse des clics de l'utilisateur*/
        test = game_to_px(x, y, nb_sqr, sqr_size, margin, nb_sqr_mini, sqr_size_mini, margin_top, margin_side);

        /*récupération de l'indice des cases en fonction de leurs coordonnées dans le jeu*/
        caseI = (int)((y-margin)/sqr_size) - 1;
        caseJ = (int)((x-margin)/sqr_size) - 1;

        /*si clic dans la grille principale*/
        if(test == 1 && ref[caseI][caseJ] == 0){
            if(lastWasQM){
                clear_question_mark(posI, posJ, sqr_size);
            }

            posI=((x-margin)/sqr_size)*sqr_size + margin + sqr_size/2;
            ligne = caseI;
            posJ=((y-margin)/sqr_size)*sqr_size + margin + sqr_size/2;
            colonne = caseJ;

            display_question_mark(posI, posJ, sqr_size, font);

            lastWasQM = 1;
        }
        /*si clic dans la grille de numéros jouables*/
        else if(test == 2 && posI!=0 && posJ!=0){
            char write[2];
            int value = ((x-margin_side)/(sqr_size_mini)) + ((y-margin_top)/(sqr_size_mini))*3 + 1;
            if(box_valid(grid,ligne,colonne,value)==0 && line_valid(grid,ligne,value)==0 && column_valid(grid,colonne,value)==0){
                grid[ligne][colonne] = value;

                write[0] =  value + '0';
                write[1] = '\0';

                display_number(posI, posJ, sqr_size, write, font);
            }
            else{
                display_invalid_number(posI, posJ, margin_side, margin_top, sqr_size, sqr_size_mini, nb_sqr_mini, font);
            }

            lastWasQM = 0;
        }

        /*si le sudoku est terminé, on affiche un message de succès et on ferme le jeu*/
        if(grid_valid(grid)){
            display_end(margin_side, margin_top, sqr_size_mini, nb_sqr_mini, font);
            sleep(5);
            return;
        }

        MLV_actualise_window();

        /*on ne rafraîchit pas la fenêtre tant que l'utilisateur n'a pas cliqué*/
        MLV_wait_mouse(&x,&y);
    }
}