#define MAX_CHILDREN 8
#define MAX_NAME 256
#define MAX_MESSAGE 1024
#include <stdbool.h>
#include "EditorEnums.h"
#include "PowerWords/PowerWordTypes.h"
#include "Cards/CardTypes.h"

typedef struct _FL_Health {
    int MAX_HP;
    int CURRENT_HP;

    FL_DMG_TYPES dmg_type;
    int Damage_Taken;
    int Damage_Taken_cummulative;
} FL_Health;

typedef struct _FL_SP {
    int MAX_SP;
    int CURRENT_SP;
} FL_SP;

typedef struct _FL_Character {

    int ID;
    int isUnlocked;
    char Name[MAX_NAME];
    char Card_Bg[MAX_NAME];

    //Stats
    int Lvl;
    FL_Health HP;
    int ATK;
    int DEF;
    int RES;
    int SPD;
    FL_SP SP;
    FL_EFFECTED active[MAX_EFFECTS];

    //Growth Stats;
    int Hp_g;
    int Atk_g;
    int Def_g;
    int Res_g;

    //More stuff
    FL_SP_REGEN regen;
    FL_COST cost;

    // Card shit !
    int Unlocked_Deck;
    FL_CARD Deck[7]; // Up to 7 incantation for cost 5 characters
    FL_CARD Normal_Attack;
    FL_CARD Ult;

} FL_Character;

typedef struct _FL_ENEMY {
    //identification
    int ID;
    char Name[MAX_NAME];
    char Card_Bg[MAX_NAME];

    //Stats
    int Lvl;
    FL_Health HP;
    int ATK;
    int DEF;
    int RES;
    int SPD;

    //Cards
    FL_CARD Deck[2];
    FL_CARD Normal_Attack;
    FL_CARD Ult;

    //AI bs
    float Aggresive;
    float Passive;
    float intel;
    float longivity;


} FL_ENEMY;

typedef struct _FL_List {
    char Name[MAX_NAME];
    char path[MAX_NAME];
} FL_List;

typedef struct _FL_COMMANDER {
    FL_COST Cost;
    int Current_xp;
    int NextLvlXP;

    float pT1;
    float pT2;
    float pT3;
} FL_COMMANDER;

typedef struct _FL_BATTLE {
    int ID;
    char Name[MAX_NAME];
    char Path[MAX_NAME];
    char Bg_Path[MAX_NAME];
    char Bg_Music[MAX_NAME];
    

    int waveCount; // Max 4 waves
    int waveEnemyCount[4];

    FL_COMMANDER commander;
} FL_BATTLE;

typedef struct _FL_STORY_FRAME {
    unsigned int ID; // we will need to link the graph using these ID's :sob:

    char Background[MAX_NAME];
    char Models[3][MAX_NAME];
    char Talking[MAX_NAME];
    char Message[MAX_MESSAGE];

    FL_SKIP_COND cond;
    unsigned int Next_ID[MAX_CHILDREN]; // A frame can have up to 8 children (yes this will limit menu options to 8 but thats fine)
    bool isSpecialNext; // Only works if 1 children, 

} FL_STORY_FRAME;

typedef struct _FL_STORY {
    char story_path[MAX_NAME];
    char Bg_audio[MAX_NAME];
} FL_STORY;

typedef struct _FL_ROUND_PACKET {

    int direction; // 1: Player , 0: Enemy 

    int Effected_Char[3];
    FL_Character* Character[3];

    int Effected_Enem[3];
    FL_ENEMY* Enemies[3];

    FL_CARD* cardplayed;

    int DMG_TAKEN[3];
    FL_EFFECTS Effects[MAX_EFFECTS];

} FL_ROUND_PACKET;

typedef struct _FL_GAME_DATA {
    char Name[MAX_NAME];
    char CharList[MAX_NAME];
    char EnemyList[MAX_NAME];
    int local_var[16];
} FL_GAME_DATA;