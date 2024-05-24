#include <ncurses/ncurses.h>
typedef void (*SChoiceFunc)();
typedef struct _SChoice {
    char* Txt;
    SChoiceFunc Func;
} SChoice;

void CreateSimpleMenu(SChoice* Choices, int N) {
    int choice;
    int highlighted = 0;

    init_pair(1,COLOR_MAGENTA,COLOR_BLACK);
    int maxX = getmaxx(stdscr);
    int maxY = getmaxy(stdscr);
    WINDOW* menuwin = newwin(N+2,96,(maxY-(N+2))/2,(maxX-96)/2);
    keypad(menuwin,true);
    box(menuwin,0,0);
    wrefresh(menuwin);
    refresh();


    while(1) {

        for (int i=0; i<N; i++) {
            if (i == highlighted) wattron(menuwin,COLOR_PAIR(1) | A_BOLD);
            mvwprintw(menuwin,i+1,1,"%d - %s",i+1,Choices[i].Txt);
            wattroff(menuwin,COLOR_PAIR(1));
            wattroff(menuwin,A_BOLD);
        }
        
        choice = wgetch(menuwin);

        switch (choice) { // selction
            case KEY_UP:
            highlighted = (highlighted - 1) % N;
            if (highlighted < 0) highlighted = N-1;
            break;

            case KEY_DOWN:
            highlighted = (highlighted + 1) % N;
            break;

            default:
            break;
        }

        if (choice == 10) { // handle enter
            break;
        }
    }

    wclear(menuwin);
    delwin(menuwin);
    Choices[highlighted].Func();
}
