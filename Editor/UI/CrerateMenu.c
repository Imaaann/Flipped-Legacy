#include <ncurses/ncurses.h>

int CreateSimpleMenu(WINDOW* menuwin,const char** Choices, int N, int x, int y) {
    int choice;
    int highlighted = 0;
    init_pair(1,COLOR_MAGENTA,COLOR_BLACK);

    while(1) {

        
        wattron(menuwin,A_BOLD);
        mvwprintw(menuwin,y,x,"                       ");
        mvwprintw(menuwin,y,x,"%s",Choices[highlighted]);
        wattroff(menuwin,A_BOLD);
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
    return highlighted;
}


