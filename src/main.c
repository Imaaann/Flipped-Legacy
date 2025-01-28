#include <fl_types.h>
#include <ncurses/ncurses.h>
#include <stdlib.h>
#include <string.h>

#define FL_EDITOR_VERSION "beta-0.1.0"
#define MAX_COLUMNS getmaxx(stdscr)
#define COLUMN_OFFSET 10

void reinit_window(WINDOW* win) {
    wclear(win);
    box(win, 0, 0);
    wrefresh(win);
}

unsigned int menu_inline(WINDOW* win, int y, int x, char** menu_items, int menu_len) {
    keypad(win, true);
    int choice;
    int index = 0;
    while (true) {
        mvwprintw(win, y, x, "                                ");
        mvwprintw(win, y, x, "%s", menu_items[index]);
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

void fl_card_get_word_condition(FLWord* word, WINDOW* input) {
    mvwprintw(input, 1, 0, "Condition: ");
    char* conditionOptions[] = {"NONE",
                                "UNDER HP",
                                "ABOVE HP",
                                "ALLY UNDER HP",
                                "ALLY ABOVE HP",
                                "ENEMY UNDER HP",
                                "ENEMY ABOVE HP",
                                "NUMBER ALLY UNDER_HP",
                                "NUMBER ALLY ABOVE_HP",
                                "NUMBER ENEMY UNDER_HP",
                                "NUMBER ENEMY ABOVE_HP",
                                "NUMBER ALLY ALIVE",
                                "NUMBER ENEMY ALIVE",
                                "IS BUFFED",
                                "IS DEBUFFED",
                                "TARGET IS BUFFED",
                                "TARGERT IS DEBUFFED",
                                "DAMAGE",
                                "DAMAGE UNDER HP",
                                "DAMAGE ABOVE HP",
                                "DAMAGE NUMBER TURNS",
                                "SP COST"};
    word->condition.type = menu_inline(input, 1, 12, conditionOptions, 22);

    switch (word->condition.type) {

    case NONE:
    case DAMAGE:
        word->condition.coeff1 = -1;
        word->condition.coeff2 = -1;
        word->condition.effect = UNDEFINED_EFFECT;
        break;

    case UNDER_HP:
    case ABOVE_HP:
    case ALLY_ABOVE_HP:
    case ALLY_UNDER_HP:
    case ENEMY_ABOVE_HP:
    case ENEMY_UNDER_HP:
    case DAMAGE_ABOVE_HP:
    case DAMAGE_UNDER_HP:
        mvwprintw(input, 2, 0, "HP Percentage: ");
        mvwscanw(input, 2, 15, "%d", &word->condition.coeff1);
        word->condition.coeff2 = -1;
        word->condition.effect = UNDEFINED_EFFECT;
        break;

    case DAMAGE_NUMBER_TURNS:
        mvwprintw(input, 2, 0, "Number of turns to check damage: ");
        mvwscanw(input, 2, 33, "%d", &word->condition.coeff1);
        word->condition.coeff2 = -1;
        word->condition.effect = UNDEFINED_EFFECT;
        break;
    case SP_COST:
        mvwprintw(input, 2, 0, "Cost: ");
        mvwscanw(input, 2, 6, "%d", &word->condition.coeff1);
        word->condition.coeff2 = -1;
        word->condition.effect = UNDEFINED_EFFECT;
        break;

    case NUMBER_ALLY_ALIVE:
    case NUMBER_ENEMY_ALIVE:
        mvwprintw(input, 2, 0, "Number to check (>=): ");
        mvwscanw(input, 2, 22, "%d", &word->condition.coeff1);
        word->condition.coeff2 = -1;
        word->condition.effect = UNDEFINED_EFFECT;
        break;

    case NUMBER_ALLY_ABOVE_HP:
    case NUMBER_ALLY_UNDER_HP:
    case NUMBER_ENEMY_ABOVE_HP:
    case NUMBER_ENEMY_UNDER_HP:
        mvwprintw(input, 2, 0, "HP Percentage: ");
        mvwprintw(input, 3, 0, "Number: ");
        mvwscanw(input, 2, 15, "%d", &word->condition.coeff1);
        mvwscanw(input, 3, 8, "%d", &word->condition.coeff2);
        word->condition.effect = UNDEFINED_EFFECT;
        break;

    case TARGET_BUFF:
    case IS_BUFF:
        mvwprintw(input, 2, 0, "Effect: ");
        char* buffOption[] = {"STATS UP", "STATS UP STACKABLE", "DODGE",
                              "REFLECT",  "ENERGY SIPHON",      "INVISIBILITY",
                              "BARRIER",  "INSPIRATION",        "ARCANE STAMP"};
        word->condition.effect = menu_inline(input, 2, 8, buffOption, 9);
        word->condition.coeff1 = -1;
        word->condition.coeff2 = -1;
        break;

    case IS_DEBUFF:
    case TARGET_DEBUFF:
        mvwprintw(input, 2, 0, "Effect: ");
        char* debuffOption[] = {
            "STATS DOWN", "STATS DOWN STACK", "NASTY WOUND", "SEAL",      "SILENCE",
            "TAUNT",      "DISARM",           "BIND",        "PARALYZED", "SKILL DRAIN",
            "DISCONCERT", "CONFUSED",         "DISRUPT"};
        word->condition.effect = menu_inline(input, 2, 8, debuffOption, 13);
        word->condition.coeff1 = -1;
        word->condition.coeff2 = -1;
        break;
    }
}

void fl_effect_set_undefined(FLEffect* eff) {
    eff->type = UNDEFINED_EFFECT;
    eff->coeff1 = -1;
    eff->coeff2 = -1;
    eff->stat1 = UNDEFINED_STAT;
    eff->stat2 = UNDEFINED_STAT;
}

void fl_effect_get_info(FLEffect* eff, WINDOW* input, int y, int x) {
    mvwprintw(input, y, x, "Effect: ");
    char* effectOptions[] = {
        "STATS UP",         "STATS UP STACK", "DODGE",       "REFLECT",      "ENERGY SIPHON",
        "INVISIBILITY",     "BARRIER",        "INSPIRATION", "ARCANE STAMP", "STATS DOWN",
        "STATS DOWN STACK", "NASTY WOUND",    "SEAL",        "SILENCE",      "TAUNT",
        "DISARM",           "BIND",           "PARALYZED",   "SKILL DRAIN",  "DISCONCERT",
        "CONFUSED",         "DISRUPT"};
    char* statOptions[] = {"MAX HP", "HP", "ATTACK", "DEFENSE", "RESISTANCE", "SPEED", "ENERGY"};
    eff->type = menu_inline(input, y, x + 8, effectOptions, 22);

    switch (eff->type) {
    case STATS_UP:
    case STATS_DOWN:
        mvwprintw(input, y + 1, x, "Stat Scale 1:");
        mvwprintw(input, y + 2, x, "Scale 1:");
        mvwprintw(input, y + 3, x, "Stat Scale 2:");
        mvwprintw(input, y + 4, x, "Scale 2:");
        eff->stat1 = menu_inline(input, y + 1, x + 13, statOptions, 7);
        mvwscanw(input, y + 2, x + 8, "%d", &eff->coeff1);
        eff->stat1 = menu_inline(input, y + 3, x + 13, statOptions, 7);
        mvwscanw(input, y + 4, x + 8, "%d", &eff->coeff2);

        break;
    case STATS_UP_STACK:
    case STATS_DOWN_STACK:
    case BARRIER:
        mvwprintw(input, y + 1, x, "Stat Scale 1:");
        mvwprintw(input, y + 2, x, "Scale 1:");

        eff->stat1 = menu_inline(input, y + 1, x + 13, statOptions, 7);
        mvwscanw(input, y + 2, x + 8, "%d", &eff->coeff1);

        eff->stat2 = UNDEFINED_STAT;
        eff->coeff2 = -1;
        break;
    case NASTY_WOUND:
        mvwprintw(input, y + 1, x, "Scale:");
        mvwscanw(input, y + 1, x + 6, "%d", &eff->coeff1);

        eff->stat1 = UNDEFINED_STAT;
        eff->stat2 = UNDEFINED_STAT;
        eff->coeff2 = -1;
        break;
    default:
        eff->stat1 = UNDEFINED_STAT;
        eff->stat2 = UNDEFINED_STAT;
        eff->coeff1 = -1;
        eff->coeff2 = -1;
        break;
    }
}

void fl_card_get_word_power(FLWord* word, WINDOW* input) {
    mvwprintw(input, 4, 0, "Power word: ");
    mvwprintw(input, 5, 0, "Target count: ");
    char* statOptions[] = {"MAX HP", "HP", "ATTACK", "DEFENSE", "RESISTANCE", "SPEED", "ENERGY"};
    char* powerWordOptions[] = {"DEAL", "HEAL", "INFLICT", "DISPEL", "IMMUNE"};
    word->word.type = menu_inline(input, 4, 12, powerWordOptions, 5);

    mvwscanw(input, 5, 14, "%d", &word->word.target);

    switch (word->word.type) {
    case DEAL:
        mvwprintw(input, 6, 0, "Stat Scale: ");
        mvwprintw(input, 7, 0, "Damage Type: ");
        mvwprintw(input, 8, 0, "Scale: ");

        word->word.stat = menu_inline(input, 6, 12, statOptions, 7);

        char* dmgTypeOptions[] = {"PHYSICAL", "MAGICAL"};
        word->word.dmgType = menu_inline(input, 7, 13, dmgTypeOptions, 2);

        mvwscanw(input, 8, 7, "%d", &word->word.coeff);

        word->word.length = -1;
        fl_effect_set_undefined(&word->word.effect);
        break;
    case MEND:
        mvwprintw(input, 6, 0, "Stat Scale: ");
        mvwprintw(input, 7, 0, "Scale: ");
        word->word.stat = menu_inline(input, 6, 12, statOptions, 7);

        mvwscanw(input, 7, 7, "%d", &word->word.coeff);

        word->word.dmgType = UNDEFINED_DAMAGE;
        word->word.length = -1;
        fl_effect_set_undefined(&word->word.effect);
        break;
    case DISPEL:
        fl_effect_get_info(&word->word.effect, input, 6, 0);

        word->word.stat = UNDEFINED_STAT;
        word->word.length = -1;
        word->word.dmgType = UNDEFINED_DAMAGE;
        word->word.coeff = -1;
        break;

    case INFLICT:
    case IMMUNE:
        mvwprintw(input, 6, 0, "Length of effect: ");
        fl_effect_get_info(&word->word.effect, input, 7, 0);
        mvwscanw(input, 6, 18, "%d", &word->word.length);

        word->word.stat = UNDEFINED_STAT;
        word->word.dmgType = UNDEFINED_DAMAGE;
        word->word.coeff = -1;
        break;
    }
}

void fl_card_get_word(FLWord* word, WINDOW* input, int word_num) {
    mvwprintw(input, 0, 0, "Word %d", word_num);
    fl_card_get_word_condition(word, input);
    fl_card_get_word_power(word, input);
}

void fl_card_get_info(FLCard* card, WINDOW* input, int deck_index) {

    char* className = (deck_index == NORMAL) ? "Normal Attack" : "Incantation";
    mvwprintw(input, 5, 1, "                                ");
    mvwprintw(input, 5, 1, "Card Class: %s", className);
    wrefresh(input);

    card->cardClass = (deck_index == NORMAL) ? NORMAL : INCANTATION;

    WINDOW* wordInput = subwin(input, 15, MAX_COLUMNS - 2, 14, 1);
    for (int i = 0; i < 2; i++) {
        whline(wordInput, 0, MAX_COLUMNS - 2);
        fl_card_get_word(&card->words[i], wordInput, i + 1);
        wclear(wordInput);
        wrefresh(wordInput);
    }
    delwin(wordInput);
    wrefresh(input);
}

void fl_card_family_get_info(FLCardFamily* family, WINDOW* input, int current, int total) {
    for (int i = 0; i < 3; i++) {
        mvwprintw(input, 3, 1, "Card Family: %d/%d", current + 1, total);
        mvwprintw(input, 4, 1, "Card Stars: %d/3", i + 1);
        fl_card_get_info(&family->members[i], input, current);
    }
}

void fl_card_get_ultimate(FLUltimateCard* ultCard, WINDOW* input) {
    mvwprintw(input, 1, 1, "Card Class: Ultimate");
    mvwprintw(input, 2, 1, "Energy Cost: ");
    wrefresh(input);
    mvwscanw(input, 2, 14, "%d", &ultCard->energyCost);
    ultCard->cardClass = ULTIMATE;

    WINDOW* wordInput = subwin(input, 15, MAX_COLUMNS - 2, 14, 1);
    for (int i = 0; i < 3; i++) {
        whline(wordInput, 0, MAX_COLUMNS - 2);
        fl_card_get_word(&ultCard->words[i], wordInput, i + 1);
        wclear(wordInput);
        wrefresh(wordInput);
    }
    delwin(input);
    wrefresh(input);
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

void character_get_stats(FLCharacter* character, WINDOW* input, int current, int total) {
    mvwprintw(input, 1, 1, "Character Number: %d/%d", current, total);
    mvwprintw(input, 2, 1, "Step2: Stats");

    mvwprintw(input, 3, 1, "HP: ");
    mvwprintw(input, 3, 6 + COLUMN_OFFSET, "HP/lvl: ");

    mvwprintw(input, 4, 1, "ATK: ");
    mvwprintw(input, 4, 6 + COLUMN_OFFSET, "ATK/lvl: ");

    mvwprintw(input, 5, 1, "DEF: ");
    mvwprintw(input, 5, 6 + COLUMN_OFFSET, "DEF/lvl: ");

    mvwprintw(input, 6, 1, "RES: ");
    mvwprintw(input, 6, 6 + COLUMN_OFFSET, "RES/lvl: ");

    mvwprintw(input, 7, 1, "SPD: ");
    mvwprintw(input, 7, 6 + COLUMN_OFFSET, "Quality: ");

    mvwprintw(input, 8, 1, "Regen: ");

    mvwscanw(input, 3, 5, "%lf", &character->stats.hp);
    mvwscanw(input, 3, 14 + COLUMN_OFFSET, "%lf", &character->stats.hpg);
    mvwscanw(input, 4, 6, "%lf", &character->stats.atk);
    mvwscanw(input, 4, 15 + COLUMN_OFFSET, "%lf", &character->stats.atkg);
    mvwscanw(input, 5, 6, "%lf", &character->stats.def);
    mvwscanw(input, 5, 15 + COLUMN_OFFSET, "%lf", &character->stats.defg);
    mvwscanw(input, 6, 6, "%lf", &character->stats.res);
    mvwscanw(input, 6, 15 + COLUMN_OFFSET, "%lf", &character->stats.resg);
    mvwscanw(input, 7, 6, "%lf", &character->stats.spd);

    char* quality_list[] = {"Common", "Uncommon", "Rare", "Epic", "Legendary"};
    character->stats.quality = menu_inline(input, 7, 15 + COLUMN_OFFSET, quality_list, 5);

    char* regen_list[] = {"AUTO", "OFFENSIVE", "DEFENSIVE"};
    character->stats.regen = menu_inline(input, 8, 8, regen_list, 3);
    wgetch(input);
}

FLCharacter character_get_info(int current, int total) {
    refresh();
    FLCharacter data;
    WINDOW* input = newwin(25, MAX_COLUMNS, 5, 0);
    box(input, 0, 0);

    character_get_meta_data(&data, input, current, total);
    reinit_window(input);

    character_get_stats(&data, input, current, total);
    reinit_window(input);

    for (unsigned int i = 0; i < 2 + data.stats.quality; i++) {
        mvwprintw(input, 1, 1, "Character Number: %d/%d", current, total);
        mvwprintw(input, 2, 1, "Step3: Card creation");
        fl_card_family_get_info(&data.deck[i], input, i, 2 + data.stats.quality);
        reinit_window(input);
    }
    fl_card_get_ultimate(&data.ultimate, input);
    reinit_window(input);

    delwin(input);
    return data;
}

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    WINDOW* info = print_info();

    FLGameData data = get_basic_info();
    strcpy(data.editorVersion, FL_EDITOR_VERSION);

    FLCharacter characters[data.characterCount];
    for (int i = 0; i < data.characterCount; i++) {
        characters[i] = character_get_info(i, data.characterCount);
    }

    delwin(info);
    getch();
    endwin();

    return 0;
}
