#include "fl-character.h"
#include "fl-card/fl-card.h"
#include <stdlib.h>
#include <string.h>
#include <utils.h>

void fl_character_get_meta_data_input(FLCharacter* character, WINDOW* input, int current,
                                      int total) {
    mvwprintw(input, 1, 1, "Character Number: %d/%d", current, total);
    mvwprintw(input, 2, 1, "Step1: MetaData");
    mvwprintw(input, 3, 1, "Name: ");
    mvwprintw(input, 4, 1, "Image Path (absolute): ");
    mvwprintw(input, 5, 1, "Description: ");
    wrefresh(input);

    char buffer[256];
    mvwscanw(input, 3, 7, "%[^\n]s", buffer);
    if (strlen(buffer) >= 128)
        exit(1);
    strcpy(character->name, buffer);

    mvwscanw(input, 4, 24, "%[^\n]s", buffer);
    if (strlen(buffer) >= 128)
        exit(1);
    strcpy(character->image, buffer);

    mvwscanw(input, 5, 14, "%[^\n]s", buffer);
    if (strlen(buffer) >= 256)
        exit(1);
    strcpy(character->description, buffer);

    wgetch(input);
}

void fl_character_get_stats_input(FLCharacter* character, WINDOW* input, int current, int total) {
    mvwprintw(input, 1, 1, "Character Number: %d/%d", current, total);
    mvwprintw(input, 2, 1, "Step2: Stats");

    mvwprintw(input, 3, 1, "HP: ");
    mvwprintw(input, 3, 6 + COLUMN_OFFSET, "HP/lvl: ");

    mvwprintw(input, 4, 1, "ATK: ");
    mvwprintw(input, 4, 6 + COLUMN_OFFSET, "ATK/lvl: ");

    mvwprintw(input, 5, 1, "DEF: ");
    mvwprintw(input, 5, 6 + COLUMN_OFFSET, "DEF/lvl: ");

    mvwprintw(input, 6, 1, "RES: ");
    mvwprintw(input, 6, 6 + COLUMN_OFFSET, "RES/lvl: ");

    mvwprintw(input, 7, 1, "SPD: ");
    mvwprintw(input, 7, 6 + COLUMN_OFFSET, "Quality: ");

    mvwprintw(input, 8, 1, "Regen: ");

    mvwscanw(input, 3, 5, "%lf", &character->stats.hp);
    mvwscanw(input, 3, 14 + COLUMN_OFFSET, "%lf", &character->stats.hpg);
    mvwscanw(input, 4, 6, "%lf", &character->stats.atk);
    mvwscanw(input, 4, 15 + COLUMN_OFFSET, "%lf", &character->stats.atkg);
    mvwscanw(input, 5, 6, "%lf", &character->stats.def);
    mvwscanw(input, 5, 15 + COLUMN_OFFSET, "%lf", &character->stats.defg);
    mvwscanw(input, 6, 6, "%lf", &character->stats.res);
    mvwscanw(input, 6, 15 + COLUMN_OFFSET, "%lf", &character->stats.resg);
    mvwscanw(input, 7, 6, "%lf", &character->stats.spd);

    char* quality_list[] = {"Common", "Uncommon", "Rare", "Epic", "Legendary"};
    character->stats.quality = menu_inline(input, 7, 15 + COLUMN_OFFSET, quality_list, 5, 5);

    char* regen_list[] = {"AUTO", "OFFENSIVE", "DEFENSIVE"};
    character->stats.regen = menu_inline(input, 8, 8, regen_list, 3, 1);
    wgetch(input);
}

void fl_character_get_input(FLCharacter* data, int current, int total) {
    refresh();
    WINDOW* input = newwin(25, MAX_COLUMNS, 5, 0);
    box(input, 0, 0);

    fl_character_get_meta_data_input(data, input, current, total);
    reinit_window(input);

    fl_character_get_stats_input(data, input, current, total);
    reinit_window(input);

    for (unsigned int i = 0; i < 2 + data->stats.quality; i++) {
        mvwprintw(input, 1, 1, "Character Number: %d/%d", current + 1, total);
        mvwprintw(input, 2, 1, "Step3: Card creation");
        fl_card_family_get_input(&data->deck[i], input, i, 2 + data->stats.quality);
        reinit_window(input);
    }
    fl_card_get_ultimate_input(&data->ultimate, input);
    reinit_window(input);

    delwin(input);
}

/**
 * @brief saves the character array to a .flgc file.
 * file is saved in the following way
 * editorVersion, characterArray[]
 *
 * @param characterArray
 * Array of characters to save
 * @param data
 * FLGame context, used to generate name of the file from game name
 */
void fl_character_save_to_file(FLCharacter* characterArray, FLGameData* data) {
    char* fileName = (char*)malloc(strlen(data->gameName) + 8);
    sprintf(fileName, "%s.flgc", data->gameName);

    FILE* character_file = fopen(fileName, "wb");
    free(fileName);

    if (character_file == NULL)
        return;

    fwrite(data->editorVersion, 16 * sizeof(char), 1, character_file);
    for (int i = 0; i < data->characterCount; i++) {
        fwrite(&characterArray[i], sizeof(FLCharacter), 1, character_file);
    }
    fclose(character_file);
}