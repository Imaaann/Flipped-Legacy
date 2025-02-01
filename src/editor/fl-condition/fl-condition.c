#include "fl-condition.h"
#include <stdlib.h>
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

void fl_condition_get_semantic(FLCondition* condition, char* str) {
    char* effectOptions[] = {"stats up",
                             "stats up stackable",
                             "dodge",
                             "reflect",
                             "energy siphon",
                             "invisibility",
                             "barrier",
                             "inspiration",
                             "arcane_stamp",
                             "stats down",
                             "stats down stackable",
                             "nasty wound",
                             "seal",
                             "taunt",
                             "disarm",
                             "disarm",
                             "bind",
                             "paralyzed",
                             "skill drain",
                             "disconcert",
                             "confused",
                             "disrupt"};

    switch (condition->type) {
    case NONE:
        sprintf(str, "");
        break;
    case UNDER_HP:
        sprintf(str, "if self under %d%%HP then", condition->coeff1);
        break;
    case ABOVE_HP:
        sprintf(str, "if self above %d%%HP then", condition->coeff1);
        break;
    case ALLY_UNDER_HP:
        sprintf(str, "if there is an ally under %d%%HP then", condition->coeff1);
        break;
    case ALLY_ABOVE_HP:
        sprintf(str, "if there is an ally above %d%%HP then", condition->coeff1);
        break;
    case ENEMY_UNDER_HP:
        sprintf(str, "if there is an enemy under %d%%HP then", condition->coeff1);
        break;
    case ENEMY_ABOVE_HP:
        sprintf(str, "if there is an enemy above %d%%HP then", condition->coeff1);
        break;
    case NUMBER_ALLY_UNDER_HP:
        sprintf(str, "if there is atleast %d allies under %d%%HP then", condition->coeff2,
                condition->coeff1);
        break;
    case NUMBER_ALLY_ABOVE_HP:
        sprintf(str, "if there is atleast %d allies above %d%%HP then", condition->coeff2,
                condition->coeff1);
        break;
    case NUMBER_ENEMY_UNDER_HP:
        sprintf(str, "if there is at least %d enemies under %d%%HP then", condition->coeff2,
                condition->coeff1);
        break;
    case NUMBER_ENEMY_ABOVE_HP:
        sprintf(str, "if there is at least %d enemies above %d%%HP then", condition->coeff2,
                condition->coeff1);
        break;
    case NUMBER_ALLY_ALIVE:
        sprintf(str, "if there is at least %d allies alive then", condition->coeff1);
        break;
    case NUMBER_ENEMY_ALIVE:
        sprintf(str, "if there is at least %d enemies alive then", condition->coeff1);
        break;
    case IS_BUFF:
        sprintf(str, "if buffed with %s then", effectOptions[condition->effect]);
        break;
    case IS_DEBUFF:
        sprintf(str, "if debuffed with %s then", effectOptions[condition->effect]);
        break;
    case TARGET_BUFF:
        sprintf(str, "if target buffed with %s then", effectOptions[condition->effect]);
        break;
    case TARGET_DEBUFF:
        sprintf(str, "if target debuffed with %s then", effectOptions[condition->effect]);
        break;
    case DAMAGE:
        sprintf(str, "if they took damage then");
        break;
    case DAMAGE_UNDER_HP:
        sprintf(str, "if taken damage under %d%%HP then", condition->coeff1);
        break;
    case DAMAGE_ABOVE_HP:
        sprintf(str, "if taken damage above %d%%HP then", condition->coeff1);
        break;
    case DAMAGE_NUMBER_TURNS:
        sprintf(str, "if took damage in the last %d turns then", condition->coeff1);
        break;
    case SP_COST:
        sprintf(str, "costs %d energy to", condition->coeff1);
        break;
    }
}
