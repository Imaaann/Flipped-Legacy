#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


/*
*   TODO:
*   -Make a Function that can handle a path (image path) and returns a texture with that image
*/

SDL_Texture* Texture_Loader(const char* path, SDL_Renderer* ren) {

    SDL_Surface* tmpSurf;

    tmpSurf = IMG_Load(path);
    if (!tmpSurf) {
        perror("Error loading image!\n");
        SDL_FreeSurface(tmpSurf);
        return NULL;
    }

    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(ren,tmpSurf);
    if (!texture) {
        perror("Error creating texture from surface!\n");
        SDL_FreeSurface(tmpSurf);
        return NULL;
    }

    SDL_FreeSurface(tmpSurf); 
    return texture;
}
