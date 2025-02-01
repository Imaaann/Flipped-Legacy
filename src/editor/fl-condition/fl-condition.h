#pragma once
#include <fl_types.h>
#include <ncurses/ncurses.h>

void fl_condition_input(FLCondition* condition, WINDOW* input);
void fl_condition_get_semantic(FLCondition* condition, char* str);
