#include "fl-character.h"
#include "fl-card/fl-card.h"
#include <stdlib.h>
#include <string.h>
#include <utils.h>

void fl_character_save_to_file(FLCharacter* characterArray, FLGameData* data) {
    char* fileName = (char*)malloc(strlen(data->gameName) + 8);
    sprintf(fileName, "%s.flgc", data->gameName);

    FILE* characterFile = fopen(fileName, "wb");
    free(fileName);

    if (characterFile == NULL)
        return;

    for (int i = 0; i < data->characterCount; i++) {
        fwrite(&characterArray[i], sizeof(FLCharacter), 1, characterFile);
    }
    fclose(characterFile);
}

void fl_character_from_file(FLCharacter* characterArray, char* name, int characterCount) {
    char* fileName = (char*)malloc(strlen(name) + 8);
    sprintf(fileName, "%s.flgc", name);

    FILE* characterFile = fopen(fileName, "rb");
    free(fileName);

    if (characterFile == NULL)
        return;

    int index = 0;
    while (fread(&characterArray[index], sizeof(FLCharacter), 1, characterFile) &&
           index < characterCount) {
        index++;
    }

    fclose(characterFile);
}