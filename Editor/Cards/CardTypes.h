
/// @brief Self explanatory really
typedef struct _FL_CARD_TIER {
    char Name[MAX_NAME];
    char Bg_path[MAX_NAME];
    char Lore[MAX_NAME];
    int SP_COST;
    FL_INC_TYPE Incan;
    FL_CARD_TYPE type;
    FL_POWER_WORD pw1; // Forced Unconditional
    FL_POWER_WORD pw2; // Unconditional or Conditional
    FL_POWER_WORD pw3; // if pw2 was conditional then this one will be too under same condition
    FL_CONDITIONS cond;
} FL_CARD_TIER;


/// @brief We will process every pw into a function and put them under the condition as needed,
typedef struct _FL_CARD {
    int Tier;
    FL_CARD_TIER Card[3]; // 3 Card tiers per card
} FL_CARD;