#pragma once
#include <fl_types.h>
#include <ncurses/ncurses.h>

// Alpha Version API
void fl_card_get_input(FLCard* card, WINDOW* input, int deck_index);
void fl_card_get_ultimate_input(FLUltimateCard* ultCard, WINDOW* input);
void fl_card_family_get_input(FLCardFamily* family, WINDOW* input, int current, int total);
void fl_card_family_print(FLCardFamily* family, WINDOW* main, int y, int index, int total);
void fl_card_ultimate_print(FLUltimateCard* ult, WINDOW* main, int y);

// Flipped Legacy Editor - Card API