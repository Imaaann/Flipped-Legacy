#pragma once
#include <fl_types.h>
#include <ncurses/ncurses.h>

void fl_character_get_meta_data_input(FLCharacter* character, WINDOW* input, int current,
                                      int total);
void fl_character_get_stats_input(FLCharacter* character, WINDOW* input, int current, int total);
void fl_character_get_input(FLCharacter* data, int current, int total);
void fl_character_save_to_file(FLCharacter* character, FLGameData* data);