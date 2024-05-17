#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void Generic_Btn_update(IntGameObj* self) {
    printf("%dU",self->ID);
}

void Generic_Btn_render(IntGameObj* self,SDL_Renderer* ren) {
    SDL_RenderCopy(ren,self->Texture,&self->srcRect,&self->destRect);
}

void Generic_Btn_Effect(IntGameObj* self,SDL_Event e,game_state* d, StaticInitFunc Statics[], IntInitFunc Inter[]) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_l) printf("%d: has been activated!!\n",self->ID);
    }
}

IntGameObj* Generic_Btn_Init(SDL_Renderer* ren) {

    IntGameObj* obj = (IntGameObj*) malloc(sizeof(IntGameObj));

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

    obj->code = INT_GENER_BTN;
    obj->ID = 0;

    obj->render = Generic_Btn_render;
    obj->update = Generic_Btn_update;
    obj->effect = Generic_Btn_Effect;

    return obj;
}