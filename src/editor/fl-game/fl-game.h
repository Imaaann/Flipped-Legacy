#pragma once
#include <fl_types.h>
#include <ncurses/ncurses.h>

void fl_game_data_input(FLGameData* data);
void fl_game_save_to_file(FLGameData* data);
void fl_game_from_file(char* name, FLGameData* data, WINDOW* input);
void fl_game_print(FLGameData* data, WINDOW* main);