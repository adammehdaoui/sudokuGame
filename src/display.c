#include "../include/display.h"
#include <MLV/MLV_all.h>

#define NAME "SUDOKU"

/**
 * @brief Initialise l'affichage du jeu (crée une fenêtre et la remplit en rose)
 * 
 * @param width 
 * @param height 
 * @param font_size 
 * @return MLV_Font* Variable de type "font" récupéré dans la fonction game
 */
MLV_Font* display_init(int width, int height, int font_size){
    MLV_create_window("NAME", NULL, width, height);
    MLV_clear_window(MLV_rgba(255,192,203,255));
    MLV_Font* font = MLV_load_font("fonts/Montserrat.ttf", font_size);
    return font;
}

/**
 * @brief Affiche la grille de sudoku à remplir 
 *
 * @param nb_sqr 
 * @param sqr_size 
 * @param margin 
 * @param grid Paramètre récupéré à partir d'un fichier texte grid*.txt
 * @param ref Paramètre permettant de garder la grille de base pour la comparer dans 
 différents traitements
 * @param str 
 * @param font 
 */
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

/**
 * @brief Fonction affichant la grille des numéros jouables (de 1 à 9)
 * 
 * @param nb_sqr 
 * @param sqr_size 
 * @param margin_top 
 * @param margin_side 
 * @param font 
 */
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

/**
 * @brief Fonction affichant un point d'interrogation dans la grille à compléter
 * 
 * @param posI 
 * @param posJ 
 * @param sqr_size 
 * @param font 
 */
void display_question_mark(int posI, int posJ, int sqr_size, MLV_Font* font){
    MLV_draw_filled_rectangle(posI-(sqr_size/2) + 1, posJ-(sqr_size/2) + 1, sqr_size-2, sqr_size-2, MLV_rgba(255,192,203,255));
    MLV_draw_text_with_font(posI, posJ, "?", font, MLV_rgba(255,255,255,255));
}

/**
 * @brief Fonction affichant un numéro ajouté dans la grille à compléter
 * 
 * @param posI 
 * @param posJ 
 * @param sqr_size 
 * @param write Paramètre correspondant au numéro à afficher
 * @param font 
 */
void display_number(int posI, int posJ, int sqr_size, char write[], MLV_Font* font){
    MLV_draw_filled_rectangle(posI-(sqr_size/2) + 1, posJ-(sqr_size/2) + 1, sqr_size-2, sqr_size-2, MLV_rgba(255,192,203,255));

    MLV_draw_text_with_font(posI, posJ, write, font, MLV_rgba(255,255,255,255));
}

/**
 * @brief Fonction affichant un message d'erreur lorsque un numéro placé est invalide
 * 
 * @param margin_side 
 * @param margin_top 
 * @param sqr_size_mini 
 * @param nb_sqr_mini 
 * @param font 
 */
void display_invalid_number(int posI, int posJ, int margin_side, int margin_top, int sqr_size, int sqr_size_mini, int nb_sqr_mini, MLV_Font* font){
    MLV_draw_text_with_font(margin_side,margin_top-sqr_size_mini,"CE NOMBRE N'EST PAS VALIDE", font, MLV_rgba(255,0,0,255));
    MLV_draw_filled_rectangle(posI-(sqr_size/2) + 1, posJ-(sqr_size/2) + 1, sqr_size-2, sqr_size-2, MLV_rgba(255,192,203,255));
}

/**
 * @brief Fonction affichant un message de félicitations une fois que le jeu est terminé
 * 
 * @param margin_side 
 * @param margin_top 
 * @param sqr_size_mini 
 * @param nb_sqr_mini 
 * @param font 
 */
void display_end(int margin_side, int margin_top, int sqr_size_mini, int nb_sqr_mini, MLV_Font* font){
    MLV_draw_text_with_font(margin_side, margin_top-sqr_size_mini, "SUCCÈS ! MERCI D'AVOIR JOUÉ", font, MLV_rgba(255,255,255,255));
    MLV_actualise_window(); 
}

/**
 * @brief Fonction effacant le point d'interrogation précédent si l'on souhaite placer un chiffre
 à une autre position
 * 
 * @param posI 
 * @param posJ 
 * @param sqr_size 
 */
void clear_question_mark(int posI, int posJ, int sqr_size){
    MLV_draw_filled_rectangle(posI-(sqr_size/2) + 1, posJ-(sqr_size/2) + 1, sqr_size-2, sqr_size-2, MLV_rgba(255,192,203,255));
}

/**
 * @brief Fonction effacant les messages antérieurs pour ne pas les garder trop longtemps 
 au sein du jeu
 * 
 * @param margin_side 
 * @param margin_top 
 * @param sqr_size_mini 
 * @param font_size 
 */
void clear_message(int margin_side, int margin_top, int sqr_size_mini, int font_size){
    MLV_draw_filled_rectangle(margin_side, margin_top-sqr_size_mini, font_size*20, font_size, MLV_rgba(255,192,203,255));
    MLV_actualise_window(); 
}