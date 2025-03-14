#pragma once

#define DECK_SIZE 6

enum _FLQuality { COMMON, UNCOMMON, RARE, EPIC, LEGENDARY };
typedef enum _FLQuality FLQuality;

enum _FLRegen { AUTO, OFFENSIVE, DEFENSIVE };
typedef enum _FLRegen FLRegen;

enum _FLCardClass { NORMAL, INCANTATION, ULTIMATE };
typedef enum _FLCardClass FLCardClass;

enum _FLStat { MAX_HEALTH, HEALTH, ATTACK, DEFENSE, RESISTANCE, SPEED, ENERGY, UNDEFINED_STAT };
typedef enum _FLStat FLStat;

enum _FLPowerWordType { DEAL, MEND, INFLICT, DISPEL, IMMUNE };
typedef enum _FLPowerWordType FLPowerWordType;

enum _FLDamageType { PHYSICAL, MAGICAL, UNDEFINED_DAMAGE };
typedef enum _FLDamageType FLDamageType;

enum _FLConditionType {
    NONE,
    UNDER_HP,
    ABOVE_HP,
    ALLY_UNDER_HP,
    ALLY_ABOVE_HP,
    ENEMY_UNDER_HP,
    ENEMY_ABOVE_HP,
    NUMBER_ALLY_UNDER_HP,
    NUMBER_ALLY_ABOVE_HP,
    NUMBER_ENEMY_UNDER_HP,
    NUMBER_ENEMY_ABOVE_HP,
    NUMBER_ALLY_ALIVE,
    NUMBER_ENEMY_ALIVE,
    IS_BUFF,
    IS_DEBUFF,
    TARGET_BUFF,
    TARGET_DEBUFF,
    DAMAGE,
    DAMAGE_UNDER_HP,
    DAMAGE_ABOVE_HP,
    DAMAGE_NUMBER_TURNS,
    SP_COST
};
typedef enum _FLConditionType FLConditionType;

enum _FLEffectType {
    // BUFFS
    STATS_UP,       // 2s 2c
    STATS_UP_STACK, // 1s 1c
    DODGE,          // 0s 0c
    REFLECT,        // 0s 0c
    ENERGY_SIPHON,  // 0s 0c
    INVISIBILITY,   // 0s 0c
    BARRIER,        // 1s 1c
    INSPIRATION,    // 0s 0c
    ARCANE_STAMP,   // 0s 0c

    // DEBUFFS
    STATS_DOWN,       // 2s 2c
    STATS_DOWN_STACK, // 1s 1c
    NASTY_WOUND,      // 0s 1c
    SEAL,             // 0s 0c
    SILENCE,          // 0s 0c
    TAUNT,            // 0s 0c
    DISARM,           // 0s 0c
    BIND,             // 0s 0c
    PARALYZED,        // 0s 0c
    SKILL_DRAIN,      // 0s 0c
    DISCONCERT,       // 0s 0c
    CONFUSED,         // 0s 0c
    DISRUPT,          // 0s 0c

    UNDEFINED_EFFECT
};
typedef enum _FLEffectType FLEffectType;

// Structs
struct _FLStatSheet {
    double hp;
    double hpg; // g stands for growth
    double atk;
    double atkg;
    double def;
    double defg;
    double res;
    double resg;
    double spd;
    FLQuality quality;
    FLRegen regen;
};
typedef struct _FLStatSheet FLStatSheet;

struct _FLGameData {
    char editorVersion[16];
    char gameName[64];
    int characterCount;
    int enemyCount;
};
typedef struct _FLGameData FLGameData;

struct _FLEffect {
    FLEffectType type;
    int coeff1;
    int coeff2;
    FLStat stat1;
    FLStat stat2;
};
typedef struct _FLEffect FLEffect;

struct _FLCondition {
    FLConditionType type;
    int coeff1;
    int coeff2;
    FLEffectType effect;
};
typedef struct _FLCondition FLCondition;

struct _FLPowerWord {
    FLPowerWordType type;
    int target;
    int coeff;
    FLStat stat;
    FLDamageType dmgType;
    FLEffect effect;
    int length;
};
typedef struct _FLPowerWord FLPowerWord;

struct _FLWord {
    FLCondition condition;
    FLPowerWord power;
};
typedef struct _FLWord FLWord;

struct _FLCard {
    FLCardClass cardClass;
    FLWord words[2];
};
typedef struct _FLCard FLCard;

struct _FLUltimateCard {
    FLCardClass cardClass;
    int energyCost;
    FLWord words[3];
};
typedef struct _FLUltimateCard FLUltimateCard;

struct _FLCardFamily {
    FLCard members[3];
};
typedef struct _FLCardFamily FLCardFamily;

struct _FLCharacter {
    // Meta Data
    char name[128];
    char image[128];
    char description[256];

    // StatSheet
    FLStatSheet stats;

    // Deck
    FLCardFamily deck[DECK_SIZE];
    FLUltimateCard ultimate;
};
typedef struct _FLCharacter FLCharacter;

struct _FLEnemy {
    FLCharacter base;
    int attackBias;
    int buffBias;
    int debuffBias;
    int healBias;
};
typedef struct _FLEnemy FLEnemy;

struct _FLLoadedGame {
    FLGameData* data;
    FLCharacter* characterArray;
    FLEnemy* enemyArray;
};
typedef struct _FLLoadedGame FLLoadedGame;