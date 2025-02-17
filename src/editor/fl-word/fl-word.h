#pragma once
#include <fl_types.h>
#include <ncurses/ncurses.h>

// Alpha Version API
void fl_card_get_word_input(FLWord* word, WINDOW* input, int word_num);

// Flipped Legacy Editor - Full word API

/**
 * @brief gets a human readable string from the word struct
 *
 * @param word word to turn into readable string
 * @param str string to write to
 */
void fl_word_get_semantic(FLWord* word, char* str);