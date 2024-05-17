#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void JOHNCENA_update(IntGameObj* self) {
    printf("%dU",self->ID);
}

void JOHNCENA_render(IntGameObj* self,SDL_Renderer* ren) {
    SDL_RenderCopy(ren,self->Texture,&self->srcRect,&self->destRect);
}

void JOHNCENA_Effect(IntGameObj* self,SDL_Event e,game_state* d,StaticInitFunc Statics[],IntInitFunc Inter[]) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_l) printf("%d: has been activated!!\n",self->ID);
    }
}

IntGameObj* JOHNCENA_Init(SDL_Renderer* ren) {

    IntGameObj* obj = (IntGameObj*) malloc(sizeof(IntGameObj));

    obj->Texture = Texture_Loader("assets/Others/Blank.png",ren);

    obj->x = 0;
    obj->y = 0;

    obj->destRect.x = 0;
    obj->destRect.y = 0;
    obj->destRect.h = 1;
    obj->destRect.w = 1;

    obj->srcRect.x = 0;
    obj->srcRect.y = 0;
    obj->srcRect.h = 1;
    obj->srcRect.w = 1;

    obj->code = INT_INVIS_JOHNCENA;
    obj->ID = 0;

    obj->render = JOHNCENA_render;
    obj->update = JOHNCENA_update;
    obj->effect = JOHNCENA_Effect;

    return obj;
}