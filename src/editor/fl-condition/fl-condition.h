#pragma once
#include <fl_types.h>
#include <ncurses/ncurses.h>

// Flipped Legacy Editor - Condition API
/**
 * @brief Gets a human readable string of the condition struct
 *
 * @param condition condition to turn into a readable string
 * @param str string to write to
 */
void fl_condition_get_semantic(FLCondition* condition, char* str);
