#include "fl-character/fl-character.h"
#include "fl-enemy/fl-enemy.h"
#include "fl-game/fl-game.h"
#include <fl_types.h>
#include <ncurses/ncurses.h>
#include <stdlib.h>
#include <utils.h>

typedef enum { NEW_GAME, READ_GAME, EDIT_GAME, DELETE_GAME, EXIT } GameMenuOptions;

static void new_game_handler(void);
static void read_game_handler(void);

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

    wclear(menu);
    wrefresh(menu);
    delwin(menu);

    switch (choice) {
    case NEW_GAME:
        new_game_handler();
        break;
    case READ_GAME:
        read_game_handler();
        break;
    case EDIT_GAME:
        break;
    case DELETE_GAME:
        break;
    case EXIT:
        break;
    }

    delwin(info);
    getch();
    endwin();

    return 0;
}

static void new_game_handler(void) {
    FLGameData data = {0};
    fl_game_data_input(&data);

    fl_game_save_to_file(&data);

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

static void read_game_handler(void) {
    char buffer[64] = {'\0'};
    char* menuOptions[] = {"Show Characters", "Show Enemies", "Show levels", "Exit"};

    WINDOW* main = newwin(MAX_ROWS - 6, MAX_COLUMNS, 5, 0);
    reinit_window(main);
    mvwprintw(main, 1, 1, "Game Name: ");
    mvwscanw(main, 1, 12, "%[^\n]s", buffer);

    FLLoadedGame game = fl_game_load(buffer);

    fl_game_print(game.data, main);

    unsigned int choice;
    while (true) {
        choice = menu_multiline(main, 1, MAX_COLUMNS - 33, menuOptions, 4, 5);
        switch (choice) {
        case 0:
            fl_character_print_all(main, game.characterArray, game.data->characterCount);
            break;
        case 1:
            fl_enemy_print_all(main, game.enemyArray, game.data->enemyCount);
            break;
        case 2:
            break;
        case 3:
            free(game.data);
            free(game.characterArray);
            free(game.enemyArray);
            delwin(main);
            return;
            break;
        }
    }
}

static void edit_game_handler(void) {
    char buffer[64] = {0};
    char* menuOptions[] = {"Edit characters", "Edit enemies", "Edit Levels", "Exit"};

    WINDOW* main = newwin(MAX_ROWS - 6, MAX_COLUMNS, 5, 0);
    reinit_window(main);
    mvwprintw(main, 1, 1, "Game Name: ");
    mvwscanw(main, 1, 12, "%[^\n]s", buffer);
}