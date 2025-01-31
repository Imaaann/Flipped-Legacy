#include "fl-character/fl-character.h"
#include "fl-enemy/fl-enemy.h"
#include "fl-game/fl-game.h"
#include <fl_types.h>
#include <ncurses/ncurses.h>
#include <utils.h>

typedef enum { NEW_GAME, READ_GAME, EDIT_GAME, DELETE_GAME, EXIT } GameMenuOptions;

static void new_game_handler(void);

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);

    WINDOW* info = print_info();

    WINDOW* menu = newwin(10, MAX_COLUMNS / 2 - 20, 5, MAX_COLUMNS / 2 - 20);
    box(menu, 0, 0);
    wrefresh(menu);
    refresh();
    char* menuOptions[] = {"1. New Game", "2. Read Game", "3. Edit Game", "4. Delete Game",
                           "5. Exit"};
    unsigned int choice = menu_multiline(menu, 1, 1, menuOptions, 5, 2);

    switch (choice) {
    case NEW_GAME:
        wclear(menu);
        wrefresh(menu);
        delwin(menu);
        new_game_handler();
        break;
    case READ_GAME:
        break;
    case EDIT_GAME:
        break;
    case DELETE_GAME:
        break;
    case EXIT:
        break;
    }

    delwin(menu);
    delwin(info);
    getch();
    endwin();

    return 0;
}

static void new_game_handler(void) {
    FLGameData data = {0};
    fl_game_data_input(&data);

    FLCharacter characters[data.characterCount];
    for (int i = 0; i < data.characterCount; i++) {
        fl_character_get_input(&characters[i], i, data.characterCount);
    }
    fl_character_save_to_file(characters, &data);

    FLEnemy enemies[data.enemyCount];
    for (int i = 0; i < data.enemyCount; i++) {
        fl_enemy_get_input(&enemies[i], i, data.enemyCount);
    }
    fl_enemy_save_to_file(enemies, &data);
}