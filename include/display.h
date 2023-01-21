#ifndef __DISPLAY__
#define __DISPLAY__

#include <MLV/MLV_all.h>

#include "sudoku.h"

MLV_Font* display_init(int width, int height, int font_size);

void display_base_grid(int nb_sqr, int sqr_size, int margin, Board grid, Board ref, char str[2], MLV_Font* font);

void display_playable_grid(int nb_sqr, int sqr_size, int margin_top, int margin_side, MLV_Font* font);

void display_question_mark(int posI, int posJ, int sqr_size, MLV_Font* font);

void display_number(int posI, int posJ, int sqr_size, char write[], MLV_Font* font);

void display_invalid_number(int posI, int posJ, int margin_side, int margin_top, int sqr_size, int sqr_size_mini, int nb_sqr_mini, MLV_Font* font);

void display_end(int margin_side, int margin_top, int sqr_size_mini, int nb_sqr_mini, MLV_Font* font);

void clear_question_mark(int posI, int posJ, int sqr_size);

void clear_message(int margin_side, int margin_top, int sqr_size_mini, int size_font);

#endif