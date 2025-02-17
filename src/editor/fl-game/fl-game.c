#include "fl-game.h"
#include <stdlib.h>
#include <string.h>
#include <utils.h>

void fl_game_data_input(FLGameData* data) {
    refresh();

    int maxColumns = getmaxx(stdscr);
    WINDOW* input = newwin(5, maxColumns, 5, 0);
    box(input, 0, 0);

    mvwprintw(input, 1, 1, "Game Name: ");
    mvwprintw(input, 2, 1, "Character Count: ");
    mvwprintw(input, 3, 1, "Enemy Count: ");

    char Buffer[256] = {'\0'};
    mvwscanw(input, 1, 12, "%[^\n]s", Buffer);
    if (strlen(Buffer) > 63)
        exit(1);
    strncpy(data->gameName, Buffer, strlen(Buffer));

    mvwscanw(input, 2, 18, "%d", &data->characterCount);
    mvwscanw(input, 3, 14, "%d", &data->enemyCount);
    strcpy(data->editorVersion, FL_EDITOR_VERSION);

    wrefresh(input);
    delwin(input);
}

void fl_game_from_file(char* name, FLGameData* data) {
    char* fileName = (char*)malloc(strlen(name) + 8);
    sprintf(fileName, "./%s.flg", name);

    FILE* dataFile = fopen(fileName, "r");
    free(fileName);

    if (dataFile == NULL) {
        return;
    }

    fscanf(dataFile, "%[^\n]s", data->editorVersion);
    (void)fgetc(dataFile);

    fscanf(dataFile, "%[^\n]s", data->gameName);
    (void)fgetc(dataFile);

    fscanf(dataFile, "%d", &data->characterCount);
    (void)fgetc(dataFile);

    fscanf(dataFile, "%d", &data->enemyCount);
    (void)fgetc(dataFile);

    fclose(dataFile);
}

void fl_game_print(FLGameData* data, WINDOW* main) {
    mvwprintw(main, 1, 1, "Game Name: %s", data->gameName);
    mvwprintw(main, 2, 1, "Character Count: %d     | Enemy Count: %d", data->characterCount,
              data->enemyCount);
    mvwprintw(main, 3, 1, "Made with: %s", data->editorVersion);
    wgetch(main);
}

/**
 * @brief Saves game metaData to a textual file with .flg extensio,
 *
 * @param data
 * metaData to save
 */
void fl_game_save_to_file(FLGameData* data) {
    char* fileName = (char*)malloc(strlen(data->gameName) + 8);
    sprintf(fileName, "%s.flg", data->gameName);
    FILE* dataFile = fopen(fileName, "w");
    fprintf(dataFile, "%s\n%s\n%d\n%d\n", data->editorVersion, data->gameName, data->characterCount,
            data->enemyCount);

    free(fileName);
}
