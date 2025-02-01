#include "fl-character.h"
#include "fl-card/fl-card.h"
#include <stdlib.h>
#include <string.h>
#include <utils.h>

void fl_character_get_meta_data_input(FLCharacter* character, WINDOW* input) {
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

void fl_character_get_stats_input(FLCharacter* character, WINDOW* input) {
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

    mvwprintw(input, 1, 1, "Character Number: %d/%d", current, total);
    fl_character_get_meta_data_input(data, input);
    reinit_window(input);

    mvwprintw(input, 1, 1, "Character Number: %d/%d", current, total);
    fl_character_get_stats_input(data, input);
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

void fl_character_print(WINDOW* main, FLCharacter* character) {
    const char* qualities[] = {"COMMON", "UNCOMMON", "RARE", "EPIC", "LEGENDARY"};
    const char* regens[] = {"AUTO", "OFFENSIVE", "DEFENSIVE"};
    char* options[] = {"Next", "Prev", "Exit"};
    const int deckSize = character->stats.quality + 2;
    reinit_window(main);

    // MetaData
    mvwprintw(main, 1, 1, "Character Name: %s", character->name);
    mvwprintw(main, 2, 1, "Image: %s", character->image);
    mvwprintw(main, 3, 1, "Description: %s", character->description);

    // Stats
    mvwprintw(main, 4, 1, "Stats: ");
    mvwprintw(main, 5, 1, "Hp: %.2f       | Hp/lvl: %.2f", character->stats.hp,
              character->stats.hpg);
    mvwprintw(main, 6, 1, "Atk: %.2f      | Atk/lvl: %.2f", character->stats.atk,
              character->stats.atkg);
    mvwprintw(main, 7, 1, "Def: %.2f      | Def/lvl: %.2f", character->stats.def,
              character->stats.defg);
    mvwprintw(main, 8, 1, "Res: %.2f      | Res/lvl: %.2f", character->stats.res,
              character->stats.resg);
    mvwprintw(main, 9, 1, "Spd: %.2f      | Regen: %s", character->stats.spd,
              regens[character->stats.regen]);
    mvwprintw(main, 10, 1, "Quality: %s", qualities[character->stats.quality]);
    mvwprintw(main, 11, 1, "Card Show: ");

    int index = 0;
    while (true) {
        fl_card_family_print(&character->deck[index], main, index + 1, deckSize);
        unsigned int choice = menu_inline(main, 11, 12, options, 3, 1);
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

void fl_character_print_all(WINDOW* main, FLCharacter* characterArray, int characterCount) {
    WINDOW* characterPrintWin = subwin(main, MAX_ROWS - 12, MAX_COLUMNS - 2, 10, 1);
    char* buttons[] = {"Next", "Prev", "Exit"};
    int index = 0;
    while (true) {
        reinit_window(characterPrintWin);
        fl_character_print(characterPrintWin, &characterArray[index]);
        mvwprintw(characterPrintWin, 1, MAX_COLUMNS - 40, "Character Showcase:");
        unsigned int choice = menu_multiline(characterPrintWin, 2, MAX_COLUMNS - 40, buttons, 3, 1);
        switch (choice) {
        case 0:
            if (index != characterCount - 1)
                index++;
            break;
        case 1:
            if (index != 0)
                index--;
            break;
        case 2:
            wclear(characterPrintWin);
            delwin(characterPrintWin);
            return;
            break;
        }
    }
}

/**
 * @brief saves the character array to a .flgc file.
 * file is saved in the following way
 * characterArray[]
 *
 * @param characterArray
 * Array of characters to save
 * @param data
 * FLGame context, used to generate name of the file from game name
 */
void fl_character_save_to_file(FLCharacter* characterArray, FLGameData* data) {
    char* fileName = (char*)malloc(strlen(data->gameName) + 8);
    sprintf(fileName, "%s.flgc", data->gameName);

    FILE* characterFile = fopen(fileName, "wb");
    free(fileName);

    if (characterFile == NULL)
        return;

    for (int i = 0; i < data->characterCount; i++) {
        fwrite(&characterArray[i], sizeof(FLCharacter), 1, characterFile);
    }
    fclose(characterFile);
}

void fl_character_from_file(FLCharacter* characterArray, char* name, int characterCount) {
    char* fileName = (char*)malloc(strlen(name) + 8);
    sprintf(fileName, "%s.flgc", name);

    FILE* characterFile = fopen(fileName, "rb");
    free(fileName);

    if (characterFile == NULL)
        return;

    int index = 0;
    while (fread(&characterArray[index], sizeof(FLCharacter), 1, characterFile) &&
           index < characterCount) {
        index++;
    }

    fclose(characterFile);
}