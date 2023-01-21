#include "../include/display.h"
#include <MLV/MLV_all.h>
#include <unistd.h>

#define NAME "SUDOKU"

/*initialise l'affichage*/
MLV_Font* display_init(int width, int height, int font_size){
    MLV_create_window("NAME", NULL, width, height);
    MLV_clear_window(MLV_rgba(255,192,203,255));
    MLV_Font* font = MLV_load_font("fonts/Montserrat.ttf", font_size);
    return font;
}

/*fonction affichant la grille à compléter*/
void display_base_grid(int nb_sqr, int sqr_size, int margin, Board grid, Board ref, char str[2], MLV_Font* font){
    for(int e=0; e<nb_sqr; e++){
            for(int i=0; i<nb_sqr; i++){
                str[0] = grid[e][i] + '0';
                str[1] = '\0';
                MLV_draw_rectangle(margin + (i+1) *sqr_size, margin + (e+1) *sqr_size, sqr_size, sqr_size, MLV_rgba(255,255,255,255));

                if(grid[e][i] != 0){
                    if(ref[e][i]!= 0){
                        MLV_draw_text_with_font(margin + (sqr_size/2) + (i+1)*sqr_size, margin + (sqr_size/2) + (e+1)*sqr_size, str, font, MLV_rgba(150,150,150,255));
                    }
                    else{
                        MLV_draw_text_with_font(margin + (sqr_size/2) + (i+1)*sqr_size, margin + (sqr_size/2) + (e+1)*sqr_size, str, font, MLV_rgba(255,255,255,255));
                    }
                }

            }
    }
}

/*fonction affichant la grille des numéros jouables*/
void display_playable_grid(int nb_sqr, int sqr_size, int margin_top, int margin_side, MLV_Font* font){
    int playable_grid[3][3] = {{1,2,3},{4,5,6},{7,8,9}};

    char playable_str[2];

    for(int e=0; e<3; e++){
        for(int i=0; i<3; i++){
            playable_str[0] = playable_grid[e][i] + '0';
            playable_str[1] = '\0';
            MLV_draw_rectangle(margin_side + i*sqr_size, margin_top + e*sqr_size, sqr_size, sqr_size, MLV_rgba(255,255,255,255));
            MLV_draw_text_with_font(margin_side + (sqr_size/2) + i*sqr_size, margin_top + (sqr_size/2) + e*sqr_size, playable_str, font, MLV_rgba(255,255,255,255));
        }
    }
}

/*fonction s'affichant lorsqu'un nombre invalide est entrée*/
void display_invalid_number(int margin_side, int margin_top, int sqr_size_mini, int nb_sqr_mini, MLV_Font* font){
    MLV_draw_text_with_font(margin_side,margin_top-sqr_size_mini,"CE NOMBRE N'EST PAS VALIDE", font, MLV_rgba(255,0,0,255));
    MLV_actualise_window();
}

/*fonction s'affichant à la fin du jeu (une fois le sudoku completé)*/
void display_end(int margin_side, int margin_top, int sqr_size_mini, int nb_sqr_mini, MLV_Font* font){
    MLV_draw_text_with_font(margin_side, margin_top-sqr_size_mini, "SUCCÈS ! MERCI D'AVOIR JOUÉ", font, MLV_rgba(255,255,255,255));
    MLV_actualise_window(); 
    sleep(5);
}

/*efface les messages précédents*/
void clear_message(int margin_side, int margin_top, int sqr_size_mini, int font_size){
    MLV_draw_filled_rectangle(margin_side, margin_top-sqr_size_mini, font_size*20, font_size, MLV_rgba(255,192,203,255));
    MLV_actualise_window(); 
}