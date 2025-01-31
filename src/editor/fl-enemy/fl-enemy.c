#include "fl-enemy.h"
#include "fl-card/fl-card.h"
#include "fl-character/fl-character.h"
#include <stdlib.h>
#include <string.h>

void fl_enemy_get_bias(FLEnemy* enemy, WINDOW* input) {
    mvwprintw(input, 2, 1, "Step4: Card biases");
    mvwprintw(input, 3, 1, "Attack Bias: ");
    mvwprintw(input, 4, 1, "Buff Bias: ");
    mvwprintw(input, 5, 1, "Debuff Bias: ");
    mvwprintw(input, 6, 1, "Heal Bias: ");

    mvwscanw(input, 3, 14, "%d", &enemy->attackBias);
    mvwscanw(input, 4, 12, "%d", &enemy->buffBias);
    mvwscanw(input, 5, 14, "%d", &enemy->debuffBias);
    mvwscanw(input, 6, 12, "%d", &enemy->healBias);

    wgetch(input);
}

void fl_enemy_get_input(FLEnemy* enemy, int current, int total) {
    refresh();
    WINDOW* input = newwin(25, MAX_COLUMNS, 5, 0);
    box(input, 0, 0);

    mvwprintw(input, 1, 1, "Enemy Number: %d/%d", current, total);
    fl_character_get_meta_data_input(&enemy->base, input);
    reinit_window(input);

    mvwprintw(input, 1, 1, "Enemy Number: %d/%d", current, total);
    fl_character_get_stats_input(&enemy->base, input);
    reinit_window(input);

    for (unsigned int i = 0; i < 2 + enemy->base.stats.quality; i++) {
        mvwprintw(input, 1, 1, "Enemy Number: %d/%d", current + 1, total);
        mvwprintw(input, 2, 1, "Step3: Card creation");
        fl_card_family_get_input(&enemy->base.deck[i], input, i, 2 + enemy->base.stats.quality);
        reinit_window(input);
    }
    fl_card_get_ultimate_input(&enemy->base.ultimate, input);
    reinit_window(input);

    mvwprintw(input, 1, 1, "Enemy Number: %d/%d", current, total);
    fl_enemy_get_bias(enemy, input);
    reinit_window(input);

    delwin(input);
}

/**
 * @brief saves the enemy array to a .flge file.
 * file is saved in the following way
 * editorVersion, enemyArray[]
 *
 * @param enemyArray
 * Array of enemies to save
 * @param data
 * FLGame context, used to generate name of the file from game name
 */
void fl_enemy_save_to_file(FLEnemy* enemyArray, FLGameData* data) {
    char* fileName = (char*)malloc(strlen(data->gameName) + 8);
    sprintf(fileName, "%s.flge", data->gameName);

    FILE* enemyFile = fopen(fileName, "wb");
    free(fileName);

    fwrite(data->editorVersion, 16 * sizeof(char), 1, enemyFile);
    for (int i = 0; i < data->enemyCount; i++) {
        fwrite(&enemyArray[i], sizeof(FLEnemy), 1, enemyFile);
    }

    fclose(enemyFile);
}