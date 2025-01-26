#include <fl_types.h>
#include <ncurses/ncurses.h>
#include <stdlib.h>
#include <string.h>

#define FL_EDITOR_VERSION "beta-1.0"
#define MAX_COLUMNS getmaxx(stdscr)

void reinit_window(WINDOW* win) {
    wclear(win);
    box(win, 0, 0);
    wrefresh(win);
}

WINDOW* print_info(void) {
    refresh();

    int maxColumns = getmaxx(stdscr);
    WINDOW* info = newwin(5, maxColumns, 0, 0);
    box(info, 0, 0);

    mvwprintw(info, 1, 1, "Welcome to the FL Editor");
    mvwprintw(info, 2, 1, "Version: ");
    mvwprintw(info, 3, 1, "sizeof(character): %lld", sizeof(FLCharacter));

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

void character_get_meta_data(FLCharacter* character, WINDOW* input, int current, int total) {
    mvwprintw(input, 1, 1, "Character Number: %d/%d", current, total);
    mvwprintw(input, 2, 1, "Step1: MetaData");
    mvwprintw(input, 3, 1, "Name: ");
    mvwprintw(input, 4, 1, "Image Path (absolute): ");
    mvwprintw(input, 5, 1, "Description: ");
    wrefresh(input);

    char buffer[256];
    mvwscanw(input, 3, 7, "%[^\n]s", buffer);
    if (strlen(buffer) >= 128)
        exit(1);
    strcpy(character->name, buffer);

    mvwscanw(input, 4, 24, "%[^\n]s", buffer);
    if (strlen(buffer) >= 128)
        exit(1);
    strcpy(character->image, buffer);

    mvwscanw(input, 5, 14, "%[^\n]s", buffer);
    if (strlen(buffer) >= 256)
        exit(1);
    strcpy(character->description, buffer);

    wgetch(input);
}

FLCharacter character_get_info(int current, int total) {
    refresh();
    FLCharacter data;
    WINDOW* input = newwin(10, MAX_COLUMNS, 5, 0);
    box(input, 0, 0);

    character_get_meta_data(&data, input, current, total);
    reinit_window(input);

    return data;
}

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    WINDOW* info = print_info();

    FLGameData data = get_basic_info();
    print_basic_info(data);

    FLCharacter characters[data.characterCount];
    for (int i = 0; i < data.characterCount; i++) {
        characters[i] = character_get_info(i, data.characterCount);
    }

    delwin(info);
    getch();
    endwin();

    return 0;
}
