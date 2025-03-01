#pragma once
#include <fl_types.h>
#include <ncurses/ncurses.h>

// Flipped Legacy Editor - Character API

/**
 * @brief saves the character array to a .flgc file.
 * file is saved in the following way
 * characterArray[]
 *
 * @param characterArray
 * Array of characters to save
 * @param data
 * FLGame context, used to generate name of the file from game name
 *
 */
void fl_character_save_to_file(FLCharacter* characterArray, FLGameData* data);

/**
 * @brief Retrieves characters from a specified file
 *
 * @param characterArray Array of characters to write to, must be at least `characterCount` long
 * @param name Name of the file to read from without the extension, usually taken from
 * `FLGame.gameName`
 * @param characterCount The amount of characters to read
 */
void fl_character_from_file(FLCharacter* characterArray, char* name, int characterCount);