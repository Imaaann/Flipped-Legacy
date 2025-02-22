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
 *
 * @exception gives back a data struct with character & enemy count = -1 on file not found exception
 */
void fl_game_from_file(char* name, FLGameData* data);

/**
 * @brief loads an entire fl game instance from files
 *
 * @param name name of the game to load
 * @return FLLoadedGame struct containing the game metadata, character array and enemy Array.
 * Ownership of the pointers is left to the caller and must be free'd accordingly
 */
FLLoadedGame fl_game_load(char* name);