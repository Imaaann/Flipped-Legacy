#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void Generic_TXT_update(GameObj* self) {
    printf("%dU",self->ID);
}

void Generic_TXT_render(GameObj* self,SDL_Renderer* ren) {
    SDL_RenderCopy(ren,self->Texture,NULL,&self->destRect);
}

GameObj* Generic_TXT_Init(SDL_Renderer* ren) {
    GameObj* obj = (GameObj*) malloc(sizeof(GameObj));

    SDL_Color c = {255,255,255};
    obj->Texture = textLoader("Hello World!","assets/Others/Fonts/butler/Butler_Medium.ttf",c,14,ren);

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

    obj->code = ST_GENER_TXT;
    obj->ID = 0;

    obj->render = Generic_TXT_render;
    obj->update = Generic_TXT_update;

    return obj;
}