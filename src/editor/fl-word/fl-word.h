#pragma once
#include <fl_types.h>
#include <ncurses/ncurses.h>

void fl_card_get_word_input(FLWord* word, WINDOW* input, int word_num);
void fl_word_get_semantic(FLWord* word, char* str);