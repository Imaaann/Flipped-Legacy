#include "fl-card.h"
#include "fl-word/fl-word.h"
#include <utils.h>

void fl_card_get_input(FLCard* card, WINDOW* input, int deck_index) {

    char* className = (deck_index == NORMAL) ? "Normal Attack" : "Incantation";
    mvwprintw(input, 5, 1, "                                ");
    mvwprintw(input, 5, 1, "Card Class: %s", className);
    wrefresh(input);

    card->cardClass = (deck_index == NORMAL) ? NORMAL : INCANTATION;

    WINDOW* wordInput = subwin(input, 15, MAX_COLUMNS - 2, 14, 1);
    for (int i = 0; i < 2; i++) {
        whline(wordInput, 0, MAX_COLUMNS - 2);
        fl_card_get_word_input(&card->words[i], wordInput, i + 1);
        wclear(wordInput);
        wrefresh(wordInput);
    }
    delwin(wordInput);
    wrefresh(input);
}

void fl_card_get_ultimate_input(FLUltimateCard* ultCard, WINDOW* input) {
    mvwprintw(input, 1, 1, "Card Class: Ultimate");
    mvwprintw(input, 2, 1, "Energy Cost: ");
    wrefresh(input);
    mvwscanw(input, 2, 14, "%d", &ultCard->energyCost);
    ultCard->cardClass = ULTIMATE;

    WINDOW* wordInput = subwin(input, 15, MAX_COLUMNS - 2, 14, 1);
    for (int i = 0; i < 3; i++) {
        whline(wordInput, 0, MAX_COLUMNS - 2);
        fl_card_get_word_input(&ultCard->words[i], wordInput, i + 1);
        wclear(wordInput);
        wrefresh(wordInput);
    }
    delwin(input);
    wrefresh(input);
}

void fl_card_family_get_input(FLCardFamily* family, WINDOW* input, int current, int total) {
    for (int i = 0; i < 3; i++) {
        mvwprintw(input, 3, 1, "Card Family: %d/%d", current + 1, total);
        mvwprintw(input, 4, 1, "Card Stars: %d/3", i + 1);
        fl_card_get_input(&family->members[i], input, current);
    }
}

void fl_card_family_print(FLCardFamily* family, WINDOW* main, int y, int index, int total) {
    const char* classes[] = {"NORMAL", "INCANTATION"};
    const char* stars[] = {"*", "**", "***"};
    const FLCardClass classIndex = family->members[0].cardClass;
    char buffer[512] = {'\0'};
    mvwprintw(main, y, 1, "                                  ");
    mvwprintw(main, y, 1, "Card: %d/%d --- Class: %s", index, total, classes[classIndex]);
    for (int i = 0; i < 3; i++) {
        mvwprintw(main, y + 1 + i * 3, 1, "(%s) Star: ", stars[i]);
        fl_word_get_semantic(&family->members[i].words[0], buffer);
        mvwprintw(main, y + 2 + i * 3, 1,
                  "                                                                    ");
        mvwprintw(main, y + 2 + i * 3, 1, "1. %s", buffer);
        fl_word_get_semantic(&family->members[i].words[1], buffer);
        mvwprintw(main, y + 3 + i * 3, 1,
                  "                                                                    ");
        mvwprintw(main, y + 3 + i * 3, 1, "2. %s", buffer);
    }
}

void fl_card_ultimate_print(FLUltimateCard* ult, WINDOW* main, int y) {
    char buffer[512] = {'\0'};
    mvwprintw(main, y, 1, "ULTIMATE CARD                     ");
    mvwprintw(main, y + 1, 1, "Energy Cost: %d", ult->energyCost);

    mvwprintw(main, y + 2, 1,
              "                                                                    ");
    fl_word_get_semantic(&ult->words[0], buffer);
    mvwprintw(main, y + 2, 1, "1. %s", buffer);

    mvwprintw(main, y + 3, 1,
              "                                                                    ");
    fl_word_get_semantic(&ult->words[1], buffer);
    mvwprintw(main, y + 3, 1, "2. %s", buffer);

    mvwprintw(main, y + 4, 1,
              "                                                                    ");
    fl_word_get_semantic(&ult->words[2], buffer);
    mvwprintw(main, y + 4, 1, "3. %s", buffer);

    for (int i = 5; i < 15; i++) {
        mvwprintw(main, y + i, 1,
                  "                                                                    ");
    }
}