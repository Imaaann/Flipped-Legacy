#include "fl-power-word.h"
#include "fl-effect/fl-effect.h"
#include <utils.h>

void fl_power_input(FLPowerWord* power, WINDOW* input) {
    mvwprintw(input, 4, 0, "Power word: ");
    mvwprintw(input, 5, 0, "Target count: ");
    char* statOptions[] = {"MAX HP", "HP", "ATTACK", "DEFENSE", "RESISTANCE", "SPEED", "ENERGY"};
    char* powerWordOptions[] = {"DEAL", "HEAL", "INFLICT", "DISPEL", "IMMUNE"};
    char* effectOptions[] = {
        "STATS UP",         "STATS UP STACK", "DODGE",       "REFLECT",      "ENERGY SIPHON",
        "INVISIBILITY",     "BARRIER",        "INSPIRATION", "ARCANE STAMP", "STATS DOWN",
        "STATS DOWN STACK", "NASTY WOUND",    "SEAL",        "SILENCE",      "TAUNT",
        "DISARM",           "BIND",           "PARALYZED",   "SKILL DRAIN",  "DISCONCERT",
        "CONFUSED",         "DISRUPT"};
    power->type = menu_inline(input, 4, 12, powerWordOptions, 5, 2);

    mvwscanw(input, 5, 14, "%d", &power->target);

    switch (power->type) {
    case DEAL:
        mvwprintw(input, 6, 0, "Stat Scale: ");
        mvwprintw(input, 7, 0, "Damage Type: ");
        mvwprintw(input, 8, 0, "Scale: ");

        power->stat = menu_inline(input, 6, 12, statOptions, 7, 4);

        char* dmgTypeOptions[] = {"PHYSICAL", "MAGICAL"};
        power->dmgType = menu_inline(input, 7, 13, dmgTypeOptions, 2, 3);

        mvwscanw(input, 8, 7, "%d", &power->coeff);

        power->length = -1;
        fl_effect_set_undefined(&power->effect);
        break;
    case MEND:
        mvwprintw(input, 6, 0, "Stat Scale: ");
        mvwprintw(input, 7, 0, "Scale: ");
        power->stat = menu_inline(input, 6, 12, statOptions, 7, 4);

        mvwscanw(input, 7, 7, "%d", &power->coeff);

        power->dmgType = UNDEFINED_DAMAGE;
        power->length = -1;
        fl_effect_set_undefined(&power->effect);
        break;
    case DISPEL:
        mvwprintw(input, 6, 0, "Effect: ");
        power->effect.type = menu_inline(input, 6, 8, effectOptions, 22, 2);

        power->effect.stat1 = UNDEFINED_STAT;
        power->effect.stat2 = UNDEFINED_STAT;
        power->effect.coeff1 = -1;
        power->effect.coeff2 = -1;

        power->stat = UNDEFINED_STAT;
        power->length = -1;
        power->dmgType = UNDEFINED_DAMAGE;
        power->coeff = -1;
        break;

    case INFLICT:
    case IMMUNE:
        mvwprintw(input, 6, 0, "Length of effect: ");
        fl_effect_get_info(&power->effect, input, 7, 0);
        mvwscanw(input, 6, 18, "%d", &power->length);

        power->stat = UNDEFINED_STAT;
        power->dmgType = UNDEFINED_DAMAGE;
        power->coeff = -1;
        break;
    }
}