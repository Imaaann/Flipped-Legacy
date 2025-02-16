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

void fl_enemy_print(WINDOW* main, FLEnemy* enemy) {
    const char* qualities[] = {"COMMON", "UNCOMMON", "RARE", "EPIC", "LEGENDARY"};
    const char* regens[] = {"AUTO", "OFFENSIVE", "DEFENSIVE"};
    char* options[] = {"Next", "Prev", "Exit"};
    const int deckSize = enemy->base.stats.quality + 2;
    reinit_window(main);

    // MetaData
    mvwprintw(main, 1, 1, "Enemy Name: %s", enemy->base.name);
    mvwprintw(main, 2, 1, "Image: %s", enemy->base.image);
    mvwprintw(main, 3, 1, "Description: %s", enemy->base.description);

    // Stats
    mvwprintw(main, 4, 1, "Stats: ");
    mvwprintw(main, 5, 1, "Hp: %.2f       | Hp/lvl: %.2f", enemy->base.stats.hp,
              enemy->base.stats.hpg);
    mvwprintw(main, 6, 1, "Atk: %.2f      | Atk/lvl: %.2f", enemy->base.stats.atk,
              enemy->base.stats.atkg);
    mvwprintw(main, 7, 1, "Def: %.2f      | Def/lvl: %.2f", enemy->base.stats.def,
              enemy->base.stats.defg);
    mvwprintw(main, 8, 1, "Res: %.2f      | Res/lvl: %.2f", enemy->base.stats.res,
              enemy->base.stats.resg);
    mvwprintw(main, 9, 1, "Spd: %.2f      | Regen: %s", enemy->base.stats.spd,
              regens[enemy->base.stats.regen]);
    mvwprintw(main, 10, 1, "Quality: %s", qualities[enemy->base.stats.quality]);

    // Biases
    mvwprintw(main, 11, 1, "Attack Bias: %d      | Buff Bias: %d", enemy->attackBias,
              enemy->buffBias);
    mvwprintw(main, 12, 1, "Heal Bias: %d        | DeBuff Bias: %d", enemy->healBias,
              enemy->debuffBias);

    mvwprintw(main, 13, 1, "Card Show: ");
    int index = 0;
    while (true) {
        fl_card_family_print(&enemy->base.deck[index], main, 15, index + 1, deckSize);
        unsigned int choice = menu_inline(main, 13, 12, options, 3, 1);
        switch (choice) {
        case 0:
            if (index != deckSize - 1)
                index++;
            break;
        case 1:
            if (index != 0)
                index--;
            break;
        case 2:
            reinit_window(main);
            return;
            break;
        }
    }
}

void fl_enemy_print_all(WINDOW* main, FLEnemy* enemyArray, int enemyCount) {
    WINDOW* enemyPrintWin = subwin(main, MAX_ROWS - 12, MAX_COLUMNS - 2, 10, 1);
    char* buttons[] = {"Next", "Prev", "Exit"};
    int index = 0;
    while (true) {
        reinit_window(enemyPrintWin);
        fl_enemy_print(enemyPrintWin, &enemyArray[index]);
        mvwprintw(enemyPrintWin, 1, MAX_COLUMNS - 40, "Enemy Showcase:");
        unsigned int choice = menu_multiline(enemyPrintWin, 2, MAX_COLUMNS - 40, buttons, 3, 1);
        switch (choice) {
        case 0:
            if (index != enemyCount - 1)
                index++;
            break;
        case 1:
            if (index != 0)
                index--;
            break;
        case 2:
            wclear(enemyPrintWin);
            delwin(enemyPrintWin);
            return;
            break;
        }
    }
}

/**
 * @brief saves the enemy array to a .flge file.
 * file is saved in the following way
 * enemyArray[]
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

    for (int i = 0; i < data->enemyCount; i++) {
        fwrite(&enemyArray[i], sizeof(FLEnemy), 1, enemyFile);
    }

    fclose(enemyFile);
}

void fl_enemy_from_file(FLEnemy* enemyArray, char* name, int characterCount) {
    char* fileName = (char*)malloc(strlen(name) + 8);
    sprintf(fileName, "%s.flge", name);

    FILE* characterFile = fopen(fileName, "rb");
    free(fileName);

    if (characterFile == NULL)
        return;

    int index = 0;
    while (fread(&enemyArray[index], sizeof(FLCharacter), 1, characterFile) &&
           index < characterCount) {
        index++;
    }

    fclose(characterFile);
}