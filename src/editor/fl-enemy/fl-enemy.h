#pragma once

#include <fl_types.h>
#include <ncurses/ncurses.h>
#include <utils.h>

// Alpha Version API
void fl_enemy_get_bias(FLEnemy* enemy, WINDOW* input);
void fl_enemy_get_input(FLEnemy* enemy, int current, int total);
void fl_enemy_print_all(WINDOW* main, FLEnemy* enemyArray, int enemyCount);

// Flipped Legacy Editor - Enemy API

/**
 * @brief Retrieves enemies from a specified file
 *
 * @param enemyArray enemy array to write to, must be at least `enemyCount` long
 * @param name name of the file to read from without the extension, usually taken from
 * `FLGame.gameName`
 * @param enemyCount number of enemies to read
 */
void fl_enemy_from_file(FLEnemy* enemyArray, char* name, int enemyCount);

/**
 * @brief Writes an enemy array into a .flge file
 *
 * @param enemyArray array of enemies to write
 * @param data game context, used to generate file name and for enemy count
 */
void fl_enemy_save_to_file(FLEnemy* enemyArray, FLGameData* data);