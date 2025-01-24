#include <ncurses/ncurses.h>
#include <stdlib.h>

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    printw("Test");
    attroff(COLOR_PAIR(1));

    refresh();
    getch();
    endwin();

    return 0;
}