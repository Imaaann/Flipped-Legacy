#include <ncurses/ncurses.h>
#include "EditorTypes.h"

// UI fucntions
#include "UI/CrerateMenu.c"
#include "UI/Logo.c"

//handlers
#include "Handlers/FL_Handlers.c"

int main() {
    initscr();
    cbreak();
    start_color();

    int maxX,maxY;
    getmaxyx(stdscr,maxY,maxX);
    box(stdscr,0,0);

    WINDOW* LogoWin = newwin(9,96,1,(maxX-96)/2);
    box(LogoWin,0,0);
    refresh();
    wrefresh(LogoWin);

    PrintLogo(LogoWin);
    refresh();

    NewGame();

    








    getch();
    endwin();
    return 0;
}

