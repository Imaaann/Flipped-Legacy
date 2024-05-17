#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void Generic_Image_update(GameObj* self) {
    printf("%dU",self->ID);
}

void Generic_Image_render(GameObj* self,SDL_Renderer* ren) {
    SDL_RenderCopy(ren,self->Texture,&self->srcRect,&self->destRect);
}

GameObj* Generic_Image_Init(SDL_Renderer* ren) {
    GameObj* obj = (GameObj*) malloc(sizeof(GameObj));

    obj->Texture = Texture_Loader("assets/Others/NULL.png",ren);

    obj->x = 0;
    obj->y = 0;

    obj->destRect.x = 0;
    obj->destRect.y = 0;
    obj->destRect.h = 32;
    obj->destRect.w = 32;

    obj->srcRect.x = 0;
    obj->srcRect.y = 0;
    obj->srcRect.h = 32;
    obj->srcRect.w = 32;

    obj->code = ST_GENER_IMG;
    obj->ID = 0;

    obj->render = Generic_Image_render;
    obj->update = Generic_Image_update;

    return obj;
}