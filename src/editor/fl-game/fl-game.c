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