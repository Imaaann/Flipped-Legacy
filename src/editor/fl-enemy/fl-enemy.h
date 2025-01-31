#pragma once

#include <fl_types.h>
#include <ncurses/ncurses.h>
#include <utils.h>

void fl_enemy_get_bias(FLEnemy* enemy, WINDOW* input);
void fl_enemy_get_input(FLEnemy* enemy, int current, int total);
void fl_enemy_save_to_file(FLEnemy* enemyArray, FLGameData* data);