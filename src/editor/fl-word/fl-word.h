#pragma once
#include <fl_types.h>
#include <ncurses/ncurses.h>

// Flipped Legacy Editor - Full word API

/**
 * @brief gets a human readable string from the word struct
 *
 * @param word word to turn into readable string
 * @param str string to write to
 */
void fl_word_get_semantic(FLWord* word, char* str);