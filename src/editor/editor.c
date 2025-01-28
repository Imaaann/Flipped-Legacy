#include "fl-character/fl-character.h"
#include "fl-game/fl-game.h"
#include <fl_types.h>
#include <ncurses/ncurses.h>
#include <utils.h>

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);

    WINDOW* info = print_info();

    FLGameData data;
    fl_game_data_input(&data);

    FLCharacter characters[data.characterCount];
    for (int i = 0; i < data.characterCount; i++) {
        fl_character_get_input(&characters[i], i, data.characterCount);
    }

    delwin(info);
    getch();
    endwin();

    return 0;
}