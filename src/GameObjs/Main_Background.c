#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../types.h"

void Background_update(struct GameObj* self) {
    printf("Background has been updated!\n");
}

void Background_render(struct GameObj* self,SDL_Renderer* ren) {
    SDL_RenderCopy(ren,self->Texture,NULL,NULL);
}

void Background_init(struct GameObj* self, SDL_Renderer* ren) {
    self->Texture = Texture_Loader("assets/Others/Pre-Flip-Main-bg.png",ren);
    self->render = &Background_render;
    self->update = &Background_update;
} 
