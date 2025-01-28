#include "fl-condition.h"
#include <utils.h>

void fl_condition_input(FLCondition* condition, WINDOW* input) {
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
    condition->type = menu_inline(input, 1, 12, conditionOptions, 22, 1);

    switch (condition->type) {

    case NONE:
    case DAMAGE:
        condition->coeff1 = -1;
        condition->coeff2 = -1;
        condition->effect = UNDEFINED_EFFECT;
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
        mvwscanw(input, 2, 15, "%d", &condition->coeff1);
        condition->coeff2 = -1;
        condition->effect = UNDEFINED_EFFECT;
        break;

    case DAMAGE_NUMBER_TURNS:
        mvwprintw(input, 2, 0, "Number of turns to check damage: ");
        mvwscanw(input, 2, 33, "%d", &condition->coeff1);
        condition->coeff2 = -1;
        condition->effect = UNDEFINED_EFFECT;
        break;
    case SP_COST:
        mvwprintw(input, 2, 0, "Cost: ");
        mvwscanw(input, 2, 6, "%d", &condition->coeff1);
        condition->coeff2 = -1;
        condition->effect = UNDEFINED_EFFECT;
        break;

    case NUMBER_ALLY_ALIVE:
    case NUMBER_ENEMY_ALIVE:
        mvwprintw(input, 2, 0, "Number to check (>=): ");
        mvwscanw(input, 2, 22, "%d", &condition->coeff1);
        condition->coeff2 = -1;
        condition->effect = UNDEFINED_EFFECT;
        break;

    case NUMBER_ALLY_ABOVE_HP:
    case NUMBER_ALLY_UNDER_HP:
    case NUMBER_ENEMY_ABOVE_HP:
    case NUMBER_ENEMY_UNDER_HP:
        mvwprintw(input, 2, 0, "HP Percentage: ");
        mvwprintw(input, 3, 0, "Number: ");
        mvwscanw(input, 2, 15, "%d", &condition->coeff1);
        mvwscanw(input, 3, 8, "%d", &condition->coeff2);
        condition->effect = UNDEFINED_EFFECT;
        break;

    case TARGET_BUFF:
    case IS_BUFF:
        mvwprintw(input, 2, 0, "Effect: ");
        char* buffOption[] = {"STATS UP", "STATS UP STACKABLE", "DODGE",
                              "REFLECT",  "ENERGY SIPHON",      "INVISIBILITY",
                              "BARRIER",  "INSPIRATION",        "ARCANE STAMP"};
        condition->effect = menu_inline(input, 2, 8, buffOption, 9, 2);
        condition->coeff1 = -1;
        condition->coeff2 = -1;
        break;

    case IS_DEBUFF:
    case TARGET_DEBUFF:
        mvwprintw(input, 2, 0, "Effect: ");
        char* debuffOption[] = {
            "STATS DOWN", "STATS DOWN STACK", "NASTY WOUND", "SEAL",      "SILENCE",
            "TAUNT",      "DISARM",           "BIND",        "PARALYZED", "SKILL DRAIN",
            "DISCONCERT", "CONFUSED",         "DISRUPT"};
        condition->effect = menu_inline(input, 2, 8, debuffOption, 13, 2);
        condition->coeff1 = -1;
        condition->coeff2 = -1;
        break;
    }
}
