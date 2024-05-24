#include "EditorEnums.h"

#define MAX_EFFECTS 16

typedef struct _FL_EFFECTED {
    FL_EFFECTS type;
    int rounds_left;
} FL_EFFECTED;

typedef struct _FL_SUMMON {
    char Name[256];
    char Card_Bg[256];
    FL_EFFECTED effects[16];
    int HP;
    int ATK;
    int DEF;
    int RES;
    int SPD;
} FL_SUMMON;

typedef struct _FL_POWER_DEAL {
    FL_POWER_NAMES type;
    int multi;
    int targets;
    FL_DMG_TYPES dmg_type;
} FL_POWER_DEAL;

typedef struct _FL_POWER_HEAL {
    FL_POWER_NAMES type;
    int multi;
    int targets;
} FL_POWER_HEAL;

typedef struct _FL_POWER_INFLICT {
    
    FL_POWER_NAMES type;
    int targets;

    FL_EFFECTS effect;

    int rounds;

    int mult1;
    int mult2;
    FL_STATS Stat1;
    FL_STATS Stat2;


} FL_POWER_INFLICT;

typedef struct _FL_POWER_DISPEL {
    FL_POWER_NAMES type;
    FL_EFFECTS effect;
    int targets;
} FL_POWER_DISPEL;

typedef struct _FL_POWER_SUMMON {
    FL_POWER_NAMES type;
    FL_SUMMON summon;
} FL_POWER_SUMMON;

typedef struct _FL_POWER_IMMUNE {
    FL_POWER_NAMES type;
    FL_EFFECTS effect;
    int targets;
    int rounds;
} FL_POWER_IMMUNE;

typedef union _FL_POWER_WORD { 
    FL_POWER_NAMES type;
    FL_POWER_DEAL deal;
    FL_POWER_HEAL heal;
    FL_POWER_INFLICT inflict;
    FL_POWER_DISPEL dispel;
    FL_POWER_IMMUNE immune;
    FL_POWER_SUMMON summon;
} FL_POWER_WORD;

