#pragma once
#include <fl_types.h>
#include <ncurses/ncurses.h>

void fl_character_get_meta_data_input(FLCharacter* character, WINDOW* input);
void fl_character_get_stats_input(FLCharacter* character, WINDOW* input);
void fl_character_get_input(FLCharacter* data, int current, int total);
void fl_character_save_to_file(FLCharacter* characterArray, FLGameData* data);
void fl_character_from_file(FLCharacter* characterArray, char* name, int characterCount);
void fl_character_print_all(WINDOW* main, FLCharacter* characterArray, int characterCount);
void fl_character_print(WINDOW* main, FLCharacter* character);