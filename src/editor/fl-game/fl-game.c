#include "fl-game.h"
#include "fl-character/fl-character.h"
#include "fl-enemy/fl-enemy.h"
#include <stdlib.h>
#include <string.h>
#include <utils.h>

void fl_game_save_to_file(FLGameData* data) {
    char* fileName = (char*)malloc(strlen(data->gameName) + 8);
    sprintf(fileName, "%s.flg", data->gameName);
    FILE* dataFile = fopen(fileName, "w");
    fprintf(dataFile, "%s\n%s\n%d\n%d\n", data->editorVersion, data->gameName, data->characterCount,
            data->enemyCount);

    free(fileName);
}

void fl_game_from_file(char* name, FLGameData* data) {
    char* fileName = (char*)malloc(strlen(name) + 8);
    sprintf(fileName, "./%s.flg", name);

    FILE* dataFile = fopen(fileName, "r");
    free(fileName);

    if (dataFile == NULL) {
        data->characterCount = -1;
        data->enemyCount = -1;
        return;
    }

    fscanf(dataFile, "%[^\n]s", data->editorVersion);
    (void)fgetc(dataFile);

    fscanf(dataFile, "%[^\n]s", data->gameName);
    (void)fgetc(dataFile);

    fscanf(dataFile, "%d", &data->characterCount);
    (void)fgetc(dataFile);

    fscanf(dataFile, "%d", &data->enemyCount);
    (void)fgetc(dataFile);

    fclose(dataFile);
}

FLLoadedGame fl_game_load(char* name) {
    FLLoadedGame result = {0};

    result.data = (FLGameData*)calloc(1, sizeof(FLGameData));
    strcpy(result.data->gameName, name);
    fl_game_from_file(name, result.data);

    if (result.data->characterCount == -1)
        return;

    result.characterArray = (FLCharacter*)calloc(result.data->characterCount, sizeof(FLCharacter));
    result.enemyArray = (FLEnemy*)calloc(result.data->enemyCount, sizeof(FLEnemy));

    fl_character_from_file(result.characterArray, result.data->gameName,
                           result.data->characterCount);
    fl_enemy_from_file(result.enemyArray, result.data->gameName, result.data->enemyCount);

    return result;
}