#pragma once
#include <fl_types.h>
#include <ncurses/ncurses.h>

void fl_effect_set_undefined(FLEffect* eff);
void fl_effect_get_info(FLEffect* eff, WINDOW* input, int y, int x);
void fl_effect_get_semantic(FLEffect* eff, char* str);