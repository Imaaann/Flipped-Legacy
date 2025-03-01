#pragma once
#include <fl_types.h>
#include <ncurses/ncurses.h>

// Flipped Legacy Editor - Effect API

/**
 * @brief Initializes an effect to an empty state
 *
 * @param eff effect to initialize
 */
void fl_effect_set_undefined(FLEffect* eff);

/**
 * @brief Gets human readable string of the effect struct
 *
 * @param eff effect to turn into readable string
 * @param str string to write to
 */
void fl_effect_get_semantic(FLEffect* eff, char* str);