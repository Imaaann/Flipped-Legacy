#pragma once
#include <fl_types.h>
#include <ncurses/ncurses.h>

void fl_card_get_input(FLCard* card, WINDOW* input, int deck_index);
void fl_card_get_ultimate_input(FLUltimateCard* ultCard, WINDOW* input);
void fl_card_family_get_input(FLCardFamily* family, WINDOW* input, int current, int total);
void fl_card_family_print(FLCardFamily* family, WINDOW* main, int y, int index, int total);