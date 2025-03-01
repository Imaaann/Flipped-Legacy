#include "fl-effect.h"
#include <utils.h>

void fl_effect_set_undefined(FLEffect* eff) {
    eff->type = UNDEFINED_EFFECT;
    eff->coeff1 = -1;
    eff->coeff2 = -1;
    eff->stat1 = UNDEFINED_STAT;
    eff->stat2 = UNDEFINED_STAT;
}

void fl_effect_get_semantic(FLEffect* eff, char* str) {
    char* stats[] = {"Max HP", "HP", "ATK", "DEF", "RES", "SPD", "Energy"};
    char* effectOptions[] = {
        "STATS UP",         "STATS UP STACK", "DODGE",         "REFLECT",      "ENERGY SIPHON",
        "INVISIBILITY",     "BARRIER",        "INSPIRATION",   "ARCANE STAMP", "STATS DOWN",
        "STATS DOWN STACK", "NASTY WOUND",    "SEAL",          "SILENCE",      "TAUNT",
        "DISARM",           "BIND",           "PARALYZED",     "SKILL DRAIN",  "DISCONCERT",
        "CONFUSED",         "DISRUPT",        "INVALID EFFECT"};
    switch (eff->type) {
    case STATS_UP:
        if (eff->stat1 != UNDEFINED_STAT && eff->stat2 != UNDEFINED_STAT) {
            sprintf(str, "+%d%%-%s, +%d%%-%s", eff->coeff1, stats[eff->stat1], eff->coeff2,
                    stats[eff->stat2]);
        } else if (eff->stat1 != UNDEFINED_STAT) {
            sprintf(str, "+%d%%-%s", eff->coeff1, stats[eff->stat1]);
        } else if (eff->stat2 != UNDEFINED_STAT) {
            sprintf(str, "+%d%%-%s", eff->coeff1, stats[eff->stat1]);
        } else {
            sprintf(str, "Invalid STATS UP");
        }
        break;
    case STATS_UP_STACK:
        if (eff->stat1 != UNDEFINED_STAT) {
            sprintf(str, "+1 +%d%%-%s stack", eff->coeff1, stats[eff->stat1]);
        } else {
            sprintf(str, "Invalid STATS UP Stack");
        }
        break;
    case BARRIER:
        if (eff->stat1 != UNDEFINED_STAT) {
            sprintf(str, "+%d%%-%s as barrier", eff->coeff1, stats[eff->stat1]);
        } else {
            sprintf(str, "Invalid BARRIER");
        }
        break;
    case STATS_DOWN:
        if (eff->stat1 != UNDEFINED_STAT && eff->stat2 != UNDEFINED_STAT) {
            sprintf(str, "-%d%%-%s, -%d%%-%s", eff->coeff1, stats[eff->stat1], eff->coeff2,
                    stats[eff->stat2]);
        } else if (eff->stat1 != UNDEFINED_STAT) {
            sprintf(str, "-%d%%-%s", eff->coeff1, stats[eff->stat1]);
        } else if (eff->stat2 != UNDEFINED_STAT) {
            sprintf(str, "-%d%%-%s", eff->coeff1, stats[eff->stat1]);
        } else {
            sprintf(str, "Invalid STATS DOWN");
        }
        break;
    case STATS_DOWN_STACK:
        if (eff->stat1 != UNDEFINED_STAT) {
            sprintf(str, "+1 +%d%%-%s stack", eff->coeff1, stats[eff->stat1]);
        } else {
            sprintf(str, "Invalid STATS DOWN Stack");
        }
        break;
    case NASTY_WOUND:
        sprintf(str, "-%d%% Healing Eff", eff->coeff1);
        break;
    default:
        sprintf(str, "%s", effectOptions[eff->type]);
        break;
    }
}