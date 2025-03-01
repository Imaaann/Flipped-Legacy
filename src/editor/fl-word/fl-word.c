#include "fl-word.h"
#include "fl-condition/fl-condition.h"
#include "fl-effect/fl-effect.h"
#include "fl-power-word/fl-power-word.h"
#include <utils.h>

void fl_word_get_semantic(FLWord* word, char* str) {
    char* stats[] = {"Max HP", "HP", "ATK", "DEF", "RES", "SPD", "Energy"};
    char* dmgTypes[] = {"Physical", "Magical"};

    char conditionSemantic[128] = {'\0'};
    fl_condition_get_semantic(&word->condition, conditionSemantic);

    char targetText[16] = {'\0'};
    if (word->power.target == 0) {
        sprintf(targetText, "Self");
    } else {
        sprintf(targetText, "%d-Target", word->power.target);
    }

    char effectSemantic[64] = {'\0'};
    fl_effect_get_semantic(&word->power.effect, effectSemantic);

    char* typeText = (word->power.effect.type >= STATS_DOWN) ? "debuff" : "buff";
    char* immuneTypeText = (word->power.effect.type >= STATS_DOWN) ? "buff" : "debuff";
    char* dispelText = (word->power.effect.type >= STATS_DOWN) ? "dispel" : "purify";
    char* inflictText = (word->power.effect.type >= STATS_DOWN) ? "inflict" : "bestow";

    switch (word->power.type) {
    case DEAL:
        sprintf(str, "%s Attack, %s deal %d%% of %s as %s", targetText, conditionSemantic,
                word->power.coeff, stats[word->power.stat], dmgTypes[word->power.dmgType]);
        break;
    case MEND:
        sprintf(str, "%s Heal, %s heal up to %d%% of %s", targetText, conditionSemantic,
                word->power.coeff, stats[word->power.stat]);
        break;
    case INFLICT:
        sprintf(str, "%s %s, %s %s [%s] for %d", targetText, typeText, conditionSemantic,
                inflictText, effectSemantic, word->power.length);
        break;
    case DISPEL:
        sprintf(str, "%s %s, %s %s [%s]", targetText, typeText, conditionSemantic, dispelText,
                effectSemantic);
        break;
    case IMMUNE:
        sprintf(str, "%s %s, %s Immune to [%s] for %d", targetText, immuneTypeText,
                conditionSemantic, effectSemantic, word->power.length);
        break;
    }
}
