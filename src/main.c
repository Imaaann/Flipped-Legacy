#include <fl_types.h>
#include <ncurses/ncurses.h>
#include <stdlib.h>
#include <string.h>

#define FL_EDITOR_VERSION "beta-1.0"

WINDOW* print_info(void) {
    refresh();

    int maxColumns = getmaxx(stdscr);
    WINDOW* info = newwin(4, maxColumns, 0, 0);
    box(info, 0, 0);

    mvwprintw(info, 1, 1, "Welcome to the FL Editor");
    mvwprintw(info, 2, 1, "Version: ");

    wattron(info, COLOR_PAIR(1));
    wprintw(info, "%s", FL_EDITOR_VERSION);
    wattroff(info, COLOR_PAIR(1));
    wrefresh(info);
    return info;
}

FLGameData get_basic_info(void) {
    refresh();

    FLGameData data;

    int maxColumns = getmaxx(stdscr);
    WINDOW* input = newwin(5, maxColumns, 5, 0);
    box(input, 0, 0);

    mvwprintw(input, 1, 1, "Game Name: ");
    mvwprintw(input, 2, 1, "Character Count: ");
    mvwprintw(input, 3, 1, "Enemy Count: ");

    char Buffer[256];
    mvwscanw(input, 1, 12, "%[^\n]s", Buffer);
    if (strlen(Buffer) > 63)
        exit(1);
    strncpy(data.gameName, Buffer, strlen(Buffer));

    mvwscanw(input, 2, 18, "%d", &data.characterCount);
    mvwscanw(input, 3, 14, "%d", &data.enemyCount);
    wrefresh(input);
    delwin(input);
    return data;
}

FLGameData print_basic_info(FLGameData data) {
    refresh();

    int maxColumns = getmaxx(stdscr);
    WINDOW* input = newwin(5, maxColumns, 5, 0);
    box(input, 0, 0);

    wattron(input, COLOR_PAIR(1));
    mvwprintw(input, 1, 1, "Game Name: %s", data.gameName);
    mvwprintw(input, 2, 1, "Character Count: %d", data.characterCount);
    mvwprintw(input, 3, 1, "Enemy Count: %d", data.enemyCount);
    wattroff(input, COLOR_PAIR(1));
    wrefresh(input);

    delwin(input);
    return data;
}

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    WINDOW* info = print_info();

    FLGameData data = get_basic_info();
    print_basic_info(data);

    for (int i = 0; i < data.characterCount; i++) {
    }

    delwin(info);
    getch();
    endwin();

    return 0;
}
