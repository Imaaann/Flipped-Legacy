#include "fl-condition.h"
#include <stdlib.h>
#include <utils.h>

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
