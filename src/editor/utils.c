#include "utils.h"
#include <fl_types.h>
#include <ncurses/ncurses.h>

void reinit_window(WINDOW* win) {
    wclear(win);
    box(win, 0, 0);
    wrefresh(win);
}

unsigned int menu_inline(WINDOW* win, int y, int x, char** menu_items, int menu_len, short color) {
    keypad(win, true);
    int choice;
    int index = 0;
    while (true) {
        mvwprintw(win, y, x, "                                ");
        wattron(win, COLOR_PAIR(color));
        mvwprintw(win, y, x, "%s", menu_items[index]);
        wattroff(win, COLOR_PAIR(color));
        choice = wgetch(win);
        switch (choice) {
        case KEY_UP:
            if (index != 0)
                index--;
            break;
        case KEY_DOWN:
            if (index != menu_len - 1)
                index++;
            break;
        case 10:
            return index;
            break;
        }
    }
};

WINDOW* print_info(void) {
    refresh();

    int maxColumns = getmaxx(stdscr);
    WINDOW* info = newwin(5, maxColumns, 0, 0);
    box(info, 0, 0);

    mvwprintw(info, 1, 1, "Welcome to the FL Editor");
    mvwprintw(info, 2, 1, "Version: ");

    wattron(info, COLOR_PAIR(1));
    wprintw(info, "%s", FL_EDITOR_VERSION);
    wattroff(info, COLOR_PAIR(1));

    mvwprintw(info, 3, 1, "sizeof(character): %lld", sizeof(FLCharacter));

    wrefresh(info);
    return info;
}