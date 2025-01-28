#include "fl-effect.h"
#include <utils.h>

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
    eff->type = menu_inline(input, y, x + 8, effectOptions, 22, 2);

    switch (eff->type) {
    case STATS_UP:
    case STATS_DOWN:
        mvwprintw(input, y + 1, x, "Stat Scale 1:");
        mvwprintw(input, y + 2, x, "Scale 1:");
        mvwprintw(input, y + 3, x, "Stat Scale 2:");
        mvwprintw(input, y + 4, x, "Scale 2:");
        eff->stat1 = menu_inline(input, y + 1, x + 13, statOptions, 7, 4);
        mvwscanw(input, y + 2, x + 8, "%d", &eff->coeff1);
        eff->stat1 = menu_inline(input, y + 3, x + 13, statOptions, 7, 4);
        mvwscanw(input, y + 4, x + 8, "%d", &eff->coeff2);

        break;
    case STATS_UP_STACK:
    case STATS_DOWN_STACK:
    case BARRIER:
        mvwprintw(input, y + 1, x, "Stat Scale 1:");
        mvwprintw(input, y + 2, x, "Scale 1:");

        eff->stat1 = menu_inline(input, y + 1, x + 13, statOptions, 7, 4);
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