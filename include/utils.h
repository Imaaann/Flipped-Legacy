#pragma once
#include <ncurses/ncurses.h>

#define FL_EDITOR_VERSION "beta-0.4.2"
#define MAX_COLUMNS getmaxx(stdscr)
#define MAX_ROWS getmaxy(stdscr)
#define COLUMN_OFFSET 10

void reinit_window(WINDOW* win);
unsigned int menu_inline(WINDOW* win, int y, int x, char** menu_items, int menu_len, short color);
unsigned int menu_multiline(WINDOW* win, int y, int x, char** menu_items, int menu_len,
                            short color);
WINDOW* print_info(void);