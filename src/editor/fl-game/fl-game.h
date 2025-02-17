#pragma once
#include <fl_types.h>
#include <ncurses/ncurses.h>

// Alpha Version API
void fl_game_data_input(FLGameData* data);
void fl_game_print(FLGameData* data, WINDOW* main);

// Flipped Legacy Editor - Game Metadata API

/**
 * @brief Writes the game metadata to a .flg file
 *
 * @param data data to write
 */
void fl_game_save_to_file(FLGameData* data);

/**
 * @brief reads the game metadata from a specified file
 *
 * @param name name of the file to read without the extenion
 * @param data struct to write to
 */
void fl_game_from_file(char* name, FLGameData* data);