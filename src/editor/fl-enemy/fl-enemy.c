#include "fl-enemy.h"
#include "fl-card/fl-card.h"
#include "fl-character/fl-character.h"
#include <stdlib.h>
#include <string.h>

void fl_enemy_save_to_file(FLEnemy* enemyArray, FLGameData* data) {
    char* fileName = (char*)malloc(strlen(data->gameName) + 8);
    sprintf(fileName, "%s.flge", data->gameName);

    FILE* enemyFile = fopen(fileName, "wb");
    free(fileName);

    for (int i = 0; i < data->enemyCount; i++) {
        fwrite(&enemyArray[i], sizeof(FLEnemy), 1, enemyFile);
    }

    fclose(enemyFile);
}

void fl_enemy_from_file(FLEnemy* enemyArray, char* name, int characterCount) {
    char* fileName = (char*)malloc(strlen(name) + 8);
    sprintf(fileName, "%s.flge", name);

    FILE* characterFile = fopen(fileName, "rb");
    free(fileName);

    if (characterFile == NULL)
        return;

    int index = 0;
    while (fread(&enemyArray[index], sizeof(FLCharacter), 1, characterFile) &&
           index < characterCount) {
        index++;
    }

    fclose(characterFile);
}